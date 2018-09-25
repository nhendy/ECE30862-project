//
// Created on 9/17/18.
//

#ifndef _ITEM_H_
#define _ITEM_H_


#include <string>
#include <vector>
#include "GameObjectModel.hpp"
#include "../lib/rapidxml-1.13/rapidxml.hpp"


class Item : public GameObjectModel{

public:
    Item(rapidxml::xml_node<> *);
    virtual ~Item();

    std::string writing_;
    std::vector<string> messages_;
    std::vector<string> actions_;

private:
    void buildTrunOn(rapidxml::xml_node<> *);

};


#endif //_ITEM_H_
