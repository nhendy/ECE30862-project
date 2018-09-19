//
// Created on 9/17/18.
//

#ifndef _ROOM_H_
#define _ROOM_H_

#include "GameObjectModel.h"
#include "Item.h"
#include "Creature.h"


class Room : public GameObjectModel {

    Room();
    virtual ~Room();


    std::string type_;
    std::vector<Room *> borders_;  //assuming borders will be rooms
    std::vector<Container *> containers_;
    std::vector<Item *> items_;
    std::vector<Creature *> creatures_;




};


#endif //_ROOM_H_
