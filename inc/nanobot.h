#ifndef NANOBOT_H
#define NANOBOT_H

#include "entity.h"
#include "dynamic.h"

enum BotMode 
{
    kNesting, 
    kSearching, 
    kReturning,
}; // 

// child of Dynamic and Entity classes
// objects of this class represent an individual nanobot
class Nanobot : public Entity, public Dynamic, public std::enable_shared_from_this<Nanobot>
{
public:
    // Constructor
    Nanobot(int id, std::vector<int> worldSize);
    void simulate();
    void move();
    void killed();

    // miscellaneous
    std::shared_ptr<Nanobot> get_shared_this() { return shared_from_this(); }

private:
    BotMode _mode;
    float _range;
    std::vector<int> _worldSize;
};

#endif