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

    virtual ~GameWorld();

    std::vector<Room*> rooms_;
    std::vector<Item*> items_;
    std::vector<Creature*> creatures_;
    std::vector<Container*> containers_;

    void static InitGameWorld();

private:
    GameWorld();


};
#endif //_GAMEWORLD_H_
