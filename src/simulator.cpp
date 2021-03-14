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

    // create string to hold file path to world image
    //std::string worldImg = "../terrains/empty-parking-lot-top-down-aerial-view.jpg"; // 1300 width, 697 height
    //std::string worldImg = "../terrains/nature.jpg"; // 485 width, 512 height
    std::string worldImg = "../terrains/soccer-field.jpg"; // 1300 width, 910 height

    // create static entities to place in the world
    std::vector<std::shared_ptr<Nest>> nests;
    std::vector<std::shared_ptr<Obstacle>> obstacles;
    std::vector<std::shared_ptr<Pile>> piles;
    // create dynamic entities to place in the world
    std::vector<std::shared_ptr<Nanobot>> nanobots;
    std::vector<std::shared_ptr<Predator>> predators;

    // TODO: Change to take in user specified numbers
    int nNests = 1;
    int nObstacles = 5;
    int nPiles = 1;
    int nNanobots = 10;
    int nPredators = 2;
    
    std::vector<int> entityQuantity{nNests, nObstacles, nPiles, nNanobots, nPredators};
    World world(nests, obstacles, piles, nanobots, predators, entityQuantity);

    /* Simulate dynamic objects */

    // // simulate nanobots
    // std::for_each(nanobots.begin(), nanobots.end(), [](std::shared_ptr<Nanobot> &i) {
    //     i->simulate();
    // });

    // // simulate predators
    // std::for_each(predators.begin(), predators.end(), [](std::shared_ptr<Predator> &v) {
    //     v->simulate();
    // });

    /* Launch visualization */

    // add all objects into common vector
    std::vector<std::shared_ptr<Entity>> entities;
    
    std::for_each(nests.begin(), nests.end(), [&entities](std::shared_ptr<Nest> &nest) {
        std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(nest);
        entities.push_back(entity);
    });

    // std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(nests[0]);
    // entities.push_back(entity);

    std::for_each(obstacles.begin(), obstacles.end(), [&entities](std::shared_ptr<Obstacle> &obstacle) {
        std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(obstacle);
        entities.push_back(entity);
    });

    std::for_each(piles.begin(), piles.end(), [&entities](std::shared_ptr<Pile> &pile) {
        std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(pile);
        entities.push_back(entity);
    });

    // std::for_each(nanobots.begin(), nanobots.end(), [&entities](std::shared_ptr<Nanobot> &nanobot) {
    //     std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(nanobot);
    //     entities.push_back(entity);
    // });

    // std::for_each(predators.begin(), predators.end(), [&entities](std::shared_ptr<Predator> &predator) {
    //     std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(predator);
    //     entities.push_back(entity);
    // });

    // draw all objects in vector
    Graphics *graphics = new Graphics();
    graphics->setWorldFilename(worldImg);
    graphics->setEntities(entities);
    graphics->simulate();
}