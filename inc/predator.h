#ifndef PREDATOR_H
#define PREDATOR_H

#include "entity.h"
#include "dynamic.h"

// child of Entity and Dynamic class
// objects of this class represent the moving predators that can kill nanobots
class Predator: public Entity, public Dynamic, public std::enable_shared_from_this<Predator>
{
public:
    // METHODS
    Predator(int id, int size, std::vector<int> worldSize); // Constructor
    // overriden methods from abstract Dynamic and Entity classes
    void simulate();
    void move();

    // miscellaneous
    std::shared_ptr<Predator> get_shared_this() { return shared_from_this(); }
};

#endif