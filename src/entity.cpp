#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>

#include "entity.h"

/* Implementation of abstract class "Entity" */

// init static variable
int Entity::_idCnt = 0;

void Entity::setPosition(int x, int y)
{
    _posX = x;
    _posY = y;
}

void Entity::getPosition(int &x, int &y)
{
    x = _posX;
    y = _posY;
}

Entity::Entity()
{
    _type = EntityType::kNone;
    _id = _idCnt++;
}