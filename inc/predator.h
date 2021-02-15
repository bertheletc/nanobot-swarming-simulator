#ifndef PREDATOR_H
#define PREDATOR_H

// child of Dynamic class
// objects of this class represent the moving predators that can kill nanobots
class Predator: public Dynamic {
public:
    // Constructor
    Predator();
    double bias();
    double move() override; // overriden function to calculate movement

private:
    float _huntSkill; // determines how likely a bot is to die when running into predator
}

#endif