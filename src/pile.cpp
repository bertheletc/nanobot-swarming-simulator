#include "pile.h"

Pile::Pile(int id, float bias, int pieces)
{
    _type = EntityType::kPile;
    _visualState = VisualState::kUnseen;
    _id = id;
    _bias = bias;
    _pieces = pieces;
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