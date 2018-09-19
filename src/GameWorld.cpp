//
// Created on 9/18/18.
//

#include "../inc/GameWorld.h"
//#include "../lib/rapidxml-1.13/rapidxml.hpp"
//#include "../lib/rapidxml-1.13/rapidxml_iterators.hpp"
//#include "../lib/rapidxml-1.13/rapidxml_print.hpp"
//#include "../lib/rapidxml-1.13/rapidxml_utils.hpp"
#include <fstream>
#include <dirent.h>
#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include "../lib/rapidxml-1.13/rapidxml.hpp"
//#include "../lib/rapidxml-1.13/rapidxml_iterators.hpp"
//#include "../lib/rapidxml-1.13/rapidxml_print.hpp"
//#include "../lib/rapidxml-1.13/rapidxml_utils.hpp"
#include "../lib/pugixml-1.9/src/pugixml.hpp"

GameWorld::GameWorld() {}
GameWorld::~GameWorld() {}


//namespace fs = std::filesystem;
namespace fs = boost::filesystem;

void GameWorld::InitGameWorld() {
    //Find the xml file in the directory


////    for (auto & p : boost::filesystem::directory_iterator('./'))
////    {
////        std::cout << p << std::endl;
////    }
//    fs::path p (".");
//
//    fs::directory_iterator end_itr;
////    boost::filesystem::path full_path( boost::filesystem::current_path() );
////    std::cout << "Current path is : " << full_path << std::endl;
//
//    // cycle through the directory
//    for (fs::directory_iterator itr(p); itr != end_itr; ++itr)
//    {
//        // If it's not a directory, list it. If you want to list directories too, just remove this check.
//        if (is_regular_file(itr->path())) {
//            // assign current file name to current_file and echo it out to the console.
//            std::string current_file = itr->path().string();
//            std::cout << current_file << std::endl;
//        }
//    }
//
//
////    std::cout << "Size" << " " << fs::file_size("sample.txt.xml") << '\n';
////    pugi::xml_document doc;
////
////    pugi::xml_parse_result result = doc.load_file("./sample.txt.xml");
////
////    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("root").attribute("name").value() << std::endl;
//
//
//    //Parse it
//
//    //Init all the
    using namespace rapidxml;
    using namespace std;

    xml_document<> doc;
    xml_node<> * root_node;
    // Read the xml file into a vector
    ifstream theFile ("sample.txt.xml");
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>(&buffer[0]);
    // Find our root node
    root_node = doc.first_node("MyBeerJournal");
    // Iterate over the brewerys
    for (xml_node<> * brewery_node = root_node->first_node("Brewery"); brewery_node; brewery_node = brewery_node->next_sibling())
    {
        printf("I have visited %s in %s. ",
               brewery_node->first_attribute("name")->value(),
               brewery_node->first_attribute("location")->value());
        // Interate over the beers
        for(xml_node<> * beer_node = brewery_node->first_node("Beer"); beer_node; beer_node = beer_node->next_sibling())
        {
            printf("On %s, I tried their %s which is a %s. ",
                   beer_node->first_attribute("dateSampled")->value(),
                   beer_node->first_attribute("name")->value(),
                   beer_node->first_attribute("description")->value());
            printf("I gave it the following review: %s", beer_node->value());
        }
        cout << endl;
    }


}

