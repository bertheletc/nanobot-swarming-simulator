#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>

#include "world.h"
#include "static.h"
#include "nest.h"
#include "obstacle.h"
#include "pile.h"
#include "dynamic.h"
#include "nanobot.h"
#include "predator.h"
#include "graphics.h"

World *simWorld;
// GUI placeholder
int iterations;

bool checkComplete(){};

int main() {

    /* Setup simulation world */

    // create static entities to place in the world
    std::vector<std::shared_ptr<Nest>> nests;
    std::vector<std::shared_ptr<Obstacle>> obstacles;
    std::vector<std::shared_ptr<Pile>> piles;
    // create dynamic entities to place in the world
    std::vector<std::shared_ptr<Nanobot>> nanobots;
    std::vector<std::shared_ptr<Predator>> predators;
    // create string to hold file path to 
    //std::string worldImg = "../terrains/empty-parking-lot-top-down-aerial-view.jpg"; // 1300 width, 697 height
    //std::string worldImg = "../terrains/nature.jpg"; // 485 width, 512 height
    std::string worldImg = "../terrains/soccer-field.jpg"; // 1300 width, 910 height

    //init traffic objects
    int nNests = 2;
    for (size_t nn = 0; nn < nNests; nn++)
    {
        nests.push_back(std::make_shared<Nest>());
    }

    // position intersections in pixel coordinates
    nests.at(0)->setPosition(100, 200);
    nests.at(1)->setPosition(200, 100);

    int nObstacles = 2;
    for (size_t no = 0; no < nObstacles; no++)
    {
        obstacles.push_back(std::make_shared<Obstacle>());
    }

    // position intersections in pixel coordinates
    obstacles.at(0)->setPosition(200, 300);
    obstacles.at(1)->setPosition(300, 200);
    
    int nPiles = 2;
    for (size_t np = 0; np < nPiles; np++)
    {
        piles.push_back(std::make_shared<Pile>());
    }

    // position intersections in pixel coordinates
    piles.at(0)->setPosition(700, 800);
    piles.at(1)->setPosition(800, 700);
    
    int nNanobots = 2;
    for (size_t nnan = 0; nnan < nNanobots; nnan++)
    {
        nanobots.push_back(std::make_shared<Nanobot>());
    }

    // position intersections in pixel coordinates
    nanobots.at(0)->setPosition(1000, 200);
    nanobots.at(1)->setPosition(200, 700);
    
    int nPredators = 2;
    for (size_t npre = 0; npre < nPredators; npre++)
    {
        predators.push_back(std::make_shared<Predator>());
    }

    // position intersections in pixel coordinates
    predators.at(0)->setPosition(500, 500);
    predators.at(1)->setPosition(600, 600);
    
    //std::vector<int> entityQuantity{nNanobots, nPredators, nNests, nObstacles, nPiles};
    //World world(nests, obstacles, piles, nanobots, predators, entityQuantity);

    /* Simulate dynamic world entities */

    // // simulate nanobots
    // std::for_each(nanobots.begin(), nanobots.end(), [](std::shared_ptr<Nanobot> &n) {
    //     n->simulate();
    // });

    // // simulate predators
    // std::for_each(predators.begin(), predators.end(), [](std::shared_ptr<Predator> &p) {
    //     p->simulate();
    // });

    /* Launch visualization */

    // add all objects into common vector
    std::vector<std::shared_ptr<Entity>> entities;
    
    std::for_each(nests.begin(), nests.end(), [&entities](std::shared_ptr<Nest> &nest) {
        std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(nest);
        entities.push_back(entity);
    });

    std::for_each(obstacles.begin(), obstacles.end(), [&entities](std::shared_ptr<Obstacle> &obstacle) {
        std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(obstacle);
        entities.push_back(entity);
    });

    std::for_each(piles.begin(), piles.end(), [&entities](std::shared_ptr<Pile> &pile) {
        std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(pile);
        entities.push_back(entity);
    });

    std::for_each(nanobots.begin(), nanobots.end(), [&entities](std::shared_ptr<Nanobot> &nanobot) {
        std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(nanobot);
        entities.push_back(entity);
    });

    std::for_each(predators.begin(), predators.end(), [&entities](std::shared_ptr<Predator> &predator) {
        std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(predator);
        entities.push_back(entity);
    });

    // draw all objects in vector
    Graphics *graphics = new Graphics();
    graphics->setWorldFilename(worldImg);
    graphics->setEntities(entities);
    graphics->simulate();
}