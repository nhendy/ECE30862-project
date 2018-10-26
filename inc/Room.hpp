//
// Created on 9/17/18.
//

#ifndef _ROOM_H_
#define _ROOM_H_

#include "GameObjectModel.hpp"
#include "../lib/rapidxml-1.13/rapidxml.hpp"

using namespace std;

class Room : public GameObjectModel {

public:


    Room(rapidxml::xml_node <> * room_node);
    virtual ~Room();
    friend ostream & operator<< (ostream&, const Room&);
    string type_ = "regular";
    map<string, string> direction_to_room_; //borders
    vector<string> containers_names_;
    vector<string> items_names_;
    vector<string> creatures_names_;


};

#endif //_ROOM_H_
