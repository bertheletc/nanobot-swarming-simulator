#ifndef STATIC_H
#define STATIC_H

// abstract parent of Obstacle, Nest, and Heap classes
class Static 
{
public:
    // METHODS
    Static() {}; // Constructor
    
protected:
    virtual double bias(){}; // method to be overriden by each child class
};

#endif