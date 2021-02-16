#ifndef STATIC_H
#define STATIC_H

#include "world.h"

// abstract parent of Obstacle, Nest, and Heap classes
class Static 
{
public:
    // METHODS
    Static() {}; // Constructor
    
protected:
    virtual double bias() const = 0; // method to be overriden by each child class
}

#endif