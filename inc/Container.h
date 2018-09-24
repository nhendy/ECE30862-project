//
// Created on 9/17/18.
//

#ifndef _CONTAINER_H_

#define _CONTAINER_H_

#include "GameObjectModel.h"
class Container : public GameObjectModel {

public:

    Container(rapidxml::xml_node<> *);
    virtual ~Container();

};


#endif //_CONTAINER_H_
