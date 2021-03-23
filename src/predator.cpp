#include <iostream>
#include <random>
#include <mutex>
#include "predator.h"

// Constructor
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

// overriden methods from abstract Dynamic and Entity classes

void Predator::simulate()
{
    // launch move function in a thread
    _threads.emplace_back(std::thread(&Predator::move, this));
}

void Predator::move()
{
    // repeating loop to move predator entities until simulation is complete
    while (true)
    {   
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // choose random movement based on uniform probability matrix and update predator position
        int x, y;
        this->randMoveChoice(x,y,_posX,_posY,_uniformMoveMatrix);
        if (x > 0  && x <= _worldSize[0] && y > 0 && y <= _worldSize[1])
        {
            this->setPosition(x,y);
        }
    }
}