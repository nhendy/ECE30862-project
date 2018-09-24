//
// Created on 9/17/18.
//

#ifndef _GAMEWORLD_H_
#define _GAMEWORLD_H_

#include <vector>
#include "Creature.hpp"
#include "Container.hpp"
#include "Item.hpp"
#include "Room.hpp"


class GameWorld {

public:

    GameWorld();
    virtual ~GameWorld();

    std::vector<Room*> rooms_;
    std::vector<Item*> items_;
    std::vector<Creature*> creatures_;
    std::vector<Container*> containers_;

    void static InitGameWorld();


};
#endif //_GAMEWORLD_H_
