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

using namespace std;

GameWorld::GameWorld(): handler_(*this){

    using namespace std;


    rapidxml::xml_document <> doc;
    ifstream file ("sample.txt.xml");

    stringstream buffer ;
    buffer << file.rdbuf();
    string content(buffer.str());

    doc.parse<0>(&content[0]);
    rapidxml::xml_node<> *root_node = doc.first_node("map");


    for (rapidxml::xml_node<> * node = root_node -> first_node(); node; node =  node -> next_sibling())
    {
        string node_name = node -> name();

        if(node_name == "room") {
            Room * room = new Room(node);
            string name = room -> name_;

            rooms_.insert(pair<string, Room*>(name, room));
        }
        else if (node_name == "creature") {
            Creature* creature = new Creature(node);
            string name = creature -> name_;

            creatures_.insert(pair<string, Creature*> (name, creature));
        }
        else if (node_name == "container") {
            Container* container = new Container(node);
            string name = container -> name_;

            containers_.insert(pair<string, Container*> (name, container));
        }
        else if (node_name == "item") {
            Item* item = new Item(node);
            string name = item -> name_;

            items_.insert(pair<string, Item*> (name, item));
        }

    }

    file.close();
}


void GameWorld::GameLoop()
{
    string input_command;

    while(true)
    {
        getline(cin, input_command);

        if(is_overridden(input_command))
        {
            continue;
        }

        execute(input_command);
    }

}


bool GameWorld::is_overridden(string input_command)
{
    //TODO
    return true;
}

bool GameWorld::execute(string input_command)
{
    if(input_command == "n" || input_command == "s" || input_command == "e" || input_command == "w")
    {
        return handler_.change_room(input_command);;
    }
    if(input_command == "i")
    {
        return handler_.show_inventory();
    }
    if(input_command.find("take") != string::npos)
    {
        return handler_.take(input_command.substr(string("take").length() + 1));
    }
    if(input_command.find("open") != string::npos)
    {
        return handler_.open(input_command.substr(string("open").length() + 1));
    }
    if(input_command.find("read") != string::npos)
    {
        return handler_.read(input_command.substr(string("read").length() + 1));
    }
    if(input_command.find("drop") != string::npos)
    {
        return handler_.drop(input_command.substr(string("drop").length() + 1));
    }
    if(input_command.find("put") != string::npos)
    {

        return handler_.put(input_command.substr(string("put").length() + 1));
    }
    if(input_command.find("turn on") != string::npos)
    {

        return handler_.turnon(input_command.substr(string("turn on").length() + 1));
    }
    if(input_command.find("attack") != string::npos)
    {

        return handler_.attack(input_command.substr(string("attack").length() + 1));
    }
}


GameWorld::~GameWorld() {}



