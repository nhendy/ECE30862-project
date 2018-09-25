//
// Created on 9/17/18.
//

#ifndef _STATUSCONDITION_H_
#define _STATUSCONDITION_H_

#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include "Condition.hpp"

class StatusCondition : public Condition{

public:
    StatusCondition(rapidxml::xml_node <> *);
    virtual ~StatusCondition();
    virtual bool isConditionSatisfied(GameWorld *);

};


#endif //_STATUSCONDITION_H_
