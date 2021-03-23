#include <iostream>
#include <random>
#include <mutex>
#include <cmath>
#include <thread>
#include <numeric>
#include "nanobot.h"
#include "static.h"

// Constructor
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
    _color = cv::Scalar(255,0,157); // PURPLE (b,g,r)
    _id = id;
    _sizeRadius = size;
    _worldSize = worldSize;
    _range = range;
    _flag = false;
    _step = 3;
}

// overriden methods from abstract Dynamic and Entity classes

void Nanobot::simulate()
{
    // launch move function in a thread
    _threads.emplace_back(std::thread(&Nanobot::move, this));
}

void Nanobot::move()
{
    // repeating loop to move nanobot entities until simulation is complete
    while (true)
    {
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        
        // nanobot behavior if it is still in the nest 
        if (_mode == BotMode::kNesting)
        {
            // choose random movement based on uniform probability matrix and update nanobot position
            int x, y;
            this->randMoveChoice(x,y,_posX,_posY,_uniformMoveMatrix);
            if (x > 0  && x <= _worldSize[0] && y > 0 && y <= _worldSize[1])
            {
                this->setPosition(x,y);
            }

            // check if nanobot has made it out of nest and change mode if it has
            if (checkIfOutOfNest())
            {
                _mode = BotMode::kSearching;
                _color = cv::Scalar(255,0,0); // BLUE (b,g,r)
            }
        } 
        // nanobot behavior if it is searching for the pile
        else if (_mode == BotMode::kSearching)
        {
            // choose random movement based on biased probability matrix and update nanobot position
            int x, y;
            std::vector<float> searchingMoveMatrix = this->calcSearchingMoveMatrix();
            EntityType detectedEntity = EntityType::kNone;

            this->randMoveChoice(x,y,_posX,_posY,searchingMoveMatrix);

            // check if interfereing with other objects
            if (this->checkDetection(x,y,detectedEntity))
            {
                this->setPosition(x,y);
                // if the nanobot detected a Pile entity then switch it to returning to the nest
                if (detectedEntity == EntityType::kPile)
                {
                    _mode = BotMode::kReturning;
                    _color = cv::Scalar(255,0,255); // PINK (b,g,r)
                    _step = 1;
                }
                // if the nanobot detected a Pile entity then switch it to DEAD
                if (detectedEntity == EntityType::kPredator)
                {
                    //print id of the current thread
                    std::unique_lock<std::mutex> lck(_mtx);
                    std::cout << "NANOBOT KILLED!" << std::endl;
                    lck.unlock();
                    _mode = BotMode::kDead;
                    _color = cv::Scalar(160,160,160); // GREY (b,g,r)
                }
            } 
            // if no interference, check if the move is in bounds
            else if (x > 0  && x <= _worldSize[0] && y > 0 && y <= _worldSize[1])
            {
                this->setPosition(x,y);
            }
        } 
        // nanobot behavior if it is returning a piece to the nest
        else if (_mode == BotMode::kReturning)
        {
            // choose random movement based on biased probability matrix and update nanobot position
            int x, y;
            std::vector<float> returningMoveMatrix = this->calcReturningMoveMatrix();
            EntityType detectedEntity = EntityType::kNone;

            this->randMoveChoice(x,y,_posX,_posY,returningMoveMatrix);

            // check if interfereing with other objects
            if (this->checkDetection(x,y,detectedEntity))
            {
                this->setPosition(x,y);
                // if the nanobot detected a Nest entity then switch it to searching for the pile
                if (detectedEntity == EntityType::kNest)
                {
                    _mode = BotMode::kSearching;
                    _color = cv::Scalar(255,0,0); // BLUE (b,g,r)
                    _step = 3;
                }
            } 
            // if no interference, check if the move is in bounds
            else if (x > 0  && x <= _worldSize[0] && y > 0 && y <= _worldSize[1])
            {
                this->setPosition(x,y);
            }
        } 
        // nanobot behavior if it has been killed by a predator
        else
        {
            // NANOBOT BOT IS DEAD
            this->setPosition(0,0);
        }
    }
}

// calculate the Euclidean distance between to points
int Nanobot::calcEuclideanDist(int x, int y)
{
    return sqrt(pow((x-_posX),2) + pow((y-_posY),2));
}

// determine direction to move if nanobot should repel from object
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

// determine direction to move if nanobot should attract to object
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

// normalize probability matrix after added biasing
void Nanobot::normalizeMoveMatrix(std::vector<float> &biasedMoveMatrix)
{
    float average = accumulate(biasedMoveMatrix.begin(), biasedMoveMatrix.end(), 0.0);

    for (float n : biasedMoveMatrix)
    {
        n /= average;
    }
}

