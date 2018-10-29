//
// Created on 9/17/18.
//

#ifndef _ATTACK_H_
#define _ATTACK_H_
#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include <string>
#include <vector>
#include "Condition.hpp"
#include "Trigger.hpp"
// #include "GameWorld.hpp"

using namespace std;

class Attack: public Trigger
{

  public:
    Attack(rapidxml::xml_node<> *);
    Attack(rapidxml::xml_node<> *, string); //Overloaded constructor
    virtual ~Attack();
    virtual bool IsActivated(string, GameWorld &);

};

#endif //_ATTACK_H_
