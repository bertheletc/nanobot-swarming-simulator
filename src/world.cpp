#include "world.h"

World::World(std::vector<std::shared_ptr<Nest>> &nests, 
          std::vector<std::shared_ptr<Obstacle>> &obstacles, 
          std::vector<std::shared_ptr<Pile>> &piles, 
          std::vector<std::shared_ptr<Nanobot>> &nanobots, 
          std::vector<std::shared_ptr<Predator>> &predators,
          std::vector<int> &entityQuantity)
{
    _numNests = entityQuantity[0];
    _numObstacles = entityQuantity[1];
    _numPiles = entityQuantity[2];
    _numBots = entityQuantity[3];
    _numPredators = entityQuantity[4];

    for (size_t nn = 0; nn < _numNests; nn++)
    {
        nests.push_back(std::make_shared<Nest>());
    }

    // position intersections in pixel coordinates
    nests.at(0)->setPosition(100, 100);

    for (size_t no = 0; no < _numObstacles; no++)
    {
        obstacles.push_back(std::make_shared<Obstacle>());
    }

    // position intersections in pixel coordinates
    obstacles.at(0)->setPosition(200, 300);
    obstacles.at(1)->setPosition(300, 200);
    obstacles.at(2)->setPosition(400, 500);
    obstacles.at(3)->setPosition(500, 400);
    obstacles.at(4)->setPosition(700, 700);
    
    for (size_t np = 0; np < _numPiles; np++)
    {
        piles.push_back(std::make_shared<Pile>());
    }

    // position intersections in pixel coordinates
    piles.at(0)->setPosition(1200, 800);
    
    // for (size_t nnan = 0; nnan < _numBots; nnan++)
    // {
    //     nanobots.push_back(std::make_shared<Nanobot>());
    // }

    // // position intersections in pixel coordinates
    // nanobots.at(0)->setPosition(1000, 200);
    // nanobots.at(1)->setPosition(200, 700);
    
    // for (size_t npre = 0; npre < _numPredators; npre++)
    // {
    //     predators.push_back(std::make_shared<Predator>());
    // }

    // // position intersections in pixel coordinates
    // predators.at(0)->setPosition(500, 500);
    // predators.at(1)->setPosition(600, 600);
}