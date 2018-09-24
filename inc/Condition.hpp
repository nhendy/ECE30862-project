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
    Condition();
    virtual ~Condition();
    virtual  bool isConditionSatisfied(GameWorld *) = 0;
};


#endif //CONDITION_H
