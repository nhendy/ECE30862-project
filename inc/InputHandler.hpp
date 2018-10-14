//
// Created by Noureldin Hendy on 10/8/18.
//

#ifndef _INPUTHANDLER_HPP
#define _INPUTHANDLER_HPP

#include "GameWorld.hpp"

class InputHandler {

public:
    InputHandler(GameWorld&);
    virtual ~InputHandler();
    bool       change_room(string);
    bool       show_inventory();
    bool       take(string);
    bool       open(string);
    bool       read(string);
    bool       drop(string);
    bool       put(string);
    bool       turnon(string);
    bool       attack(string);

private:
    GameWorld& gameworld_;
    

};

#endif //_INPUTHANDLER_HPP
