#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "world.h"
#include "static.h"
#include "nest.h"
#include "obstacle.h"
#include "pile.h"
#include "dynamic.h"
#include "nanobot.h"
#include "predator.h"

World *simWorld;
// GUI placeholder
int iterations;

void createEntities();
void runSim();
bool checkComplete();
void stopSim();

int main() 
{
    return 0;
}

// EXAMPLE CODE FROM TRAFFIC SIMULATOR
// int main() {
//     /* PART 1 : Set up traffic objects */

//     // create and connect intersections and streets
//     std::vector<std::shared_ptr<Street>> streets;
//     std::vector<std::shared_ptr<Intersection>> intersections;
//     std::vector<std::shared_ptr<Vehicle>> vehicles;
//     std::string backgroundImg;
//     int nVehicles = 6;
//     createTrafficObjects_Paris(streets, intersections, vehicles, backgroundImg, nVehicles);

//     /* PART 2 : simulate traffic objects */

//     // simulate intersection
//     std::for_each(intersections.begin(), intersections.end(), [](std::shared_ptr<Intersection> &i) {
//         i->simulate();
//     });

//     // simulate vehicles
//     std::for_each(vehicles.begin(), vehicles.end(), [](std::shared_ptr<Vehicle> &v) {
//         v->simulate();
//     });

//     /* PART 3 : Launch visualization */

//     // add all objects into common vector
//     std::vector<std::shared_ptr<TrafficObject>> trafficObjects;
//     std::for_each(intersections.begin(), intersections.end(), [&trafficObjects](std::shared_ptr<Intersection> &intersection) {
//         std::shared_ptr<TrafficObject> trafficObject = std::dynamic_pointer_cast<TrafficObject>(intersection);
//         trafficObjects.push_back(trafficObject);
//     });

//     std::for_each(vehicles.begin(), vehicles.end(), [&trafficObjects](std::shared_ptr<Vehicle> &vehicles) {
//         std::shared_ptr<TrafficObject> trafficObject = std::dynamic_pointer_cast<TrafficObject>(vehicles);
//         trafficObjects.push_back(trafficObject);
//     });

//     // draw all objects in vector
//     Graphics *graphics = new Graphics();
//     graphics->setBgFilename(backgroundImg);
//     graphics->setTrafficObjects(trafficObjects);
//     graphics->simulate();
// }