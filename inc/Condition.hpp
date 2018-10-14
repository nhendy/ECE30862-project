//
// Created 9/23/18.
//

#ifndef CONDITION_H
#define CONDITION_H



/**
 *  Used forward declaration since file inclusion failed for some unknown reason TODO
 */
class GameWorld;


class Condition {
public:
    virtual  bool isConditionSatisfied(const GameWorld&) = 0;
};


#endif //CONDITION_H
