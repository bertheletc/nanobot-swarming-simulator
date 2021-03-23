#ifndef NANOBOT_H
#define NANOBOT_H

#include "entity.h"
#include "dynamic.h"
#include "nest.h"
#include "obstacle.h"
#include "pile.h"
#include "predator.h"

enum BotMode 
{
    kNesting, 
    kSearching, 
    kReturning,
    kDead,
}; // 

// child of Dynamic and Entity classes
// objects of this class represent an individual nanobot
class Nanobot : public Entity, public Dynamic, public std::enable_shared_from_this<Nanobot>
{
public:
    // Constructor
    Nanobot(std::vector<std::shared_ptr<Nest>> &nests,
            std::vector<std::shared_ptr<Obstacle>> &obstacles,
            std::vector<std::shared_ptr<Pile>> &piles,
            std::vector<std::shared_ptr<Predator>> &predators,
            int id, int size, std::vector<int> worldSize, int range);
    
    void simulate();
    void move();
    void killed();
    BotMode getBotMode() { return _mode; }

    // miscellaneous
    std::shared_ptr<Nanobot> get_shared_this() { return shared_from_this(); }

private:
    int calcEuclideanDist(int x, int y);
    int calcRepelBiasDirection(int x, int y);
    int calcAttractBiasDirection(int x, int y);
    void normalizeMoveMatrix(std::vector<float> &biasedMoveMatrix);
    std::vector<float> calcSearchingMoveMatrix();
    bool checkDetection(int &x, int &y, EntityType &detectedObject);
    void moveAwayFrom(int &x, int &y, int &xAway, int &yAway);
    bool checkIfOutOfNest();
    std::vector<float> calcReturningMoveMatrix();
    
    BotMode _mode;
    float _range;
    std::mutex _mutex;

    std::vector<std::shared_ptr<Nest>> _nests;
    std::vector<std::shared_ptr<Obstacle>> _obstacles;
    std::vector<std::shared_ptr<Pile>> _piles;
    std::vector<std::shared_ptr<Predator>> _predators;
};

#endif