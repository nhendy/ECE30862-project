//
// Created on 9/17/18.
//

#ifndef _TRIGGER_H_
#define _TRIGGER_H_
#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include <string>
#include <vector>
#include "Condition.hpp"


using namespace std;

class Trigger {

public:

    Trigger(rapidxml::xml_node<> *);
    virtual ~Trigger();

    string type_ = "single";
    string command_;
    vector<Condition* > conditions_;
    vector<string> actions_;
    vector<string> messages_;




};


#endif //_TRIGGER_H_
