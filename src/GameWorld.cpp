//
// Created on 9/18/18.
//

#include "../inc/GameWorld.hpp"
#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <dirent.h>
#include <algorithm>

using namespace std;

/**************************** Constructors & destructors ****************************/

GameWorld::GameWorld() {}
GameWorld::~GameWorld()
{
    //Don't deallocate inventory since it's just another copy
    //of items
    for (auto room_pair : rooms_map_)
    {
        delete room_pair.second;
    }

    for (auto item_pair : items_map_)
    {
        delete item_pair.second;
    }

    for (auto creature_pair : creatures_map_)
    {
        delete creature_pair.second;
    }

    for (auto container_pair : containers_map_)
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
#ifdef DEBUG
    cout << content << endl;
#endif
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
#ifdef DEBUG
            cout << node_name << endl;
#endif
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
        this->current_room_ = "Entrance";
        cout << rooms_map_[current_room_]->description_ << endl;

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

#ifdef DEBUG
    cout << "Updating trigger queue, curr room is " << *curr_room << endl;
#endif

    //loop over room triggers
    for (Trigger *trigger : curr_room->triggers_)
    {
        //check if trigger is activated
        if (trigger->IsActivated(input_command, *this) && !trigger->is_disabled())
        {
#ifdef DEBUG
            cout << "Trigger in rooms is activated" << endl;
#endif
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
#ifdef DEBUG
                cout << "Trigger in inventory is activated" << endl;
#endif

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
#ifdef DEBUG
                cout << "Trigger in current room items is activated" << endl;
#endif
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
#ifdef DEBUG
                cout << "Trigger in containers in current room is activated" << endl;
#endif
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
#ifdef DEBUG
                cout << "Trigger in creatures is activated" << endl;
#endif
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
#ifdef DEBUG
    cout << "Input is " << input << endl;
#endif
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

    // if (input_command.find("open") != string::npos)
    // {
    //     return this->Open(input_command.substr(string("open").length() + 1));
    // }
    // if (input_command.find("read") != string::npos)
    // {
    //     return this->Read(input_command.substr(string("read").length() + 1));
    // }
    // if (input_command.find("drop") != string::npos)
    // {
    //     return this->Drop(input_command.substr(string("drop").length() + 1));
    // }
    // if (input_command.find("put") != string::npos)
    // {
    //     return this->Put(input_command.substr(string("put").length() + 1));
    // }
    // if (input_command.find("turn on") != string::npos)
    // {
    //     return this->Turnon(input_command.substr(string("turn on").length() + 1));
    // }
    // if (input_command.find("attack") != string::npos)
    // {
    //     return this->Attack(input_command.substr(string("attack").length() + 1));
    // }

    return false;
}

/************************************** Commands **********************************/

/**
 * @Author: Damini
 **/
bool GameWorld::ChangeRoom(string direction)
{

    #ifdef DEBUG_1
    cout << "Trying to change room now @ " << current_room_ << endl;

    for(auto & pair : rooms_map_ )
    {
        cout << pair.first << endl;
    }
    #endif
    // pointer to curretn room
    Room *room_ptr = rooms_map_.at(current_room_);
    if (direction == "n")
    {

        //check if the direction exists
        if (room_ptr->direction_to_room_.find("north") != room_ptr->direction_to_room_.end())
        {

            //change current room if it exists
            current_room_ = room_ptr->direction_to_room_["north"];
            // print the description of the room
            std::cout << " " << room_ptr->description_ << std::endl;
        }
        else
        {
            //if not then print error
            std::cout << "Can’t go that way." << std::endl;
        }
    }
    //repeat for all directions
    if (direction == "s")
    {

        if (room_ptr->direction_to_room_.find("south") != room_ptr->direction_to_room_.end())
        {
            current_room_ = room_ptr->direction_to_room_["south"];
            std::cout << " " << room_ptr->description_ << std::endl;
        }
        else
        {
            cout << "Can’t go that way." << std::endl;
        }
    }
    if (direction == "e")
    {

        if (room_ptr->direction_to_room_.find("east") != room_ptr->direction_to_room_.end())
        {
            current_room_ = room_ptr->direction_to_room_["east"];
            cout << " " << room_ptr->description_ << std::endl;
        }
        else
        {
            cout << "Can’t go that way." << std::endl;
        }
    }
    if (direction == "w")
    {

        if (room_ptr->direction_to_room_.find("west") != room_ptr->direction_to_room_.end())
        {
            current_room_ = room_ptr->direction_to_room_["west"];
            cout << " " << room_ptr->description_ << std::endl;
        }
        else
        {
            cout << "Can’t go that way." << std::endl;
        }
    }

    this->UpdateTriggerQueue(""); // Update not using commands
}
bool GameWorld::ShowInventory()
{
    /**
	 * @Author: Urvaksh
	 **/
    cout << "Inventory: ";
    if (inventory_map_.empty())
    { // Check if inventory is empty
        cout << "empty" << endl;
        return false;
    }

    for (map<std::string, Item *>::iterator item_iter = inventory_map_.begin(); item_iter != (--inventory_map_.end()); item_iter++)
    { // Looping from the first item in inventory until the second last element in the inventory
        cout << item_iter->first << ", ";
    }
    cout << (inventory_map_.rbegin())->first << endl; // Prints the last element in the inventory map
    this->UpdateTriggerQueue("");                     // Update not using commands
    return true;
}

/**
 * @Author: Damini
 **/

bool GameWorld::Take(string item)
{

    Room *room_ptr = rooms_map_.at(current_room_);
    //if item in room
    if (find(room_ptr->items_names_.begin(), room_ptr->items_names_.end(), item) != room_ptr->items_names_.end())
    {
        inventory_map_[item] = items_map_[item];
        //Delete from room
        room_ptr->items_names_.erase(find(room_ptr->items_names_.begin(), room_ptr->items_names_.end(), item));
#ifdef DEBUG_1
        cout << "Room after deleting item " << item << " from it" << endl;
        for (auto name : room_ptr->items_names_)
        {
            cout << name << endl;
        }
#endif

        cout << "Item " << item << " added to inventory" << endl;

        return true;
    }

    //room in room container items
    for (string container_name : room_ptr->containers_names_)
    {
        Container *container = containers_map_[container_name];

        if (container->status_ == "unlocked")
        {
            if (find(container->stored_items_.begin(), container->stored_items_.end(), item) != container->stored_items_.end())
            {
                inventory_map_[item] = items_map_[item];
                container->stored_items_.erase(find(container->stored_items_.begin(), container->stored_items_.end(), item));
            }
        }
    }

    this->UpdateTriggerQueue(""); // Update not using commands
}

bool GameWorld::Open(string input)
{
    /**
	 * @Author: Urvaksh
	 **/
    map<std::string, Container *>::iterator container_ptr;
    if (input == "exit")
    { // End game if you try to open "exit"
        map<std::string, Room *>::iterator room_ptr;
        room_ptr = rooms_map_.find(current_room_); // Pointer to room you are currently in
        if (((room_ptr->second)->type_) == "exit")
        { // If you are in a room of type "exit"
            game_over_ = true;
            return true;
        }
        else
        { // If you are not in a room of type "exit" then "open exit" is an invalid command
            cout << "Invalid command" << endl;
            return false;
        }
    }
    container_ptr = containers_map_.find(input); // Iterator
    if (container_ptr != containers_map_.end())
    {
        // Check if container exists
        if (container_ptr->second->status_ == "locked")
        {
            // Check if container is locked
            cout << container_ptr->first << " is locked." << endl;
            return false;
        }
        else
        {
            //TODO Review this
            // If container is not locked, loop through a items in the container and print them
            if ((container_ptr->second)->stored_items_.empty())
            {
                cout << container_ptr->first << " is empty." << endl;
            }
            for (auto itr = (container_ptr->second)->stored_items_.begin(); itr != (container_ptr->second)->stored_items_.end(); itr++)
            {
                cout << *itr << endl;
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

// bool GameWorld::Read(string input)
// {
// 	/**
// 		 * @Author: Urvaksh
// 	**/
//     map<std::string, Item *>::iterator it;
//     it = inventory_map_.find(input); // Iterator
//     if (it == inventory_map_.end())
//     { // Item does not exist in user's current inventory
//         cout << "Error" << endl;
//         return false;
//     }
//     else
//     {
//         if ((it->second)->writing_.empty())
//         {
//             cout << "Nothing written." << endl;
//         }
//         else
//         {
//             cout << (it->second)->writing_ << endl;
//         }
//     }
//     this->UpdateTriggerQueue(""); // Update not using commands
//     return true;
// }

// /**
//  * @Author: Damini
//  **/
// bool GameWorld::Drop(string input)
// {
//     Room *room_ptr = rooms_map_.at(current_room_);
//     //if input in inventory
//     if( inventory_map_.find(input) != inventory_map_.end())
//     {
//         //then change from inventory to room
//         //add to room items
//         room_prt->items_names_.push_back(input);
//         //remove from inventroy map
//         inventory_map_.erase (input);
//         //print dropped
//         cout<< input <<" dropped."<<std::endl;
//     }
//     this->UpdateTriggerQueue(""); // Update not using commands
// }

// bool GameWorld::Turnon(string item)
// {
// 	/**
// 		 * @Author: Urvaksh
// 	**/

// 	// THIS MIGHT NOT WORK!!!!
//     this->UpdateTriggerQueue("turn on " + item); // Update not using commands
//     return true;

// }

// bool GameWorld::Attack(string input)
// {
//     istringstream iss(input);
//     vector<string> command_tokens((istream_iterator<string>(iss)),  // KEEP EXTRA PARANTHESES!
//                                         istream_iterator<string>());   // to disambiguate function call

//     string creatue_to_attack = command_tokens[0];
//     string weapon            = command_tokens[2];

//     if(creatures_map_.find(creatue_to_attack) == creatures_map_.end())
//     {
//         #ifdef DEBUG
//         cout << "Creature not existent" << endl;
//         #endif
//         return false;
//     }
//     if(inventory_map_.find(weapon) == inventory_map_.end())
//     {
//         #ifdef DEBUG
//         cout << "Weapon not existent" << endl;
//         #endif
//         return false;
//     }
//     Creature * creature_ptr  = creatures_map_[creatue_to_attack];
//     if(find(creature_ptr -> vulnerabilities_.begin(), creature_ptr -> vulnerabilities_.end(), weapon) == creature_ptr -> vulnerabilities_.end())
//     {
//         #ifdef DEBUG
//         cout << "Creature is not vulnerable" << endl;
//         #endif
//         cout << "Can't attack with " << weapon << endl;
//         return true;
//     }

//     this->UpdateTriggerQueue("attack " + creatue_to_attack); // Update not using commands
// }

// /**
//  * @Author: Damini
//  **/

bool GameWorld::Put(string input)
{
    istringstream iss(input);
    vector<std::string> item_container((istream_iterator<std::string>(iss)), istream_iterator<std::string>());
    string item = item_container[0];
    string container = item_container[1];
    if(inventory_map_.find(item) != inventory_map_.end()) // If item in player's inventory
    {
    	Room *room_ptr = rooms_map_.at(current_room_);
    	//if statement to check if container exists in current room
    	if (find(room_ptr->containers_names_.begin(), room_ptr->containers_names_.end(), container) != room_ptr->containers_names_.end())
    	{
    		map<std::string, Container *>::iterator destination_container_ptr; // Pointer to the destination container obj.
    		destination_container_ptr = containers_map_.find(container);
    		if (find(destination_container_ptr->second->stored_items_.begin(), destination_container_ptr->second->stored_items_.end(), item) == destination_container_ptr->second->stored_items_.end())
    		{ // If item is not in the destination container
    			destination_container_ptr->second->stored_items_.push_back(item); // Add item to the stored items vector of the dest. container
        		cout << "Item" << item << " added to " << container << "." << endl;
        		inventory_map_.erase(item); // Remove item from user's inventory
    		}
    		else { // If item is already in the destination container (it would never reach this statement. Idk why I added it)
				#ifdef DEBUG
    			cout << "Item is already in " << container << endl;
				#endif
    		}
		}
    	else
    	{
    		#ifdef DEBUG
    		cout << "Cannot put item" << container << " is not in current room." << endl;
    		#endif
		}
     }
     else {
         cout << item << " is not in the players inventory." << endl;
         return false;
     }
     this->UpdateTriggerQueue(""); // Update not using commands
     return true;
 }

