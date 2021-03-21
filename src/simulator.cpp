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

// GUI placeholder
int iterations;

bool checkComplete(){};

void generateEntities(std::vector<std::shared_ptr<Nest>> &nests, 
          std::vector<std::shared_ptr<Obstacle>> &obstacles, 
          std::vector<std::shared_ptr<Pile>> &piles, 
          std::vector<std::shared_ptr<Predator>> &predators,
          std::vector<int> &entityQuantity)
{

    for (size_t nn = 0; nn < entityQuantity[0]; nn++)
    {
        nests.push_back(std::make_shared<Nest>());
    }

    // position intersections in pixel coordinates
    nests.at(0)->setPosition(100, 100);

    for (size_t no = 0; no < entityQuantity[1]; no++)
    {
        obstacles.push_back(std::make_shared<Obstacle>());
    }

    // position intersections in pixel coordinates
    obstacles.at(0)->setPosition(200, 300);
    obstacles.at(1)->setPosition(300, 200);
    obstacles.at(2)->setPosition(400, 500);
    obstacles.at(3)->setPosition(500, 400);
    obstacles.at(4)->setPosition(700, 700);
    
    for (size_t np = 0; np < entityQuantity[2]; np++)
    {
        piles.push_back(std::make_shared<Pile>());
    }

    // position intersections in pixel coordinates
    piles.at(0)->setPosition(1200, 800);
    
    for (size_t npre = 0; npre < entityQuantity[3]; npre++)
    {
        predators.push_back(std::make_shared<Predator>());
    }

    // position intersections in pixel coordinates
    predators.at(0)->setPosition(500, 500);
    predators.at(1)->setPosition(600, 600);
}

void generateNanobots(std::vector<std::shared_ptr<Nanobot>> &nanobots, int nNanobots, std::vector<int> worldSize)
{
    for (int nnan = 0; nnan < nNanobots; nnan++)
    {
        nanobots.push_back(std::make_shared<Nanobot>(nnan, worldSize));
    }

    // position intersections in pixel coordinates
    nanobots.at(0)->setPosition(1000, 200);
    nanobots.at(1)->setPosition(200, 700);
    nanobots.at(2)->setPosition(1000, 200);
    nanobots.at(3)->setPosition(200, 700);
    nanobots.at(4)->setPosition(1000, 200);
    nanobots.at(5)->setPosition(200, 700);
    nanobots.at(6)->setPosition(1000, 200);
    nanobots.at(7)->setPosition(200, 700);
    nanobots.at(8)->setPosition(1000, 200);
    nanobots.at(9)->setPosition(200, 700);
}

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
    std::vector<std::shared_ptr<Predator>> predators;
    std::vector<std::shared_ptr<Nanobot>> nanobots;

    // TODO: Change to take in user specified numbers
    int nNests = 1;
    int nObstacles = 5;
    int nPiles = 1;
    int nPredators = 2;
    int nNanobots = 10;

    // load image to extract pixel height and width
    cv::Mat image = cv::imread(worldImg);
    std::vector<int> worldSize;
    worldSize.push_back(image.size().width);
    worldSize.push_back(image.size().height);
    
    std::vector<int> entityQuantity{nNests, nObstacles, nPiles, nPredators};

    generateEntities(nests, obstacles, piles, predators, entityQuantity);
    generateNanobots(nanobots, nNanobots, worldSize);

    /* Simulate dynamic objects */

    // simulate nanobots
    std::for_each(nanobots.begin(), nanobots.end(), [](std::shared_ptr<Nanobot> &i) {
        i->simulate();
    });

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