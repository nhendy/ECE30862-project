#include "../inc/Trigger.hpp"
#include "../inc/ConditionFactory.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/Attack.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>


Attack::Attack(string creature) : Trigger(creature)
{
    this -> type_ = "permanent";
    this -> command_ = "attack " + creature;

}


Attack::Attack(rapidxml::xml_node<> * node, string command): Trigger(node, command){
    this -> type_ = "permanent";
} //Overloaded constructor


Attack::~Attack(){}

bool Attack::IsActivated(string input_command, GameWorld &gameworld)
{
    //Tokenize to find the creature
    istringstream iss(input_command);
    vector<std::string> command_tokens((istream_iterator<std::string>(iss)), istream_iterator<std::string>());

    

    string creature_name = command_tokens[1];
    string weapon = command_tokens[3];


    
    //Chech if command matches;
    if ("attack " + creature_name != command_)
    {

        return false;
    }

    

    //Check if creature is in current room
    if(find(gameworld.rooms_map_[gameworld.current_room_] -> creatures_names_.begin(),
            gameworld.rooms_map_[gameworld.current_room_] -> creatures_names_.end(), creature_name) == gameworld.rooms_map_[gameworld.current_room_] -> creatures_names_.end())
    {
        #ifdef DEBUG_C
        cout << creature_name << " not in the room" << endl;
        #endif
        cout << "Error" << endl;
        return false;
    }

    //If so check vulnerabilities 

    Creature * creature = gameworld.creatures_map_[creature_name];
    

    if(find(creature -> vulnerabilities_.begin(), creature -> vulnerabilities_.end(), weapon) == creature -> vulnerabilities_.end())
    {
        #ifdef DEBUG_C
        cout << "Vulnerability not there" << endl;
        #endif
        cout << "Error" << endl;
        return false;
    }


    //check if player has the weapon in inventory
    if(gameworld.inventory_map_.find(weapon) == gameworld.inventory_map_.end())
    {
        cout << "Error" <<endl;
        
        return false;
    }


    //Check if conditions are all satisfied
    for (Condition *cond : conditions_)
    {
        if (!cond->IsConditionSatisfied(gameworld))
        {
            //If any fails return False;
            return false;
        }
    }


    cout << "You assault the " << creature_name << " with the " << weapon << "." << endl;


    //If all pass return True;
    return true;
}