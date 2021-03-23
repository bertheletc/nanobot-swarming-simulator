#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "entity.h"
#include "static.h"

// child of Entity and Static classes
// objects of this class represent the obstacles nanobots must avoid
class Obstacle : public Entity, public Static, public std::enable_shared_from_this<Obstacle>
{
public:
    // METHODS
    Obstacle(int id, int size, float bias); // Constructor
    // FUTURE IMPROVEMENTS: WASN'T ABLE TO IMPLEMENT IN TIME
    // // overriden methods from abstract Dynamic and Entity classes
    // void simulate();
    // void exist();

    // miscellaneous
    std::shared_ptr<Obstacle> get_shared_this() { return shared_from_this(); }
};

#endif