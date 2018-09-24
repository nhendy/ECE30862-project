//
// Created on 9/18/18.
//

#include "../inc/GameWorld.h"
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include <sstream>
#include "../lib/rapidxml-1.13/rapidxml.hpp"

GameWorld::GameWorld() {}
GameWorld::~GameWorld() {}


//namespace fs = std::filesystem;
namespace fs = boost::filesystem;

void GameWorld::InitGameWorld() {
    //Find the xml file in the directory

//    using namespace rapidxml;
//    using namespace std;
//
//    xml_document<> doc;
//    xml_node<> * root_node;
//    // Read the xml file into a vector
//    ifstream theFile ("sample.txt.xml");
//    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
//    buffer.push_back('\0');
//    // Parse the buffer using the xml file parsing library into doc
//    doc.parse<0>(&buffer[0]);
//    // Find our root node
//    root_node = doc.first_node("map");
//    // Iterate over the brewerys
//
//    for (xml_node<> * brewery_node = root_node->first_node("Brewery"); brewery_node; brewery_node = brewery_node->next_sibling())
//    {
//        printf("I have visited %s in %s. ",
//               brewery_node->first_attribute("name")->value(),
//               brewery_node->first_attribute("location")->value());
//        // Interate over the beers
//        for(xml_node<> * beer_node = brewery_node->first_node("Beer"); beer_node; beer_node = beer_node->next_sibling())
//        {
//            printf("On %s, I tried their %s which is a %s. ",
//                   beer_node->first_attribute("dateSampled")->value(),
//                   beer_node->first_attribute("name")->value(),
//                   beer_node->first_attribute("description")->value());
//            printf("I gave it the following review: %s", beer_node->value());
//        }
//        cout << endl;
//    }
//
//    theFile.close();

    using namespace rapidxml;
    using namespace std;

    xml_document <> doc;
    ifstream file ("sample.txt.xml");

    stringstream buffer ;
    buffer << file.rdbuf();
    file.close();
    string content(buffer.str());

    doc.parse<0>(&content[0]);
    xml_node<> *root_node = doc.first_node();


    for (xml_node<> * node = root_node -> first_node(); node; node =  node -> next_sibling() )
    {
        cout << node -> name() << endl;

        for (xml_node<> * inner_node = node -> first_node(); inner_node; inner_node =  inner_node -> next_sibling())
        {
            cout << inner_node -> name() << endl;
        }
        cout << endl;
    }




}

