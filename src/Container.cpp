//
// Created on 10/14/18.
//

#include "../inc/Container.hpp"
#include "../inc/Item.hpp"

Container::Container(rapidxml::xml_node<> * container_node) {

    for(rapidxml::xml_node<> * node = container_node; node; node = node -> next_sibling())
    {
        std::string node_name = node -> name();

        if (node_name == "name") { this->name_ = node->value(); }
        else if (node_name == "status") { this->status_ = node->value(); }
        else if (node_name == "description") { this->description_ = node->value(); }
        else if (node_name == "trigger") { this->triggers_.push_back(new Trigger(node)); }
        else if (node_name == "item") { this-> stored_items_.push_back(node -> value());}
        else if (node_name == "accept") { this-> accepted_.push_back(node -> value());}
    }

}
Container::~Container() {}