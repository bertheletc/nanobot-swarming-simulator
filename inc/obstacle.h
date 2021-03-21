#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "entity.h"
#include "static.h"

// child of Static class
// objects of this class represent the obstacles nanobots must avoid
class Obstacle : public Entity
{
public:
    // METHODS
    // Constructor
    Obstacle();
    // TODO: find correct format for this function declaration
    //double bias() override; // overriden function to calculate the bias
    
    // ATTRIBUTES

private:
};

#endif