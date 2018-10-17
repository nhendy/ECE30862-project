//
// Created on 9/24/18.
//

#include "../inc/HasCondition.hpp"
#include "../inc/GameWorld.hpp"
#include <algorithm>

HasCondition::~HasCondition() {}
HasCondition::HasCondition(rapidxml::xml_node<> *condition_node)
{
    for (rapidxml::xml_node<> *node = condition_node; node; node = node->next_sibling())
    {
        string node_name = node->name();
        if (node_name == "owner")
        {
            this->owner_ = node->value();
        }
        else if (node_name == "has")
        {
            this->has_ = node->value() == "no" ? false : true;
        }
        else if (node_name == "object")
        {
            this->object_name_ = node->value();
        }
    }
}

//TODO check if condition is satisfied
bool HasCondition::isConditionSatisfied(const GameWorld &gameworld)
{

    if (owner_ == "inventory")
    {
        if (gameworld.inventory_.find(object_name_) != gameworld.inventory_.end())
        {
            return has_;
        }
    }
    //find in room
    else if (gameworld.rooms_.find(owner_) != gameworld.rooms_.end())
    {
        Room * room = gameworld.rooms_.at(owner_);

        //find in items_
        if (find(room -> items_names_.begin(), room -> items_names_.end(), object_name_) != room -> items_names_.end())
        {
            return has_;
        }

        //find in containers
        if (find(room -> containers_names_.begin(), room -> containers_names_.end(), object_name_) != room -> containers_names_.end())
        {
            return has_;
        }

        //find in creatures
        if (find(room -> creatures_names_.begin(), room -> creatures_names_.end(), object_name_) != room -> creatures_names_.end())
        {
            return has_;
        }
    }


    //find in containers
    else if (gameworld.containers_.find(owner_) != gameworld.containers_.end())
    {
        Container * container = gameworld.containers_.at(owner_);

        //find in stored_items_
        if (find(container -> stored_items_.begin(), container -> stored_items_.end(), object_name_) != container -> stored_items_.end())
        {
            return has_;
        }
    
    }

    return false;
}
