//
// Created 9/23/18.
//

#ifndef CONDITION_H
#define CONDITION_H



/**
 *  Used forward declaration since file inclusion failed for some unknown reason TODO
 */
class GameWorld;
// #include "GameWorld.hpp"


class Condition {
public:
    virtual  bool IsConditionSatisfied(const GameWorld &) = 0;
    virtual ~Condition(){};
};


#endif //CONDITION_H
