//
// Created on 9/17/18.
//

#ifndef _CREATURE_H_
#define _CREATURE_H_

#include "GameObjectModel.h"

class Creature : public GameObjectModel {

public:

    Creature(rapidxml::xml_node<> *);
    virtual ~Creature();

};


#endif //_CREATURE_H_
