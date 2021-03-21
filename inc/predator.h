#ifndef PREDATOR_H
#define PREDATOR_H

#include "entity.h"
#include "dynamic.h"

// child of Dynamic class
// objects of this class represent the moving predators that can kill nanobots
class Predator: public Entity, public std::enable_shared_from_this<Predator>
{
public:
    // Constructor
    Predator(int id, std::vector<int> worldSize);
    double bias();
    void simulate();
    void move();
    //double move() override; // overriden function to calculate movement

    // miscellaneous
    std::shared_ptr<Predator> get_shared_this() { return shared_from_this(); }

private:
    void randMoveChoice(int &x, int &y);
    std::vector<float> moveMatrix;
    
    float _huntSkill; // determines how likely a bot is to die when running into predator
    std::vector<int> _worldSize;
};

#endif