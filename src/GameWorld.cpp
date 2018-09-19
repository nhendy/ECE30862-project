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
#include "../lib/pugixml-1.9/src/pugixml.hpp"

GameWorld::GameWorld() {}
GameWorld::~GameWorld() {}


//namespace fs = std::filesystem;
namespace fs = boost::filesystem;

void GameWorld::InitGameWorld() {
    //Find the xml file in the directory


//    for (auto & p : boost::filesystem::directory_iterator('./'))
//    {
//        std::cout << p << std::endl;
//    }
    fs::path p (".");

    fs::directory_iterator end_itr;
    boost::filesystem::path full_path( boost::filesystem::current_path() );
    std::cout << "Current path is : " << full_path << std::endl;

    // cycle through the directory
    for (fs::directory_iterator itr(p); itr != end_itr; ++itr)
    {
        // If it's not a directory, list it. If you want to list directories too, just remove this check.
        if (is_regular_file(itr->path())) {
            // assign current file name to current_file and echo it out to the console.
            std::string current_file = itr->path().string();
            std::cout << current_file << std::endl;
        }
    }


//    std::cout << "name" << " " << fs::file_size("sample.txt.xml") << '\n';
//    pugi::xml_document doc;

//    pugi::xml_parse_result result = doc.load_file("./sample.txt.xml");

//    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;


    //Parse it

    //Init all the

}

