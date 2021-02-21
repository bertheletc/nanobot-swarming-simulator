#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <thread>

#include "static.h"
#include "nest.h"
#include "obstacle.h"
#include "pile.h"
#include "dynamic.h"
#include "nanobot.h"
#include "predator.h"

class World {
public:
    // Constructor
    World(std::vector<std::shared_ptr<Nest>> &nests, 
          std::vector<std::shared_ptr<Obstacle>> &obstacles, 
          std::vector<std::shared_ptr<Pile>> &piles, 
          std::vector<std::shared_ptr<Nanobot>> &nanobots, 
          std::vector<std::shared_ptr<Predator>> &predators,
          std::vector<int> &entityQuantity);
    
    void findOpenSpaces();
    void display();

private:
    std::vector<int> _size; // [x,y] base * height in pixels
    std::vector<std::vector<int>> _openSpaces;

    int _numNests;
    int _numObstacles;
    int _numPiles;
    int _numBots; // number of nanobots in the simulation
    int _numPredators;
};

#endif