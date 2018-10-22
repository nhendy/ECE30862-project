//
// Created on 9/18/18.
//

#include "../inc/GameWorld.hpp"
#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <dirent.h>

using namespace std;

/**************************** Constructors & destructors ****************************/

GameWorld::GameWorld() {}
GameWorld::~GameWorld() 
{
    //Don't deallocate inventory since it's just another copy
    //of items
    for(auto room_pair: rooms_map_)
    {
        delete room_pair.second;
    }

    for(auto item_pair: items_map_)
    {
        delete item_pair.second;
    }

    for(auto creature_pair: creatures_map_)
    {
        delete creature_pair.second;
    }

    for(auto container_pair: containers_map_)
    {
        delete container_pair.second;
    }

}
bool GameWorld::InitGame()
{
    rapidxml::xml_document<> doc;
    ifstream file("sample.txt.xml");

    stringstream buffer;
    buffer << file.rdbuf();
    string content(buffer.str());
    cout << content << endl;

    doc.parse<0>(&content[0]);
    rapidxml::xml_node<> *root_node = doc.first_node("map");
    if (root_node == nullptr)
    {
        cout << "can't open the file" << endl;
    }
    else
    {
        cout << root_node->name() << endl;

        for (rapidxml::xml_node<> *node = root_node->first_node(); node; node = node->next_sibling())
        {
            string node_name = node->name();

            cout << node_name << endl;

            if (node_name == "room")
            {
                Room *room = new Room(node);
                string name = room->name_;

                rooms_map_.insert(pair<string, Room *>(name, room));
                name_to_type_[name] = "room";
            }
            else if (node_name == "creature")
            {
                Creature *creature = new Creature(node);
                string name = creature->name_;

                creatures_map_.insert(pair<string, Creature *>(name, creature));
                name_to_type_[name] = "creature";
            }
            else if (node_name == "container")
            {
                Container *container = new Container(node);
                string name = container->name_;

                containers_map_.insert(pair<string, Container *>(name, container));
                name_to_type_[name] = "container";
            }
            else if (node_name == "item")
            {
                Item *item = new Item(node);
                string name = item->name_;

                items_map_.insert(pair<string, Item *>(name, item));
                name_to_type_[name] = "item";
            }
        }

        file.close();
        
        //Go to entrance
        this -> current_room_ = "Entrance";
        cout << rooms_map_[current_room_] -> description_ << endl;

        return true;
    }


    return false;
}

/*************************************** Game loop ***************************************/
void GameWorld::GameLoop()
{
    string input_command;

    while (!game_over_)
    {
        input_command = ParseInput();

        if (pending_triggers_.empty())
        {
            Execute(input_command);
        }

        while (!pending_triggers_.empty())
        {
            Trigger *trigger = pending_triggers_.front();
            pending_triggers_.pop();

            trigger->Fire(*this);
        }
    }

    cout << "Game Over" << endl;
}

/************************************** Trigger checking **********************************/
void GameWorld::UpdateTriggerQueue(string input_command)
{
    //TODO
    //TODO Refactor
    //Loop over triggers check commands AND conditions !! LOOP OVER MEANINGFUL TRIGGERS !!
    //You can only trigger triggers of objects in the current room

    Room *curr_room = this->rooms_map_[current_room_];

    //loop over room triggers
    for (Trigger *trigger : curr_room->triggers_)
    {
        //check if trigger is activated
        if (trigger->IsActivated(input_command, *this) && !trigger->is_disabled())
        {
            //enqueue to pending triggers
            this->pending_triggers_.push(trigger);
        }
    }

    //loop over inventory triggers
    for (auto &item_pair : inventory_map_)
    {
        for (Trigger *trigger : item_pair.second->triggers_)
        {
            //check if trigger is activated
            if (trigger->IsActivated(input_command, *this) && !trigger->is_disabled())
            {
                //enqueue to pending triggers
                this->pending_triggers_.push(trigger);
            }
        }
    }

    //loop over items in room
    for (string item : curr_room->items_names_)
    {
        Item *item_ptr = this->items_map_[item];

        //loop over triggers of items
        for (Trigger *trigger : item_ptr->triggers_)
        {
            //check if trigger is activated
            if (trigger->IsActivated(input_command, *this) && !trigger->is_disabled())
            {
                //enqueue to pending triggers
                this->pending_triggers_.push(trigger);
            }
        }
    }

    //loop over containers in room
    for (string container : curr_room->containers_names_)
    {
        Container *container_ptr = this->containers_map_[container];

        //loop over triggers of containers
        for (Trigger *trigger : container_ptr->triggers_)
        {
            //check if trigger is activated
            if (trigger->IsActivated(input_command, *this) && !trigger->is_disabled())
            {
                //enqueue to pending triggers
                this->pending_triggers_.push(trigger);
            }
        }
    }

    //loop over creatures in room
    for (string creature : curr_room->creatures_names_)
    {
        Creature *creature_ptr = this->creatures_map_[creature];

        //loop over triggers of creatures
        for (Trigger *trigger : creature_ptr->triggers_)
        {
            //check if trigger is activated
            if (trigger->IsActivated(input_command, *this) && !trigger->is_disabled())
            {
                //enqueue to pending triggers
                this->pending_triggers_.push(trigger);
            }
        }
    }
}

/************************************** Parse Input **********************************/
string GameWorld::ParseInput()
{
    string input = "";

    getline(cin, input);
    this->UpdateTriggerQueue(input);

    return input;
}

/************************************** Executing input commands **********************************/

