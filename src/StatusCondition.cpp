//
// Created on 9/24/18.
//

#include "../inc/StatusCondition.hpp"
#include "../inc/GameWorld.hpp"

StatusCondition::~StatusCondition() {}
StatusCondition::StatusCondition(rapidxml::xml_node<> *condition_node)
{
    for (rapidxml::xml_node<> *node = condition_node; node; node = node->next_sibling())
    {
        string node_name = node->name();
        if (node_name == "status")
        {
            this->object_status_ = node->value();
        }
        else if (node_name == "object")
        {
            this->object_name_ = node->value();
        }
    }
}

//TODO check if condition is satisfied
bool StatusCondition::isConditionSatisfied(const GameWorld &gameworld)
{

    string stat = "";

    if (gameworld.rooms_.find(object_name_) != gameworld.rooms_.end())
    {
        Room *room = gameworld.rooms_.at(object_name_);
        stat = room->status_;

    }

    else if (gameworld.items_.find(object_name_) != gameworld.items_.end())
    {
        Item *item = gameworld.items_.at(object_name_);
        stat = item->status_;

    }

    else if (gameworld.containers_.find(object_name_) != gameworld.containers_.end())
    {
        Container *container = gameworld.containers_.at(object_name_);
        stat = container->status_;
    }

    else if (gameworld.creatures_.find(object_name_) != gameworld.creatures_.end())
    {
        Creature *creature = gameworld.creatures_.at(object_name_);
        stat = creature->status_;
    }

    return stat == object_status_;

}
