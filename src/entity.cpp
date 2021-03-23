#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>

#include "entity.h"

/* Implementation of abstract class "Entity" */

// static mutex declaration
std::mutex Entity::_mtx;

// init static variable
int Entity::_idCnt = 0;

// Constructor
Entity::Entity()
{
    _type = EntityType::kNone;
    _id = _idCnt++;
}

// Destructor
Entity::~Entity()
{
    // set up thread barrier before this object is destroyed
    std::for_each(_threads.begin(), _threads.end(), [](std::thread &t) {
        t.join();
    });
}

// getters and setters
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