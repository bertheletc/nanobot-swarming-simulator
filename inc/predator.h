#ifndef PREDATOR_H
#define PREDATOR_H

#include "entity.h"
#include "dynamic.h"

// child of Dynamic class
// objects of this class represent the moving predators that can kill nanobots
class Predator: public Entity, public Dynamic, public std::enable_shared_from_this<Predator>
{
public:
    // Constructor
    Predator(int id, int size, std::vector<int> worldSize);
    double bias();
    void simulate();
    void move();
    //double move() override; // overriden function to calculate movement

    // miscellaneous
    std::shared_ptr<Predator> get_shared_this() { return shared_from_this(); }

private:    
    float _huntSkill; // determines how likely a bot is to die when running into predator
};

#endif