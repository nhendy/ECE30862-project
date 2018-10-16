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

    std::map<string, Room*> rooms_;
    std::map<string, Item*> items_;
    std::map<string, Creature*> creatures_;
    std::map<string, Container*> containers_;
    std::map<string, Item*> inventory_;


    void GameLoop();

private:
    string current_room_;
    bool execute(string);
    bool is_overridden(string);
    bool change_room(string);
    bool show_inventory();
    bool take(string);
    bool open(string);
    bool read(string);
    bool drop(string);
    bool turnon(string);
    bool attack(string);
    bool put(string);



};
#endif //_GAMEWORLD_H_
