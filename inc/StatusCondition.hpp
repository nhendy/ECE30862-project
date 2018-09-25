//
// Created on 9/17/18.
//

#ifndef _STATUSCONDITION_H_
#define _STATUSCONDITION_H_

#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include "Condition.hpp"
#include <string>

using namespace std;

class StatusCondition : public Condition{

public:
    StatusCondition(rapidxml::xml_node <> *);
    virtual ~StatusCondition();
    virtual bool isConditionSatisfied(GameWorld *);

private:
    string object_name_;
    string object_status_;

};


#endif //_STATUSCONDITION_H_
