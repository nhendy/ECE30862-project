//
// Created on 9/17/18.
//

#ifndef _HASCONDITION_H_
#define _HASCONDITION_H_

#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include "Condition.hpp"



class HasCondition: public Condition{

public:
    HasCondition(rapidxml::xml_node <> *);
    virtual ~HasCondition();
    virtual  bool isConditionSatisfied(GameWorld *);

};


#endif //_HASCONDITION_H_
