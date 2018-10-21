//
// Created on 9/23/18.
//

#include "../inc/Item.hpp"


Item::~Item() {}
Item::Item(rapidxml::xml_node<> * item_node) {

    for (rapidxml::xml_node<> * node = item_node; node; node = node -> next_sibling()) {
        std::string node_name = node->name();

        if (node_name == "name") { this->name_ = node->value(); }
        else if (node_name == "status") { this->status_ = node->value(); }
        else if (node_name == "description") { this->description_ = node->value(); }
        else if (node_name == "trigger") { this->triggers_.push_back(new Trigger(node)); }
        else if (node_name == "turnon") { this->triggers_.push_back(new Trigger(node, "turn on"));}
        else if (node_name == "writing") { this-> writing_ = node -> value();}

    }


}

// void Item::buildTrunOn(rapidxml::xml_node<> * turnon_node) {

//     for(rapidxml::xml_node<> * node = turnon_node; node; node = node -> next_sibling())
//     {
//         std::string node_name = node->name();

//         if (node_name == "print") { this->messages_.push_back(node->value());}
//         else if (node_name == "action") { this->actions_.push_back(node->value());}
//     }
// }