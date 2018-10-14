//
// Created on 9/17/18.
//

#ifndef CONTAINER_H_
#define CONTAINER_H_


#include "GameObjectModel.hpp"

class Container : public GameObjectModel {

public:

    Container(rapidxml::xml_node<> *);
    virtual ~Container();


};


#endif //_CONTAINER_H_
