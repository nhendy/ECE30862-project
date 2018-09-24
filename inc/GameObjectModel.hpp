//
// Created on 9/17/18.
//



#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_


#include <string>
#include <vector>
#include <map>
#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include "Trigger.hpp"


class GameObjectModel {
public:

    std::string name_ = "";
    std::string status_ = "";
    std::string description_ = "";

    std::vector<Trigger* > triggers_;

    GameObjectModel();
    virtual  ~GameObjectModel();

};

#endif //_GAMEOBJECT_H_
