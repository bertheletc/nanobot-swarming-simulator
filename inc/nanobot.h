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
}; // describes the state of the nanobot

// child of Dynamic and Entity classes
// objects of this class represent an individual nanobot
class Nanobot : public Entity, public Dynamic, public std::enable_shared_from_this<Nanobot>
{
public:
    // METHODS
    // Constructor
    Nanobot(std::vector<std::shared_ptr<Nest>> &nests,
            std::vector<std::shared_ptr<Obstacle>> &obstacles,
            std::vector<std::shared_ptr<Pile>> &piles,
            std::vector<std::shared_ptr<Predator>> &predators,
            int id, int size, std::vector<int> worldSize, int range);
    
    // overriden methods from abstract Dynamic and Entity classes
    void simulate();
    void move();
    // getter
    BotMode getBotMode() { return _mode; }

    // miscellaneous
    std::shared_ptr<Nanobot> get_shared_this() { return shared_from_this(); }

private:
    // METHODS
    int calcEuclideanDist(int x, int y); // calculate the Euclidean distance between to points
    int calcRepelBiasDirection(int x, int y); // determine direction to move if nanobot should repel from object
    int calcAttractBiasDirection(int x, int y); // determine direction to move if nanobot should attract to object
    void normalizeMoveMatrix(std::vector<float> &biasedMoveMatrix); // normalize probability matrix after added biasing
    std::vector<float> calcSearchingMoveMatrix(); // calculate the biasing matrix if nanobot is searching
    bool checkDetection(int &x, int &y, EntityType &detectedObject); // check if nanobot has run into another entity
    void moveAwayFrom(int &x, int &y, int &xAway, int &yAway); // calculate movement away from other entity if detected
    bool checkIfOutOfNest(); // check if nanobot has made it outside of nest
    std::vector<float> calcReturningMoveMatrix(); // calculate the biasing matrix if nanobot is returning
    
    // ATTRIBUTES
    BotMode _mode; // state of nanobot
    float _range; // range that nanobot can be influenced/biased by other entities (pixels) 
    std::mutex _mutex; // mutex to protect access to shared resources

    // vectors to shared pointers of all non-nanobot entities
    std::vector<std::shared_ptr<Nest>> _nests;
    std::vector<std::shared_ptr<Obstacle>> _obstacles;
    std::vector<std::shared_ptr<Pile>> _piles;
    std::vector<std::shared_ptr<Predator>> _predators;
};

#endif