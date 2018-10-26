//
// Created on 10/14/18.
//
#include <iostream>
#include "../inc/Container.hpp"
#include "../inc/Item.hpp"

Container::Container(rapidxml::xml_node<> * container_node) {

    for(rapidxml::xml_node<> * node = container_node -> first_node(); node; node = node -> next_sibling())
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


ostream & operator<< (ostream& os, const Container& container)
{
    os << "Container: " << container.name_ << "\n";
    os << "status: " << container.status_ << "\n";    
    os << "description: " << container.description_ << "\n";  
    os << "Triggers: " ;
    for(Trigger * trigger: container.triggers_)
    {
        os << *trigger << "\n";
    }
    os << "Items: " ;
    for(auto item: container.stored_items_)
    {
        os << item << "\n";
    }  
    os << "Accepted: " ;
    for(auto accepted: container.accepted_)
    {
        os << accepted << "\n";
    }  
    os << endl;
    return os;
}