#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include "entity.h"

// class to visually render the simulation world
class Graphics
{
public:
    // METHODS
    // getters / setters
    void setWorldFilename(std::string filename) { _worldFilename = filename; }
    void setEntities(std::vector<std::shared_ptr<Entity>> &entities) { _entities = entities; };
    // method to simulate the graphics engine
    void simulate();

private:
    // METHODS
    void loadBackgroundImg(); // method to load image into rendering of simulation
    void drawTrafficObjects();

    // ATTRIBUTES
    std::vector<std::shared_ptr<Entity>> _entities; // vector of shared pointers to ALL entities
    std::string _worldFilename; // filename of the background image
    std::string _windowName; // name of simulation window
    std::vector<cv::Mat> _images; 
};

#endif