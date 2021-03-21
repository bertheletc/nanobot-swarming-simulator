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
    ~Dynamic();

protected:
    virtual void simulate(){}; // method to be overriden by each child class
    virtual void move(){}; // method to be overriden by each child class
    // TODO: decide whether these attributed are public or protected
    void randMoveChoice(int &x, int &y, int posX, int posY);

    std::vector<float> _moveMatrix;
    std::vector<int> _worldSize;
    std::vector<std::thread> _threads; // holds all threads that have been launched within this object
    static std::mutex _mtx;           // mutex shared by all traffic objects for protecting cout 
};

#endif