#include <iostream>
#include <random>
#include <mutex>
#include "predator.h"

Predator::Predator(int id, int size, std::vector<int> worldSize)
{
    _type = EntityType::kPredator;
    _id = id;
    _sizeRadius = size;
    _color = cv::Scalar(0,0,255); // RED (b,g,r)
    _worldSize = worldSize;
    _flag = false;
    _step = 1;
}

void Predator::simulate()
{
    // launch move function in a thread
    _threads.emplace_back(std::thread(&Predator::move, this));
}

void Predator::move()
{
    // initalize variables
    double cycleDuration = 1000; // duration of a single simulation cycle in ms

    while (true)
    {   
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        int x, y;
        randMoveChoice(x,y,_posX,_posY,_uniformMoveMatrix);
        if (x > 0  && x <= _worldSize[0] && y > 0 && y <= _worldSize[1])
        {
            this->setPosition(x,y);
        }
    }
}