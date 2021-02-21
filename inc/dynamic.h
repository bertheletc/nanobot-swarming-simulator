#ifndef DYNAMIC_H
#define DYNAMIC_H

// abstract parent of Nanobot and Predator classes
class Dynamic 
{
public:
    //METHODS
    Dynamic(); // Constructor

protected:
    virtual double move(){}; // method to be overriden by each child class
    // TODO: decide whether these attributed are public or protected
};

#endif