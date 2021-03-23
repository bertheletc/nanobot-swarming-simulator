#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
#include "dynamic.h"

// choose random movement based on probaility matrix
void Dynamic::randMoveChoice(int &x, int &y, int posX, int posY, std::vector<float> moveMatrix)
{   
    // create a discrete distribution based on probability matrix
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d({moveMatrix[0], moveMatrix[1], moveMatrix[2], 
                                    moveMatrix[3], moveMatrix[4], moveMatrix[5], 
                                    moveMatrix[6], moveMatrix[7], moveMatrix[8]});
    // choose a movement based on the outcome of the random selection
    switch(d(gen))
    {
        case 0:
            x = posX - _step;
            y = posY - _step;
            break;
        case 1:
            x = posX;
            y = posY - _step;
            break;
        case 2:
            x = posX + _step;
            y = posY - _step;
            break;
        case 3:
            x = posX - _step;
            y = posY;
            break;
        case 4:
            x = posX;
            y = posY;
            break;
        case 5:
            x = posX + _step;
            y = posY;
            break;
        case 6:
            x = posX - _step;
            y = posY + _step;
            break;
        case 7:
            x = posX;
            y = posY + _step;
            break;
        case 8:
            x = posX + _step;
            y = posY + _step;
            break;
    }
}