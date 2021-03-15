#ifndef NANOBOT_H
#define NANOBOT_H

#include "entity.h"

enum BotMode 
{
    kNesting, 
    kSearching, 
    kReturning,
}; // 

// child of Static class
// objects of this class represent an individual nanobot
class Nanobot : public Entity, public std::enable_shared_from_this<Nanobot>
{
public:
    // Constructor
    Nanobot();
    //double move() override; // overriden function to calculate movement
    void killed();
    void move();
    void simulate();

    // miscellaneous
    std::shared_ptr<Nanobot> get_shared_this() { return shared_from_this(); }

private:
    BotMode _mode;
    float _range;
};

#endif