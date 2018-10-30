//
// Created on 9/23/18.
//

#include "../inc/Item.hpp"
#include <iostream>
#include "../inc/HasCondition.hpp"

Item::~Item() {}
Item::Item(rapidxml::xml_node<> * item_node) {

    for (rapidxml::xml_node<> * node = item_node -> first_node(); node; node = node -> next_sibling()) {
        std::string node_name = node->name();

        if (node_name == "name") { this->name_ = node->value(); }
        else if (node_name == "status") { this->status_ = node->value(); }
        else if (node_name == "description") { this->description_ = node->value(); }
        else if (node_name == "trigger") { this->triggers_.push_back(new Trigger(node)); }
        else if (node_name == "turnon") { 
            Trigger * trigger =  new Trigger(node, "turn on " + this -> name_);
            trigger -> messages_.insert(trigger -> messages_.begin(), "You activate the " + this -> name_ + ".");
            trigger -> conditions_.push_back(new HasCondition("inventory", true, this -> name_));
            this->triggers_.push_back(trigger);
        }
        else if (node_name == "writing") { this-> writing_ = node -> value();}

    }


}

ostream & operator<< (ostream& os, const Item& item)
{
    os << "Item: " << item.name_ << "\n";
    os << "status: " << item.status_ << "\n";    
    os << "description: " << item.description_ << "\n";  
    os << "Triggers: " ;
    for(Trigger * trigger: item.triggers_)
    {
        os << *trigger << "\n";
    }
    os << "Writing: " << item.writing_ ;
   
   
    os << endl;
    return os;
}

// void Item::buildTrunOn(rapidxml::xml_node<> * turnon_node) {

//     for(rapidxml::xml_node<> * node = turnon_node; node; node = node -> next_sibling())
//     {
//         std::string node_name = node->name();

//         if (node_name == "print") { this->messages_.push_back(node->value());}
//         else if (node_name == "action") { this->actions_.push_back(node->value());}
//     }
// }