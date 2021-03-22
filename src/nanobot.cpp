#include <iostream>
#include <random>
#include <mutex>
#include <cmath>
#include <thread>
#include <numeric>
#include "nanobot.h"
#include "static.h"

Nanobot::Nanobot(std::vector<std::shared_ptr<Nest>> &nests,
            std::vector<std::shared_ptr<Obstacle>> &obstacles,
            std::vector<std::shared_ptr<Pile>> &piles,
            std::vector<std::shared_ptr<Predator>> &predators,
            int id, int size, std::vector<int> worldSize, int range)
{
    _nests = nests;
    _obstacles = obstacles;
    _piles = piles;
    _predators = predators;
    
    _type = EntityType::kNanobot;
    _mode = BotMode::kNesting;
    _color = cv::Scalar(255,0,0); // BLUE (b,g,r)
    _id = id;
    _sizeRadius = size;
    _worldSize = worldSize;
    _range = range;
}

void Nanobot::simulate()
{
    // launch move function in a thread
    _threads.emplace_back(std::thread(&Nanobot::move, this));
}

void Nanobot::move()
{
    // initalize variables
    double cycleDuration = 1000; // duration of a single simulation cycle in ms

    while (true)
    {
        // //print id of the current thread
        // std::unique_lock<std::mutex> lck(_mtx);
        // std::cout << "Nanobot #" << _id << "::drive: thread id = " << std::this_thread::get_id() << std::endl;
        // lck.unlock();

        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
       
        int x, y;
        std::vector<float> biasedMoveMatrix = this->calcBiasMoveMatrix();

        this->randMoveChoice(x,y,_posX,_posY,biasedMoveMatrix);

        // check if interfereing with other objects
        if (this->checkDetection(x,y))
        {
            this->setPosition(x,y);
        } 
        // if no interference, check if the move is in bounds
        else if (x > 0  && x <= _worldSize[0] && y > 0 && y <= _worldSize[1])
        {
            this->setPosition(x,y);
        }
    }
}

int Nanobot::calcEuclideanDist(int x, int y)
{
    return sqrt(pow((x-_posX),2) + pow((y-_posY),2));
}

int Nanobot::calcRepelBiasDirection(int x, int y)
{
    //[0,1,2
    // 3,4,5
    // 6,7,8]

    int xdiff, ydiff;
    xdiff = _posX - x;
    ydiff = _posY - y;

    if (xdiff>0 && ydiff>0) {
        return 8;
    } else if (xdiff<0 && ydiff>0) {
        return 6;
    } else if (xdiff>0 && ydiff<0) {
        return 2;
    } else if (xdiff<0 && ydiff<0) {
        return 0;
    } else if (xdiff==0 && ydiff>0) {
        return 7;
    } else if (xdiff>0 && ydiff==0) {
        return 5;
    } else if (xdiff<0 && ydiff==0) {
        return 3;
    } else if (xdiff==0 && ydiff<0) {
        return 1;
    } else {
        return 0;
    }
}

int Nanobot::calcAttractBiasDirection(int x, int y)
{
    //[0,1,2
    // 3,4,5
    // 6,7,8]

    int xdiff, ydiff;
    xdiff = _posX - x;
    ydiff = _posY - y;

    if (xdiff>0 && ydiff>0) {
        return 0;
    } else if (xdiff<0 && ydiff>0) {
        return 2;
    } else if (xdiff>0 && ydiff<0) {
        return 6;
    } else if (xdiff<0 && ydiff<0) {
        return 8;
    } else if (xdiff==0 && ydiff>0) {
        return 1;
    } else if (xdiff>0 && ydiff==0) {
        return 3;
    } else if (xdiff<0 && ydiff==0) {
        return 5;
    } else if (xdiff==0 && ydiff<0) {
        return 7;
    } else {
        return 0;
    }
}

void Nanobot::normalizeMoveMatrix(std::vector<float> &biasedMoveMatrix)
{
    float average = accumulate(biasedMoveMatrix.begin(), biasedMoveMatrix.end(), 0.0);

    for (float n : biasedMoveMatrix)
    {
        n /= average;
    }
}

std::vector<float> Nanobot::calcBiasMoveMatrix()
{
    std::vector<float> biasedMoveMatrix(9, 1.0);

    //std::lock_guard<std::mutex> uLock(_mutex);
    //std::unique_lock<std::mutex> lck(_mutex);

    for (auto it : _obstacles)
    {
        if (it->getVisualState() == VisualState::kSeen)
        {
            int ox, oy;
            it->getPosition(ox,oy);
            if (this->calcEuclideanDist(ox,oy) < _range)
            {
                biasedMoveMatrix[this->calcRepelBiasDirection(ox,oy)] += it->getBias();
            }
        }
    }

    for (auto it : _piles)
    {
        if (it->getVisualState() == VisualState::kSeen)
        {
            int px, py;
            it->getPosition(px,py);
            if (this->calcEuclideanDist(px,py) < _range)
            {
                biasedMoveMatrix[this->calcAttractBiasDirection(px,py)] += it->getBias();
            }
        }
    }

    normalizeMoveMatrix(biasedMoveMatrix);

    return biasedMoveMatrix;
}

bool Nanobot::checkDetection(int &x, int &y)
{
    //std::lock_guard<std::mutex> uLock(_mutex);
    //std::unique_lock<std::mutex> lck(_mutex);

    for (auto it : _obstacles)
    {
        int ox, oy;
        it->getPosition(ox,oy);
        if (this->calcEuclideanDist(ox,oy) < (_sizeRadius + it->getSizeRadius()))
        {
            this->moveAwayFrom(x, y, ox, oy);
            return true;
        }
    }

    for (auto it : _piles)
    {
        int px, py;
        it->getPosition(px,py);
        if (this->calcEuclideanDist(px,py) < (_sizeRadius + it->getSizeRadius()))
        {
            this->moveAwayFrom(x, y, px, py);
            return true;
        }
    }

    return false;
}

void Nanobot::moveAwayFrom(int &x, int &y, int &xAway, int &yAway)
{
    //[0,1,2
    // 3,4,5
    // 6,7,8]

    int xdiff, ydiff;
    xdiff = _posX - xAway;
    ydiff = _posY - yAway;

    if (xdiff>0 && ydiff>0) {
        x = _posX + 1;
        y = _posY + 1;
    } else if (xdiff<0 && ydiff>0) {
        x = _posX - 1;
        y = _posY + 1;
    } else if (xdiff>0 && ydiff<0) {
        x = _posX + 1;
        y = _posY - 1;
    } else if (xdiff<0 && ydiff<0) {
        x = _posX - 1;
        y = _posY - 1;
    } else if (xdiff==0 && ydiff>0) {
        x = _posX;
        y = _posY + 1;
    } else if (xdiff>0 && ydiff==0) {
        x = _posX + 1;
        y = _posY;
    } else if (xdiff<0 && ydiff==0) {
        x = _posX - 1;
        y = _posY;
    } else if (xdiff==0 && ydiff<0) {
        x = _posX;
        y = _posY - 1;
    } else {
        x = _posX;
        y = _posY;
    }
}