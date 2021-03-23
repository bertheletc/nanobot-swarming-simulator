# CPPND: Nanobot Swarming Simulator

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application starting with this repo, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

<img src="images/NANOBOT_SIMULATION_WINDOW.png"/>

## Dependencies for Running Locally
* cmake >= 3.11.3
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./nanobot_simulation`.

## Running Behavior

* While the simulation is running you will see a window like the one shown in the project intro above.
* The color coding key is as follows
  * Nanobots: purple, blue, or pink
    * purple - in the nest
    * blue - searching for the pile of pieces
    * pink - returning to nest with piece
  * Predators: red
  * Nests: orange
  * Obstacles: black
  * Piles: yellow
* While the simulation is running you will see printouts of what is happening as shown in the image below.
* You will see the following things printed out to the console.
    * Message when nanobot returns a piece to the nest telling how many have been collected.
    * Message stating that a nanobot has been killed by a predator. 

<img src="images/simulation_running_printout.png"/>

* Once the simulation is complete you will see console printouts stating the completion as well as the simulation duration (as shown below)

<img src="images/simulation_end.png"/>

## Rubric Checkoffs

THE FOLLOWING RUBRIC POINTS ARE ADDRESSED IN THIS PROJECT

* The project demonstrates an understanding of C++ functions and control structures.
  * FILES: Check ALL files
* The project reads data from a file and process the data, or the program writes data to a file. 
  * FILES: Check graphics.cpp, line 46 
* The project uses Object Oriented Programming techniques.
  * FILES: Check entire project structure and files except simulator.cpp
* Classes use appropriate access specifiers for class members.
  * FILES: Check ALL .h files
* Classes abstract implementation details from their interfaces.
  * FILES: Check entire project structure and files except simulator.cpp
* Classes encapsulate behavior.
  * FILES: Check entire project structure and files except simulator.cpp
* Classes follow an appropriate inheritance hierarchy.
  * FILES: Check entire project structure and files except simulator.cpp. Specifically look at Nanobot, Predator, Nest, Obstacle, and Pile subclasses
* Derived class functions override virtual base class functions.
  * FILES: Check out Predator and Nanobot classes that overrite virtual methods from Entity and Dynamic classes
* The project makes use of references in function declarations.
  * FILES: Check out nanobot.cpp, lines 213, 266, 358
* The project uses destructors appropriately.
  * FILES: Check out entity.cpp, line 24
* The project uses smart pointers instead of raw pointers.
  * FILES: Shared pointers are used to pass the entity objects around. Check out simulator.cpp, line 106
* The project uses multithreading.
  * FILES: Nanobots and Predators run in threads. Check out nanobot.cpp and predator.cpp
* A mutex or lock is used in the project.
  * FILES: Check out nanobot.cpp, lines 92, 230, 268, 283, 401, 423

