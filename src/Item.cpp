//
// Created by Noureldin Hendy on 9/23/18.
//

#include "../inc/Item.hpp"

Item::Item(rapidxml::xml_node<> * item_node) {

    for (rapidxml::xml_node<> * node = item_node; node; node = node -> next_sibling())
    {

    }

}
Item::~Item() {}
