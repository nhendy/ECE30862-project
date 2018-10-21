//
// Created on 9/17/18.
//

#ifndef _GAMEWORLD_H_
#define _GAMEWORLD_H_

#include <vector>
#include <list>
#include <queue>
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
    bool game_over_ = false;
    std::string current_room_;

    std::map<std::string, Room *> rooms_map_;
    std::map<std::string, Item *> items_map_;
    std::map<std::string, Creature *> creatures_map_;
    std::map<std::string, Container *> containers_map_;
    std::map<std::string, Item *> inventory_map_;
    std::map<std::string, std::string> name_to_type_; //Map names to types

    void GameLoop();
    bool InitGame();

  private:
    
    std::queue<Trigger *> pending_triggers_;

    std::string ParseInput();
    bool Execute(std::string);
    void UpdateTriggerQueue(std::string);
    bool ChangeRoom(std::string);
    bool ShowInventory();
    bool Take(std::string);
    bool Open(std::string);
    bool Read(std::string);
    bool Drop(std::string);
    bool Turnon(std::string);
    bool Attack(std::string);
    bool Put(std::string);
};
#endif //_GAMEWORLD_H_
