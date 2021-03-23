#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <mutex>
#include <thread>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

enum EntityType
{
    kNone,
    kNanobot,
    kNest,
    kObstacle,
    kPile,
    kPredator,
};

// abstract parent of Obstacle, Nest, and Pile classes
class Entity
{
public:
    // // METHODS
    Entity(); // Constructor
    ~Entity();

    // getter and setter
    int getID() { return _id; }
    void setPosition(int x, int y);
    void getPosition(int &x, int &y);
    EntityType getType() { return _type; }
    int getSizeRadius() { return _sizeRadius; }
    cv::Scalar getColor() { return _color; }
    void turnOnFlag() { _flag = true; }
    bool getFlag() { return _flag; }

protected:
    virtual void simulate(){}; // method to be overriden by each child class

    EntityType _type;                 // identifies the class type
    int _id;                          // every traffic object has its own unique id
    int _posX, _posY;              // vehicle position in pixels
    cv::Scalar _color; // rendered color of object
    int _sizeRadius; // represents the size of the object (all objects are circles)
    bool _flag; 

    std::vector<std::thread> _threads; // holds all threads that have been launched within this object
    static std::mutex _mtx;           // mutex shared by all traffic objects for protecting cout 

private:
    // ???
    static int _idCnt; // global variable for counting object ids
};

#endif