// calculate the biasing matrix if nanobot is searching
std::vector<float> Nanobot::calcSearchingMoveMatrix()
{
    // initialize uniform probability matrix
    std::vector<float> searchingMoveMatrix(9, 1.0);
    
    // lock the mutex so we can access shared resources
    std::lock_guard<std::mutex> uLock(_mutex);

    // incorporate biases from obstacles that are in nanobot's range
    for (auto it : _obstacles)
    {
        if (it->getVisualState() == VisualState::kSeen)
        {
            int ox, oy;
            it->getPosition(ox,oy);
            if (this->calcEuclideanDist(ox,oy) < _range)
            {
                searchingMoveMatrix[this->calcRepelBiasDirection(ox,oy)] += it->getBias();
            }
        }
    }
    // incorporate biases from piles that are in nanobot's range
    for (auto it : _piles)
    {
        if (it->getVisualState() == VisualState::kSeen)
        {
            int px, py;
            it->getPosition(px,py);
            if (this->calcEuclideanDist(px,py) < _range)
            {
                searchingMoveMatrix[this->calcAttractBiasDirection(px,py)] += it->getBias();
            }
        }
    }

    // normalize the probability matrix
    normalizeMoveMatrix(searchingMoveMatrix);

    return searchingMoveMatrix;
}

// check if nanobot has run into another entity
bool Nanobot::checkDetection(int &x, int &y, EntityType &detectedEntity)
{
    // lock the mutex so we can access shared resources
    std::lock_guard<std::mutex> uLock(_mutex);

    // iterate through nests to see if nanobot nas detected one
    for (auto it : _nests)
    {
        int nx, ny;
        it->getPosition(nx,ny);
        if (this->calcEuclideanDist(nx,ny) < (_sizeRadius + it->getSizeRadius()))
        {
            // if we have hit a nest and the nanobot was returning, then deposit piece into nest
            if (_mode == BotMode::kReturning)
            {
                it->depositPiece();
                // lock cout with a mutex
                std::unique_lock<std::mutex> lck(_mtx);
                std::cout << "The nanobots have collected " << it->getPiecesCollected() << "/" << it->getPiecesToCollect() << " pieces!" << std::endl;
                lck.unlock();
                // check if all pieces have been collected and turn on flag if they have
                if (it->getPiecesCollected() >= it->getPiecesToCollect())
                {
                    // sleep at every iteration to reduce CPU usage
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    it->turnOnFlag();
                }
            }
            
            detectedEntity = EntityType::kNest;
            this->moveAwayFrom(x, y, nx, ny);
            return true;
        }
    }
    
    // iterate through obstacles to see if nanobot nas detected one
    for (auto it : _obstacles)
    {
        int ox, oy;
        it->getPosition(ox,oy);
        if (this->calcEuclideanDist(ox,oy) < (_sizeRadius + it->getSizeRadius()))
        {
            detectedEntity = EntityType::kObstacle;
            this->moveAwayFrom(x, y, ox, oy);
            return true;
        }
    }

    // iterate through piles to see if nanobot nas detected one
    for (auto it : _piles)
    {
        int px, py;
        it->getPosition(px,py);
        if (this->calcEuclideanDist(px,py) < (_sizeRadius + it->getSizeRadius()))
        {
            // if we have hit a pile, the nanobot is searching, and the pile has stock, then remove a piece
            if (it->getPileStock() == PileStock::kFilled)
            {
                if (_mode == BotMode::kSearching)
                {
                    it->removePiece();
                    // if all pieces are gone then set the pile stock to empty
                    if (it->getPiecesLeft() == 0)
                    {
                        it->setPileStockEmpty();
                    }
                }
            }
            
            detectedEntity = EntityType::kPile;
            this->moveAwayFrom(x, y, px, py);
            return true;
        }
    }

    // iterate through predators to see if nanobot nas detected one
    for (auto it : _predators)
    {
        int prex, prey;
        it->getPosition(prex,prey);
        if (this->calcEuclideanDist(prex,prey) < (_sizeRadius + it->getSizeRadius()))
        {
            detectedEntity = EntityType::kPredator;
            this->moveAwayFrom(x, y, prex, prey);
            return true;
        }
    }

    return false;
}

// calculate movement away from other entity if detected
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

// check if nanobot has made it outside of nest and return boolean
bool Nanobot::checkIfOutOfNest()
{
    // lock the mutex so we can access shared resources
    std::lock_guard<std::mutex> uLock(_mutex);

    for (auto it : _nests)
    {
        int nx, ny;
        it->getPosition(nx,ny);
        if (this->calcEuclideanDist(nx,ny) >= (_sizeRadius + it->getSizeRadius()))
        {
            return true;
        }
    }

    return false;
}

// calculate the biasing matrix if nanobot is returning
std::vector<float> Nanobot::calcReturningMoveMatrix()
{
    // initialize uniform probability matrix
    std::vector<float> returningMoveMatrix(9, 1.0);

    // lock the mutex so we can access shared resources
    std::lock_guard<std::mutex> uLock(_mutex);

    // incorporate biases from nests that are in nanobot's range
    for (auto it : _nests)
    {
        if (it->getVisualState() == VisualState::kSeen)
        {
            int nx, ny;
            it->getPosition(nx,ny);
            returningMoveMatrix[this->calcAttractBiasDirection(nx,ny)] += it->getBias();
        }
    }

    // normalize the probability matrix
    normalizeMoveMatrix(returningMoveMatrix);

    return returningMoveMatrix;
}