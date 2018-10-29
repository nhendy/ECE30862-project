#include "../inc/Trigger.hpp"
#include "../inc/ConditionFactory.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/Attack.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>


Attack::Attack(rapidxml::xml_node<> *trigger_node) : Trigger(trigger_node){}
Attack::Attack(rapidxml::xml_node<> *trigger_node, string input): Trigger(trigger_node, input){}
Attack::~Attack(){}


bool Attack::IsActivated(string input_command, GameWorld &gameworld)
{
    //Tokenize to find the creature
    istringstream iss(input_command);
    vector<std::string> command_tokens((istream_iterator<std::string>(iss)), istream_iterator<std::string>());

    //Need to speify weapon too
    if(command_tokens.size() != 4)    {return false;}
    

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
        // cout << "Error" << endl;
        return false;
    }

    // //If so check vulnerabilities 

    Creature * creature = gameworld.creatures_map_[creature_name];
    // bool FOUND = false;

    // for(string vulnerability: creature -> vulnerabilities_)
    // {
    //     if(gameworld.inventory_map_.find(vulnerability) != gameworld.inventory_map_.end())
    //     {
    //         FOUND = true;
    //         break;
    //     }
    // }

    // if(!creature -> vulnerabilities_.empty() && !FOUND)
    // {
    //     #ifdef DEBUG_C
    //     cout << "Vulnerability not there" << endl;
    //     #endif
    //     return false;
    // }

    if(find(creature -> vulnerabilities_.begin(), creature -> vulnerabilities_.end(), weapon) == creature -> vulnerabilities_.end())
    {
        #ifdef DEBUG_C
        cout << "Vulnerability not there" << endl;
        #endif
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


    cout << "You assault the " << creature_name << " with " << weapon << endl;

    //remove weapon from the inventory

    gameworld.inventory_map_.erase(weapon);  //==============??????

    //If all pass return True;
    return true;
}