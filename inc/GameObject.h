//
// Created on 9/17/18.
//

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_


#include <string>
#include <vector>
#include <Trigger.h>

/**
 *
 */
class GameObject {
public:

    string name = "";
    string status = "";
    string description = "";

    vector<Trigger* > triggers;

    GameObject();
    virtual  ~GameObject();

};

#endif //_GAMEOBJECT_H_
