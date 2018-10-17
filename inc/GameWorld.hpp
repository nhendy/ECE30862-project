//
// Created on 9/17/18.
//

#ifndef _GAMEWORLD_H_
#define _GAMEWORLD_H_

#include <vector>
#include <map>
#include <string>
#include "Creature.hpp"
#include "Item.hpp"
#include "Room.hpp"
#include "Container.hpp"


class GameWorld
{

  public:
    GameWorld();
    virtual ~GameWorld();

    std::map<std::string, Room *> rooms_;
    std::map<std::string, Item *> items_;
    std::map<std::string, Creature *> creatures_;
    std::map<std::string, Container *> containers_;
    std::map<std::string, Item *> inventory_;

    void GameLoop();
    bool InitGame();

  private:
    std::string current_room_;
    std::vector<Trigger *> pending_triggers_;

    std::string parse_input();
    bool execute(std::string);
    Trigger *update_trigger_queue(std::string);
    bool change_room(std::string);
    bool show_inventory();
    bool take(std::string);
    bool open(std::string);
    bool read(std::string);
    bool drop(std::string);
    bool turnon(std::string);
    bool attack(std::string);
    bool put(std::string);
};
#endif //_GAMEWORLD_H_
