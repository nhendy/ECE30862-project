//
// Created on 9/24/18.
//

#include "../inc/StatusCondition.hpp"
#include "../inc/Condition.hpp"

StatusCondition::~StatusCondition() {}
StatusCondition::StatusCondition(rapidxml::xml_node<> * condition_node)
{
    for (rapidxml::xml_node <> * node = condition_node; node; node = node -> next_sibling())
    {
        string node_name = node -> name();
        if(node_name == "status") {this -> object_status_ = node -> value();}
        else if(node_name == "object") {this -> object_name_ = node -> value();}
    }
}


//TODO check if condition is satisfied
bool StatusCondition::isConditionSatisfied(GameWorld *) {}

