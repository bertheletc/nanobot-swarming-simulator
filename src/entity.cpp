#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>

#include "entity.h"

/* Implementation of abstract class "Entity" */

std::mutex Entity::_mtx;

// init static variable
int Entity::_idCnt = 0;

//std::mutex Entity::_mtx;

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

Entity::~Entity()
{
    // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });
}