//TODO check if input_command is valid
bool GameWorld::Execute(string input_command)
{
    if (input_command == "n" || input_command == "s" || input_command == "e" || input_command == "w")
    {
        return this->ChangeRoom(input_command);
    }
    if (input_command == "i")
    {
        return this->ShowInventory();
    }
    if (input_command.find("take") != string::npos)
    {
        return this->Take(input_command.substr(string("take").length() + 1));
    }
    if (input_command.find("open") != string::npos)
    {
        return this->Open(input_command.substr(string("open").length() + 1));
    }
    if (input_command.find("read") != string::npos)
    {
        return this->Read(input_command.substr(string("read").length() + 1));
    }
    if (input_command.find("drop") != string::npos)
    {
        return this->Drop(input_command.substr(string("drop").length() + 1));
    }
    if (input_command.find("put") != string::npos)
    {
        return this->Put(input_command.substr(string("put").length() + 1));
    }
    if (input_command.find("turn on") != string::npos)
    {
        return this->Turnon(input_command.substr(string("turn on").length() + 1));
    }
    if (input_command.find("attack") != string::npos)
    {
        return this->Attack(input_command.substr(string("attack").length() + 1));
    }

    return false;
}

/************************************** Commands **********************************/

/**
 * @Author: Damini
 **/
bool GameWorld::ChangeRoom(string direction) {
    if(direction == "n")
    {
        Room *ptr = rooms_map_.at(current_room_); 
        if(ptr->direction_to_room_.find("north") != ptr->direction_to_room_.end())
        {
            current_room_ = ptr->direction_to_room_["north"]; 
        }
        else{
            std::cout<<"Can’t go that way."<<std::endl;
        }
    }
    if(direction == "s")
    {
        Room *ptr = rooms_map_.at(current_room_); 
        if(ptr->direction_to_room_.find("south") != ptr->direction_to_room_.end())
        {
            current_room_ = ptr->direction_to_room_["south"]; 
        }
        else{
            std::cout<<"Can’t go that way."<<std::endl;
        }
    }
    if(direction == "e")
    {
        Room *ptr = rooms_map_.at(current_room_); 
        if(ptr->direction_to_room_.find("east") != ptr->direction_to_room_.end())
        {
            current_room_ = ptr->direction_to_room_["east"]; 
        }
        else{
            std::cout<<"Can’t go that way."<<std::endl;
        }
    }
    if(direction == "w")
    {
        Room *ptr = rooms_map_.at(current_room_); 
        if(ptr->direction_to_room_.find("west") != ptr->direction_to_room_.end())
        {
            current_room_ = ptr->direction_to_room_["west"]; 
        }
        else{
            std::cout<<"Can’t go that way."<<std::endl;
        }
    }

      this->UpdateTriggerQueue(""); // Update not using commands
}
bool GameWorld::ShowInventory()
{
    cout << "Inventory: ";

    int ct = 0; // Used to determine if the first item in inventory is being printed
    for (auto &item_pair : inventory_map_)
    {
        if (ct == 0)
        {
            cout << item_pair.first;
            ct++;
        }
        else
        {
            cout << ", " << item_pair.first;
        }
    }
    if (ct == 0)
    { 
        // Count will not be updated if an item is not found in the inventory
        cout << "empty" << endl;
        return false;
    }
    cout << endl;
    this->UpdateTriggerQueue(""); // Update not using commands
    return true;
}

bool GameWorld::Take(string input)
{

    this->UpdateTriggerQueue(""); // Update not using commands
}
bool GameWorld::Open(string input)
{
    map<std::string, Container *>::iterator it;
    if (input == "exit")
    { // End game if you try to open "exit"
        game_over_ = true;
        return true;
    }
    it = containers_map_.find(input); // Iterator
    if (it != containers_map_.end())
    { 
        // Check if container exists
        if (it->second->status_ == "locked")
        { 
            // Check if container is locked
            cout << it->first << " is locked." << endl;
            return false;
        }
        else
        {    
            //TODO Review this            
            // If container is not locked, loop through all items in the container and print them
            int ct = 0; // Counts number of items in container that have been seen
            for (auto itr = (it->second)->stored_items_.begin(); itr != (it->second)->stored_items_.end(); itr++)
            {
                ct++;
                cout << *itr << endl;
            }
            if (ct == 0)
            { 
                // If no items found, print empty
                cout << it->first << " is empty." << endl;
            }
        }
    }
    else
    { 
        // This is if the container does not exist
        cout << "Error" << endl;
        return false;
    }
    this->UpdateTriggerQueue(""); // Update not using commands
    return true;
}
bool GameWorld::Read(string input)
{
    map<std::string, Item *>::iterator it;
    it = inventory_map_.find(input); // Iterator
    if (it == inventory_map_.end())
    { // Item does not exist in user's current inventory
        cout << "Error" << endl;
        return false;
    }
    else
    {
        if ((it->second)->writing_.empty())
        {
            cout << "Nothing written." << endl;
        }
        else
        {
            cout << (it->second)->writing_ << endl;
        }
    }
    this->UpdateTriggerQueue(""); // Update not using commands
    return true;
}
bool GameWorld::Drop(string input)
{

    this->UpdateTriggerQueue(""); // Update not using commands
}
bool GameWorld::Turnon(string input)
{

    this->UpdateTriggerQueue(""); // Update not using commands
}
bool GameWorld::Attack(string input)
{

    this->UpdateTriggerQueue(""); // Update not using commands
}
bool GameWorld::Put(string input)
{


    this->UpdateTriggerQueue(""); // Update not using commands
}
