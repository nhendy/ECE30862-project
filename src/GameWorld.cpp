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
GameWorld::~GameWorld() {}
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
        input_command = parse_input();

        if (pending_triggers_.empty())
        {
            execute(input_command);
        }

        for (auto it = pending_triggers_.begin(); it != pending_triggers_.end(); it++)
        {
            (*it)->fire(*this);
        }
    }

    cout << "Game Over" << endl;
}

/************************************** Trigger checking **********************************/
void GameWorld::update_trigger_queue(string input_command)
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
        if (trigger->is_activated(input_command, *this))
        {
            //enqueue to pending triggers
            this->pending_triggers_.push_back(trigger);
        }
    }

    //loop over inventory triggers
    for (auto &item_pair : inventory_map_)
    {
        for (Trigger *trigger : item_pair.second -> triggers_)
        {
            //check if trigger is activated
            if (trigger->is_activated(input_command, *this))
            {
                //enqueue to pending triggers
                this->pending_triggers_.push_back(trigger);
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
            if (trigger->is_activated(input_command, *this))
            {
                //enqueue to pending triggers
                this->pending_triggers_.push_back(trigger);
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
            if (trigger->is_activated(input_command, *this))
            {
                //enqueue to pending triggers
                this->pending_triggers_.push_back(trigger);
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
            if (trigger->is_activated(input_command, *this))
            {
                //enqueue to pending triggers
                this->pending_triggers_.push_back(trigger);
            }
        }
    }

}

/************************************** Parse Input **********************************/
string GameWorld::parse_input()
{
    string input = "";

    getline(cin, input);
    this->update_trigger_queue(input);

    return input;
}

/************************************** Executing input commands **********************************/

//TODO check if input_command is valid
bool GameWorld::execute(string input_command)
{
    if (input_command == "n" || input_command == "s" || input_command == "e" || input_command == "w")
    {
        return this->change_room(input_command);
    }
    if (input_command == "i")
    {
        return this->show_inventory();
    }
    if (input_command.find("take") != string::npos)
    {
        return this->take(input_command.substr(string("take").length() + 1));
    }
    if (input_command.find("open") != string::npos)
    {
        return this->open(input_command.substr(string("open").length() + 1));
    }
    if (input_command.find("read") != string::npos)
    {
        return this->read(input_command.substr(string("read").length() + 1));
    }
    if (input_command.find("drop") != string::npos)
    {
        return this->drop(input_command.substr(string("drop").length() + 1));
    }
    if (input_command.find("put") != string::npos)
    {
        return this->put(input_command.substr(string("put").length() + 1));
    }
    if (input_command.find("turn on") != string::npos)
    {
        return this->turnon(input_command.substr(string("turn on").length() + 1));
    }
    if (input_command.find("attack") != string::npos)
    {
        return this->attack(input_command.substr(string("attack").length() + 1));
    }

    return false;
}

/************************************** Commands **********************************/

/**
 * @Author: Damini
 **/
bool GameWorld::change_room(string)
{
    //TODO

    this->update_trigger_queue(""); // Update not using commands
}
bool GameWorld::show_inventory()
{

    this->update_trigger_queue(""); // Update not using commands
}

bool GameWorld::take(string)
{

    this->update_trigger_queue(""); // Update not using commands
}
bool GameWorld::open(string)
{

    this->update_trigger_queue(""); // Update not using commands
}
bool GameWorld::read(string)
{

    this->update_trigger_queue(""); // Update not using commands
}
bool GameWorld::drop(string)
{

    this->update_trigger_queue(""); // Update not using commands
}
bool GameWorld::turnon(string)
{

    this->update_trigger_queue(""); // Update not using commands
}
bool GameWorld::attack(string)
{

    this->update_trigger_queue(""); // Update not using commands
}
bool GameWorld::put(string)
{

    this->update_trigger_queue(""); // Update not using commands
}