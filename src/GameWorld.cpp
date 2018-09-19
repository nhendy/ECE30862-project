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
#include "../lib/pugixml-1.9/src/pugixml.hpp"

GameWorld::GameWorld() {}
GameWorld::~GameWorld() {}


//namespace fs = std::filesystem;

void GameWorld::InitGameWorld() {
    //Find the xml file in the directory


//    for (auto & p : fs::directory_iterator('./'))
//    {
//        std::cout << p << std::endl;
//    }

    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file("sample.txt.xml");

    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;


    //Parse it

    //Init all the

}

