#include "nest.h"

Nest::Nest(int id, float bias)
{
    _type = EntityType::kNest;
    _visualState = VisualState::kSeen;
    _bias = bias;
    _timeOn = 0;
}