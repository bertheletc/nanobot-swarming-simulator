#include "obstacle.h"

Obstacle::Obstacle(int id, int size, float bias)
{
    _type = EntityType::kObstacle;
    _visualState = VisualState::kUnseen;
    _id = id;
    _sizeRadius = size;
    _bias = bias;
    _timeOn = 0;
    _color = cv::Scalar(0,0,0); // BLACK (b,g,r)
}

void Obstacle::simulate()
{
    // launch move function in a thread
    _threads.emplace_back(std::thread(&Obstacle::exist, this));
}

void Obstacle::exist()
{

}