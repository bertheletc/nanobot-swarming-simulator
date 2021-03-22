#include "nest.h"

Nest::Nest(int id, int size, float bias)
{
    _type = EntityType::kNest;
    _visualState = VisualState::kSeen;
    _id = id;
    _sizeRadius = size;
    _bias = bias;
    _timeOn = 0;
    _color = cv::Scalar(0,128,255); // ORANGE (b,g,r)
}