//
// Created on 9/17/18.
//

#ifndef _ITEM_H_
#define _ITEM_H_

#include "GameObjectModel.hpp"
class Item : public GameObjectModel{

public:
    Item(rapidxml::xml_node<> *);
    virtual ~Item();

};


#endif //_ITEM_H_
