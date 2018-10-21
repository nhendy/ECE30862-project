//
// Created on 9/17/18.
//

#ifndef _CREATURE_H_
#define _CREATURE_H_

#include "GameObjectModel.hpp"
#include <vector>

class Creature : public GameObjectModel {

public:

    Creature(rapidxml::xml_node<> *);
    virtual ~Creature();
    vector<string> vulnerabilities_;

};


#endif //_CREATURE_H_
