#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <thread>
#include <mutex>

// abstract parent of Nanobot and Predator classes
class Dynamic 
{
public:
    //METHODS
    Dynamic() {}; // Constructor

protected:
    //METHODS
    virtual void move(){}; // method to be overriden by each child class
    void randMoveChoice(int &x, int &y, int posX, int posY, std::vector<float> moveMatrix); // choose random movement based on probaility matrix

    // ATTRIBUTES
    std::vector<int> _worldSize; // holds bounds of the world so dynamic entities stay confined
    int _step; // describes amount of pixels dynamic entity moves per iteration
    std::vector<float> _uniformMoveMatrix{(1.0/9.0),(1.0/9.0),(1.0/9.0),
                                          (1.0/9.0),(1.0/9.0),(1.0/9.0),
                                          (1.0/9.0),(1.0/9.0),(1.0/9.0)}; // move matrix with all probabilities even
};

#endif