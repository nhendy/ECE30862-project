//
// Created on 10/14/18.
//

#include "../inc/Creature.hpp"

Creature::Creature(rapidxml::xml_node<> * creature_node) {

    for(rapidxml::xml_node<> * node = creature_node; node; node = node -> next_sibling())
    {
        std::string node_name = node -> name();

        if (node_name == "name") { this->name_ = node->value(); }
        else if (node_name == "status") { this->status_ = node->value(); }
        else if (node_name == "description") { this->description_ = node->value(); }
        else if (node_name == "trigger") { this->triggers_.push_back(new Trigger(node)); }
        else if (node_name == "attack") { this-> attack_ = new Trigger(node);}
    }
}
Creature::~Creature() {}
