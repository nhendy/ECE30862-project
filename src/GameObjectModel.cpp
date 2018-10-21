//
// Created 9/21/18.
//

#include "../inc/GameObjectModel.hpp"

GameObjectModel::GameObjectModel() {}
GameObjectModel::~GameObjectModel() 
{
    for(Trigger * trigger: triggers_)
    {
        delete trigger;
    }
}