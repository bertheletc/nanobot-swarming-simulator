#include <iostream>
#include <thread>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "graphics.h"

// USED VERY SIMILAR CODE TO CONCURRENT TRAFFIC SIMULATOR FOR THIS

// method to simulate the graphics engine
void Graphics::simulate()
{
    this->loadBackgroundImg();
    // begin loop to render the simulation
    while (true)
    {
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        
        // update graphics
        this->drawTrafficObjects();

        for (auto it : _entities)
        {
            // check Nest entity flag to know if simulation is complete
            if (it->getType() == EntityType::kNest)
            {
                if (it->getFlag())
                {
                    // RETURN AND END SIMULATION
                    return;
                }
            }
        }
    }
}

// method to load image into rendering of simulation
void Graphics::loadBackgroundImg()
{    
    // create window
    _windowName = "Nanobot Swarming Simulation";
    cv::namedWindow(_windowName, cv::WINDOW_NORMAL);

    // load image and create copy to be used for semi-transparent overlay
    cv::Mat background = cv::imread(_worldFilename);
    // // added this resize because window was enormous!
    // cv::resizeWindow(_windowName, 960, 540);
    _images.push_back(background);         // first element is the original background
    _images.push_back(background.clone()); // second element will be the transparent overlay
    _images.push_back(background.clone()); // third element will be the result image for display

    std::cout << "World Size" << std::endl;
    std::cout << "Width : " << background.size().width << " pixels" << std::endl;
    std::cout << "Height: " << background.size().height << " pixels" << std::endl;
}

void Graphics::drawTrafficObjects()
{
    // reset images
    _images.at(1) = _images.at(0).clone();
    _images.at(2) = _images.at(0).clone();

    // create overlay from all traffic objects
    for (auto it : _entities)
    {
        int posx, posy;
        it->getPosition(posx, posy);

        if (it->getType() == EntityType::kNest)
        {
            cv::RNG rng(it->getID());
            cv::circle(_images.at(1), cv::Point2d(posx, posy), it->getSizeRadius(), it->getColor(), -1);
        }
        else if (it->getType() == EntityType::kObstacle)
        {
            cv::RNG rng(it->getID());
            cv::circle(_images.at(1), cv::Point2d(posx, posy), it->getSizeRadius(), it->getColor(), -1);
        }
        else if (it->getType() == EntityType::kPile)
        {
            cv::RNG rng(it->getID());
            cv::circle(_images.at(1), cv::Point2d(posx, posy), it->getSizeRadius(), it->getColor(), -1);
        }
        else if (it->getType() == EntityType::kNanobot)
        {
            cv::RNG rng(it->getID());
            cv::circle(_images.at(1), cv::Point2d(posx, posy), it->getSizeRadius(), it->getColor(), -1);
        }
        else if (it->getType() == EntityType::kPredator)
        {
            cv::RNG rng(it->getID());
            cv::circle(_images.at(1), cv::Point2d(posx, posy), it->getSizeRadius(), it->getColor(), -1);
        }
    }

    float opacity = 0.85;
    cv::addWeighted(_images.at(1), opacity, _images.at(0), 1.0 - opacity, 0, _images.at(2));

    // display background and overlay image
    cv::imshow(_windowName, _images.at(2));
    cv::waitKey(33);
}
