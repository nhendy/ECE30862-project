//
// Created by Noureldin Hendy on 9/20/18.
//

#include "../inc/Trigger.hpp"
#include "../inc/ConditionFactory.hpp"

Trigger::Trigger(rapidxml::xml_node<> * trigger_node) {

    for(rapidxml::xml_node <> * node = trigger_node; node; node = node -> next_sibling())
    {
        std::string node_name = node -> name();

        if(node_name == "type") {this -> type_ = node -> value(); }
        else if (node_name == "command") {this -> command_ = node -> value();}
        else if (node_name == "condition")
        {
            Condition * curr_condition = ConditionFactory::createCondition(node);
            this -> conditions_.push_back(curr_condition);
        }
        else if (node_name == "print") {this -> messages_.push_back(node -> value());}
        else if (node_name == "action") {this -> actions_.push_back(node -> value());}

    }


}
Trigger::~Trigger() {}