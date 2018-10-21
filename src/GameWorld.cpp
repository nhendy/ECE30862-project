//
// Created on 9/18/18.
//

#include "../inc/GameWorld.hpp"
#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include "boost/algorithm/string.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <dirent.h>

using namespace std;

/**************************** Constructors & destructors ****************************/

GameWorld::GameWorld() {}
GameWorld::~GameWorld() {}
bool GameWorld::InitGame() {
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

                rooms_.insert(pair<string, Room *>(name, room));
            }
            else if (node_name == "creature")
            {
                Creature *creature = new Creature(node);
                string name = creature->name_;

                creatures_.insert(pair<string, Creature *>(name, creature));
            }
            else if (node_name == "container")
            {
                Container *container = new Container(node);
                string name = container->name_;

                containers_.insert(pair<string, Container *>(name, container));
            }
            else if (node_name == "item")
            {
                Item *item = new Item(node);
                string name = item->name_;

                items_.insert(pair<string, Item *>(name, item));
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

    while (true)
    {
        getline(cin, input_command);

        if (is_overridden(input_command))
        {
            continue;
        }

        execute(input_command);
    }
}

/************************************** Trigger checking **********************************/
bool GameWorld::is_overridden(string input_command)
{
    //TODO

    return true;
}

/************************************** Executing input commands **********************************/
bool GameWorld::execute(string input_command)
{
    if (input_command == "n" || input_command == "s" || input_command == "e" || input_command == "w")
    {
        return this->change_room(input_command);
        ;
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
bool GameWorld::change_room(string direction) {
    if(direction == "n")
    {
        Room *ptr = rooms_.at(current_room_); 
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
        Room *ptr = rooms_.at(current_room_); 
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
        Room *ptr = rooms_.at(current_room_); 
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
        Room *ptr = rooms_.at(current_room_); 
        if(ptr->direction_to_room_.find("west") != ptr->direction_to_room_.end())
        {
            current_room_ = ptr->direction_to_room_["west"]; 
        }
        else{
            std::cout<<"Can’t go that way."<<std::endl;
        }
    }
    
}
bool GameWorld::show_inventory() {}
bool GameWorld::take(string) {}
bool GameWorld::open(string) {}
bool GameWorld::read(string) {}
bool GameWorld::drop(string) {}
bool GameWorld::turnon(string) {}
bool GameWorld::attack(string) {}
bool GameWorld::put(string) {}