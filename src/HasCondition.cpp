//
// Created on 9/24/18.
//

#include "../inc/HasCondition.hpp"
#include "../inc/GameWorld.hpp"

HasCondition::~HasCondition() {}
HasCondition::HasCondition(rapidxml::xml_node<> * condition_node)
{
    for (rapidxml::xml_node <> * node = condition_node; node; node = node -> next_sibling())
    {
        string node_name = node -> name();
        if(node_name == "owner") {this -> owner_ = node -> value();}
        else if(node_name == "has")
        {
            this -> has_ = node -> value() == "no" ? false : true;
        }
        else if(node_name == "object") {this -> object_name_ = node -> value();}
    }
}



//TODO check if condition is satisfied
bool HasCondition::isConditionSatisfied(const GameWorld&) {}