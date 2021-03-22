#include "pile.h"

Pile::Pile(int id, int size, float bias, int pieces)
{
    _type = EntityType::kPile;
    _visualState = VisualState::kSeen;
    _stock = PileStock::kFilled;
    _color = cv::Scalar(0,255,255); // YELLOW (b,g,r)
    _id = id;
    _sizeRadius = size;
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