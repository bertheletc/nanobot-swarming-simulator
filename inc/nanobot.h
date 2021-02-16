#ifndef NANOBOT_H
#define NANOBOT_H

enum BotMode 
{
    kNesting, 
    kSearching, 
    kReturning,
}; // 

// child of Static class
// objects of this class represent an individual nanobot
class Nanobot : public Entity, public Dynamic 
{
public:
    // Constructor
    Nanobot();
    double move() override; // overriden function to calculate movement
    void killed();

private:
    BotMode _mode;
    float _range;
}

#endif