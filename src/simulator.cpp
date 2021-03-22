#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "static.h"
#include "nest.h"
#include "obstacle.h"
#include "pile.h"
#include "dynamic.h"
#include "nanobot.h"
#include "predator.h"
#include "graphics.h"

int iterations;

bool checkComplete(){};

void generateStaticEntities(std::vector<std::shared_ptr<Nest>> &nests, 
          std::vector<std::shared_ptr<Obstacle>> &obstacles, 
          std::vector<std::shared_ptr<Pile>> &piles,
          std::vector<int> staticEntityQuantity,
          std::vector<float> staticEntityBiases, 
          std::vector<int> staticEntitySizes,
          int pilePieces)
{

    for (int nn = 0; nn < staticEntityQuantity[0]; nn++)
    {
        nests.push_back(std::make_shared<Nest>(nn, staticEntitySizes[0], staticEntityBiases[0]));
    }

    // position intersections in pixel coordinates
    nests.at(0)->setPosition(100, 100);

    for (int no = 0; no < staticEntityQuantity[1]; no++)
    {
        obstacles.push_back(std::make_shared<Obstacle>(no, staticEntitySizes[1], staticEntityBiases[1]));
    }

    // position intersections in pixel coordinates
    obstacles.at(0)->setPosition(400, 500);
    obstacles.at(1)->setPosition(500, 400);
    obstacles.at(2)->setPosition(700, 700);
    
    for (int np = 0; np < staticEntityQuantity[2]; np++)
    {
        piles.push_back(std::make_shared<Pile>(np, staticEntitySizes[2], staticEntityBiases[2], pilePieces));
    }

    // position intersections in pixel coordinates
    piles.at(0)->setPosition(1200, 450);
}

void generateDynamicEntities(std::vector<std::shared_ptr<Nest>> &nests,
                             std::vector<std::shared_ptr<Obstacle>> &obstacles,
                             std::vector<std::shared_ptr<Pile>> &piles,
                             std::vector<std::shared_ptr<Predator>> &predators,
                             std::vector<std::shared_ptr<Nanobot>> &nanobots,
                             std::vector<int> dynamicEntityQuantity,
                             std::vector<int> dynamicEntitySizes,
                             std::vector<int> worldSize,
                             int nanobotRange)
{
    for (int npre = 0; npre < dynamicEntityQuantity[0]; npre++)
    {
        predators.push_back(std::make_shared<Predator>(npre, dynamicEntitySizes[0], worldSize));
    }

    // position intersections in pixel coordinates
    predators.at(0)->setPosition(500, 500);
    predators.at(1)->setPosition(600, 600);
    
    for (int nnan = 0; nnan < dynamicEntityQuantity[1]; nnan++)
    {
        nanobots.push_back(std::make_shared<Nanobot>(nests, obstacles, piles, predators, nnan, dynamicEntitySizes[1], worldSize, nanobotRange));
        nanobots.at(nnan)->setPosition(100, 100);
    }
}

int main() {

    /* Setup simulation world */

    // PARAMETERS TO CHANGE
    int nNanobots = 100;
    int nanobotRange = 200;
    int pilePieces = 100;
    float nestBias = 10.0;
    float obstacleBias = 1.0;
    float pileBias = 10.0;
    // END OF PARAMETERS TO CHANGE


    // create string to hold file path to world image
    //std::string worldImg = "../images/empty-parking-lot-top-down-aerial-view.jpg"; // 1300 width, 697 height
    //std::string worldImg = "../images/nature.jpg"; // 485 width, 512 height
    std::string worldImg = "../images/soccer-field.jpg"; // 1300 width, 910 height

    // create static entities to place in the world
    std::vector<std::shared_ptr<Nest>> nests;
    std::vector<std::shared_ptr<Obstacle>> obstacles;
    std::vector<std::shared_ptr<Pile>> piles;
    // create dynamic entities to place in the world
    std::vector<std::shared_ptr<Predator>> predators;
    std::vector<std::shared_ptr<Nanobot>> nanobots;

    // WORLD POSITION AND SIZING
    int nNests = 1;
    int nObstacles = 3;
    int nPiles = 1;
    int nPredators = 2;

    int nestSize = 100;
    int obstacleSize = 50;
    int pileSize = 80;
    int predatorSize = 20;
    int nanobotSize = 10;

    // load image to extract pixel height and width
    cv::Mat image = cv::imread(worldImg);
    std::vector<int> worldSize;
    worldSize.push_back(image.size().width);
    worldSize.push_back(image.size().height);
    
    std::vector<int> staticEntityQuantity{nNests, nObstacles, nPiles};
    std::vector<float> staticEntityBiases{nestBias, obstacleBias, pileBias};
    std::vector<int> staticEntitySizes{nestSize, obstacleSize, pileSize};
    std::vector<int> dynamicEntityQuantity{nPredators, nNanobots};
    std::vector<int> dynamicEntitySizes{predatorSize, nanobotSize};

    generateStaticEntities(nests, obstacles, piles, staticEntityQuantity, staticEntityBiases, staticEntitySizes, pilePieces);
    generateDynamicEntities(nests, obstacles, piles, predators, nanobots, dynamicEntityQuantity, dynamicEntitySizes, worldSize, nanobotRange);

    /* Simulate static objects */

    // simulate obstacles
    std::for_each(obstacles.begin(), obstacles.end(), [](std::shared_ptr<Obstacle> &o) {
        o->simulate();
    });

    // simulate piles
    std::for_each(piles.begin(), piles.end(), [](std::shared_ptr<Pile> &p) {
        p->simulate();
    });

    /* Simulate dynamic objects */

    // simulate predators
    std::for_each(predators.begin(), predators.end(), [](std::shared_ptr<Predator> &pred) {
        pred->simulate();
    });

    // simulate nanobots
    std::for_each(nanobots.begin(), nanobots.end(), [](std::shared_ptr<Nanobot> &bot) {
        bot->simulate();
    });

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

    std::for_each(predators.begin(), predators.end(), [&entities](std::shared_ptr<Predator> &predator) {
        std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(predator);
        entities.push_back(entity);
    });

    std::for_each(nanobots.begin(), nanobots.end(), [&entities](std::shared_ptr<Nanobot> &nanobot) {
        std::shared_ptr<Entity> entity = std::dynamic_pointer_cast<Entity>(nanobot);
        entities.push_back(entity);
    });

    // draw all objects in vector
    Graphics *graphics = new Graphics();
    graphics->setWorldFilename(worldImg);
    graphics->setEntities(entities);
    graphics->simulate();
}