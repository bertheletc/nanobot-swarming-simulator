#include <iostream>
#include <random>
#include <mutex>
#include "predator.h"

Predator::Predator(int id, std::vector<int> worldSize)
{
    _type = EntityType::kPredator;
    _id = id;

    _worldSize = worldSize;

    for (int i = 0; i < 9; i++)
    {
        moveMatrix.push_back(1.0/9.0);
    }
}

void Predator::simulate()
{
    // launch move function in a thread
    threads.emplace_back(std::thread(&Predator::move, this));
}

void Predator::move()
{
    // initalize variables
    double cycleDuration = 1000; // duration of a single simulation cycle in ms

    while (true)
    {
        // print id of the current thread
        std::unique_lock<std::mutex> lck(_mtx);
        std::cout << "Nanobot #" << _id << "::drive: thread id = " << std::this_thread::get_id() << std::endl;
        lck.unlock();

        int x, y;
        while(true)
        {
            randMoveChoice(x,y);
            if (x > 0  && x <= _worldSize[0] && y > 0 && y <= _worldSize[1])
            {
                this->setPosition(x,y);
                break;
            }
        }
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void Predator::randMoveChoice(int &x, int &y)
{
    int step = 2; // pixels
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d({moveMatrix[0], moveMatrix[1], moveMatrix[2], 
                                    moveMatrix[3], moveMatrix[4], moveMatrix[5], 
                                    moveMatrix[6], moveMatrix[7], moveMatrix[8]});
    switch(d(gen))
    {
        case 0:
            x = _posX - step;
            y = _posY - step;
            break;
        case 1:
            x = _posX;
            y = _posY - step;
            break;
        case 2:
            x = _posX + step;
            y = _posY - step;
            break;
        case 3:
            x = _posX - step;
            y = _posY;
            break;
        case 4:
            x = _posX;
            y = _posY;
            break;
        case 5:
            x = _posX + step;
            y = _posY;
            break;
        case 6:
            x = _posX - step;
            y = _posY + step;
            break;
        case 7:
            x = _posX;
            y = _posY + step;
            break;
        case 8:
            x = _posX + step;
            y = _posY + step;
            break;
    }
}