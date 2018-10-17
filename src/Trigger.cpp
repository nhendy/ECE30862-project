//
// Created on 9/20/18.
//

#include "../inc/Trigger.hpp"
#include "../inc/ConditionFactory.hpp"
#include "../inc/GameWorld.hpp"
#include <sstream>

Trigger::Trigger(rapidxml::xml_node<> *trigger_node)
{

    for (rapidxml::xml_node<> *node = trigger_node; node; node = node->next_sibling())
    {
        std::string node_name = node->name();

        if (node_name == "type")
        {
            this->type_ = node->value();
        }
        else if (node_name == "command")
        {
            this->command_ = node->value();
        }
        else if (node_name == "condition")
        {
            Condition *curr_condition = ConditionFactory::createCondition(node);
            this->conditions_.push_back(curr_condition);
        }
        else if (node_name == "print")
        {
            this->messages_.push_back(node->value());
        }
        else if (node_name == "action")
        {
            this->actions_.push_back(node->value());
        }
    }
}

/**
 * ref: https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
 */
void Trigger::fire(GameWorld& gameworld)
{
    //execute actions
    //execute prints

    for (std::string action : actions_)
    {
    
        istringstream iss(action);
        vector<string> command_tokens((istream_iterator<string>(iss)),
                                         istream_iterator<string>());
        if(command_tokens[0] == "Delete")
        {
            string obj_to_delete = command_tokens[1];
            gameworld.rooms_.find(obj_to_delete);

        }

    }


}

bool Trigger::is_activated(string input_command, GameWorld &gameworld)
{
    //Check if command exists;
    if (!command_.empty())
    {
        //Chech if command matches;
        if (input_command != command_)
        {
            return false;
        }
    }

    //Check if conditions are all satisfied
    for (Condition *cond : conditions_)
    {
        if (!cond->isConditionSatisfied(gameworld))
        {
            //If any fails return False;
            return false;
        }
    }

    //If all pass return True;
    return true;
}

Trigger::~Trigger() {}