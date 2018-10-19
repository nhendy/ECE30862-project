//
// Created on 9/20/18.
//

#include "../inc/Trigger.hpp"
#include "../inc/ConditionFactory.hpp"
#include "../inc/GameWorld.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>

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
        vector<string> command_tokens((istream_iterator<string>(iss)),  // KEEP EXTRA PARANTHESES! 
                                         istream_iterator<string>());   // to disambiguate function call

        //TODO check validity of the action
        //TODO check if objects exist

        //Execute Delete
        if(command_tokens[0] == "Delete")
        {
            string obj_to_delete = command_tokens[1];
            string obj_to_delete_type = gameworld.name_to_type_[obj_to_delete];

            //curr room object
            Room * curr_room = gameworld.rooms_map_[gameworld.current_room_];

            if(obj_to_delete_type == "room")
            {
                //Loop over directions_to_room till the room is the target room to delete
                for(map<string, string>::iterator it = curr_room -> direction_to_room_.find(obj_to_delete); it != curr_room -> direction_to_room_.end(); it++ )
                {
                    if(it -> second == obj_to_delete)
                    {
                        curr_room -> direction_to_room_.erase(it);
                        break;
                    }
                }
            }
            else if (obj_to_delete_type == "item")
            {
                //find in items vector and delete
                vector<string>::iterator it = find(curr_room -> items_names_.begin(), curr_room -> items_names_.end(), obj_to_delete);
                if(it != curr_room -> items_names_.end())
                {
                    curr_room -> items_names_.erase(it);   
                }
            }
            else if (obj_to_delete_type == "creatue")
            {
                //find in creatrues vector and delete
                vector<string>::iterator it = find(curr_room -> creatures_names_.begin(), curr_room -> creatures_names_.end(), obj_to_delete);
                if(it != curr_room -> creatures_names_.end())
                {
                    curr_room -> creatures_names_.erase(it);   
                }
            }
            else if (obj_to_delete_type == "container")
            {
                //find in containers vector and delete
                vector<string>::iterator it = find(curr_room -> containers_names_.begin(), curr_room -> containers_names_.end(), obj_to_delete);
                if(it != curr_room -> containers_names_.end())
                {
                    curr_room -> containers_names_.erase(it);   
                }
            }

        } // if(command_tokens[0] == "Delete")

        //Execute Add
        else if(command_tokens[0] == "Add")
        {
            string obj_to_add = command_tokens[1];
            string dest_obj   = command_tokens[3];
            string dest_type   = gameworld.name_to_type_[dest_obj];
            string obj_to_add_type = gameworld.name_to_type_[obj_to_add];
            
            if(dest_type == "room")
            {
                if(obj_to_add_type == "container")
                {
                    //TODO
                }
                else if (obj_to_add_type == "item")
                {
                    //TODO
                }
                else if (obj_to_add_type == "creature")
                {
                    //TODO
                }

            }
            else if (dest_type == "container")
            {
                if (obj_to_add_type == "item")
                {
                    //TODO
                }
            
            }
            
        } // else if(command_tokens[0] == "Add")

        //TODO Update
        //Execute Update
        else if(command_tokens[0] == "Update")
        {


        }// else if(command_tokens[0] == "Update")

        //TODO Game Over
        //Execute Game Over
        else if(action == "Game Over")
        {
            gameworld.game_over_ = true;

        }// else if(action == "Game Over")

    }//  for (std::string action : actions_)

    //TODO loop over prints


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