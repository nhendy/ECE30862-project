//
// Created by Noureldin Hendy on 9/23/18.
//

#ifndef CONDITION_H
#define CONDITION_H

class GameWorld;


class Condition {

public:
    Condition();
    virtual ~Condition();
    virtual  bool isConditionSatisfied(GameWorld *) = 0;
};


#endif //CONDITION_H
