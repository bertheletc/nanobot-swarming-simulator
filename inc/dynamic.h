#ifndef DYNAMIC_H
#define DYNAMIC_H

// abstract parent of Nanobot and Predator classes
class Dynamic 
{
public:
    //METHODS
    Dynamic(); // Constructor

protected:
    virtual void simulate(){}; // method to be overriden by each child class
    virtual void move(){}; // method to be overriden by each child class
    virtual void nextPosition(){};
    // TODO: decide whether these attributed are public or protected
    //std::vector<float> moveMatrix;
};

#endif