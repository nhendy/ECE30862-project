//
// Created on 9/17/18.
//

#ifndef _GAMEWORLD_H_
#define _GAMEWORLD_H_

#include <vector>
#include "Creature.h"
#include "Container.h"
#include "Item.h"
#include "Room.h"


class GameWorld {

public:

    GameWorld();
    virtual ~GameWorld();

    vector<Room*> rooms_;
    vector<Item*> items_;
    vector<Creature*> creatures_;
    vector<Containter*> containers_




};
#endif //_GAMEWORLD_H_
