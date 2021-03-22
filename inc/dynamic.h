#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <thread>
#include <mutex>

// abstract parent of Nanobot and Predator classes
class Dynamic 
{
public:
    //METHODS
    Dynamic(); // Constructor

protected:
    virtual void move(){}; // method to be overriden by each child class
    // TODO: decide whether these attributed are public or protected
    void randMoveChoice(int &x, int &y, int posX, int posY, std::vector<float> moveMatrix);

    std::vector<int> _worldSize;

    std::vector<float> _uniformMoveMatrix{(1.0/9.0),(1.0/9.0),(1.0/9.0),
                                          (1.0/9.0),(1.0/9.0),(1.0/9.0),
                                          (1.0/9.0),(1.0/9.0),(1.0/9.0)};
};

#endif