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

void runSim();
bool checkComplete();
void stopSim();

int main() {
    std::cout << "Hello World!" << "\n";
    return 0;
}