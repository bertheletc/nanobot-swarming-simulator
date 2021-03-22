#include "pile.h"

Pile::Pile(int id, float bias)
{
    _type = EntityType::kPile;
    _visualState = VisualState::kSeen;
    _bias = bias;
    _timeOn = 0;
}

void Pile::simulate()
{
    // launch move function in a thread
    _threads.emplace_back(std::thread(&Pile::exist, this));
}

void Pile::exist()
{

}