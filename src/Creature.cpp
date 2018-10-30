//
// Created on 10/14/18.
//

#include "../inc/Creature.hpp"
#include "../inc/Attack.hpp"
#include <iostream>

Creature::Creature(rapidxml::xml_node<> * creature_node) {


    for(rapidxml::xml_node<> * node = creature_node -> first_node(); node; node = node -> next_sibling())
    {
        std::string node_name = node -> name();

        if (node_name == "name") { this->name_ = node->value(); }
        else if (node_name == "status") { this->status_ = node->value(); }
        else if (node_name == "description") { this->description_ = node->value(); }
        else if (node_name == "vulnerability") { this->vulnerabilities_.push_back(node->value()); }
        else if (node_name == "trigger") { this->triggers_.push_back(new Trigger(node)); }
        else if (node_name == "attack") {  this-> attacks_.push_back(new Attack(node, "attack " + this -> name_));} //Model attack as trigger
    }

    //if no attack specification but the creature is vulnerable
    if(attacks_.empty() && !vulnerabilities_.empty())
    {
        this -> attacks_.push_back(new Attack(this -> name_));
    }

    
}

Creature::~Creature() { 
    for(auto attack: attacks_)
    {
        delete attack;
    }
}
ostream & operator<< (ostream& os, const Creature& creature)
{
    os << "Creature: " << creature.name_ << "\n";
    os << "status: " << creature.status_ << "\n";    
    os << "description: " << creature.description_ << "\n";  
    os << "Triggers: " ;
    for(Trigger * trigger: creature.triggers_)
    {
        os << *trigger << "\n";
    }
    os << endl;
    return os;
}