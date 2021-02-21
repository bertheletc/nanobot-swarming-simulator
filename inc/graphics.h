#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include <opencv2/core.hpp>

#include "entity.h"

class Graphics
{
public:
    // constructor / desctructor

    // getters / setters
    void setWorldFilename(std::string filename) { _worldFilename = filename; }
    void setEntities(std::vector<std::shared_ptr<Entity>> &entities) { _entities = entities; };

    // typical behaviour methods
    void simulate();

private:
    // typical behaviour methods
    void loadBackgroundImg();
    void drawTrafficObjects();

    // member variables
    std::vector<std::shared_ptr<Entity>> _entities;
    std::string _worldFilename;
    std::string _windowName;
    std::vector<cv::Mat> _images;
};

#endif