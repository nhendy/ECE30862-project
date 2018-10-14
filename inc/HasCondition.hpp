//
// Created on 9/17/18.
//

#ifndef _HASCONDITION_H_
#define _HASCONDITION_H_

#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include "Condition.hpp"
#include <string>

using namespace std;

class HasCondition: public Condition{

public:
    HasCondition(rapidxml::xml_node <> *);
    virtual ~HasCondition();
    virtual  bool isConditionSatisfied(const GameWorld&);   ////POINTER!!!!!

private:
    string object_name_;
    bool has_;
    string owner_;

};


#endif //_HASCONDITION_H_
