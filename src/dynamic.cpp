#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
#include "dynamic.h"

std::mutex Dynamic::_mtx;

Dynamic::Dynamic()
{
    for (int i = 0; i < 9; i++)
    {
        _moveMatrix.push_back(1.0/9.0);
    }
}

Dynamic::~Dynamic()
{
    // set up thread barrier before this object is destroyed
    std::for_each(_threads.begin(), _threads.end(), [](std::thread &t) {
        t.join();
    });
}

void Dynamic::randMoveChoice(int &x, int &y, int posX, int posY)
{
    int step = 2; // pixels
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d({_moveMatrix[0], _moveMatrix[1], _moveMatrix[2], 
                                    _moveMatrix[3], _moveMatrix[4], _moveMatrix[5], 
                                    _moveMatrix[6], _moveMatrix[7], _moveMatrix[8]});
    switch(d(gen))
    {
        case 0:
            x = posX - step;
            y = posY - step;
            break;
        case 1:
            x = posX;
            y = posY - step;
            break;
        case 2:
            x = posX + step;
            y = posY - step;
            break;
        case 3:
            x = posX - step;
            y = posY;
            break;
        case 4:
            x = posX;
            y = posY;
            break;
        case 5:
            x = posX + step;
            y = posY;
            break;
        case 6:
            x = posX - step;
            y = posY + step;
            break;
        case 7:
            x = posX;
            y = posY + step;
            break;
        case 8:
            x = posX + step;
            y = posY + step;
            break;
    }
}