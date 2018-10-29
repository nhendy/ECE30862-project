//
// Created on 9/17/18.
//

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <vector>
#include "GameObjectModel.hpp"

class Container : public GameObjectModel {

public:

    Container(rapidxml::xml_node<> *);
    virtual ~Container();
    vector<string> accepted_;
    vector<string> stored_items_;
    bool is_open = false;
    friend ostream & operator<< (ostream&, const Container&);

};


#endif //_CONTAINER_H_
