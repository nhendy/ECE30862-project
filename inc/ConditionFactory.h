//
// Created on 9/17/18.
//

#ifndef _CONTIONFACTORY_H_
#define _CONTIONFACTORY_H_

#include "Condition.h"
#include "../lib/rapidxml-1.13/rapidxml.hpp"

using namespace std;


struct ConditionFactory {

    static Condition * createCondition(rapidxml::xml_node<> *);

};


#endif //_CONTIONFACTORY_H_
