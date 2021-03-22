#include "obstacle.h"

Obstacle::Obstacle(int id, float bias)
{
    _type = EntityType::kObstacle;
    _visualState = VisualState::kSeen;
    _bias = bias;
    _timeOn = 0;
}

void Obstacle::simulate()
{
    // launch move function in a thread
    _threads.emplace_back(std::thread(&Obstacle::exist, this));
}

void Obstacle::exist()
{

}