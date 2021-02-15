#ifndef STATIC_H
#define STATIC_H

#include "world.h"

enum class Color {kBlue, kGreen, kRed, kYellow, kOrange, kBlack}; //

// abstract parent of Obstacle, Nest, and Heap classes
class Static {
public:
    // METHODS
    Static() {}; // Constructor
    
protected:
    virtual double bias() const = 0; // method to be overriden by each child class
    // TODO: decide whether these attributed are public or protected
    // ATTRIBUTES
    // TODO: change this to a smart pointer because it will be accessed by many objects
    World *world; // pointer to instance of World that the Static object belongs to
    Color color; // rendered color of object
    // TODO: figure out units to use, pixels
    float pos_x; // x-coordinate of center position of object
    float pos_y; // y-coordinate of center position of object
    float sizeRadius; // represents the size of the object (all objects are circles) 
}

#endif