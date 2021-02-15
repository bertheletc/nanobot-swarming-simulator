#ifndef WORLD_H
#define WORLD_H

#include <vector>

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
    World();
    void findOpenSpaces();
    void display();

private:
    vector<int> _size; // [x,y] base * height in pixels
    vector<vector<int>> _openSpaces;

    int _numNests
    int _numBots; // number of nanobots in the simulation
    int _numObstacles;
    int _numPiles;
    int _numPredators;
}

#endif