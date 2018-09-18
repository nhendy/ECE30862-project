//
// Created on 9/17/18.
//

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_


#include <string>
#include <vector>
#include "Trigger.h"

/**
 *
 */
class GameObjectModel {
public:

    string name_ = "";
    string status_ = "";
    string description_ = "";

    vector<Trigger* > triggers_;

    GameObjectModel();
    virtual  ~GameObjectModel();

};

#endif //_GAMEOBJECT_H_
