#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "entity.h"
#include "static.h"

// child of Static class
// objects of this class represent the obstacles nanobots must avoid
class Obstacle : public Entity, public std::enable_shared_from_this<Obstacle>
{
public:
    // METHODS
    // Constructor
    Obstacle();
    // TODO: find correct format for this function declaration
    //double bias() override; // overriden function to calculate the bias

    // miscellaneous
    std::shared_ptr<Obstacle> get_shared_this() { return shared_from_this(); }

    // ATTRIBUTES

private:
};

#endif