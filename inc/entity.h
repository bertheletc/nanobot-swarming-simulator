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
}; // descriptor of entity type

// abstract parent of ALL world objects
class Entity
{
public:
    // METHODS
    Entity(); // Constructor
    ~Entity(); // Destructor
    // getters and setters
    int getID() { return _id; }
    void setPosition(int x, int y);
    void getPosition(int &x, int &y);
    EntityType getType() { return _type; }
    int getSizeRadius() { return _sizeRadius; }
    cv::Scalar getColor() { return _color; }
    bool getFlag() { return _flag; }
    // function to turn on the boolean flag
    void turnOnFlag() { _flag = true; }

protected:
    // METHODS
    virtual void simulate(){}; // method to be overriden by each child class
    
    // ATTRIBUTES
    EntityType _type; // identifies the entity type
    int _id; // every entity object has its own unique id
    int _posX, _posY; // entity position in pixels
    cv::Scalar _color; // rendered color of entity
    int _sizeRadius; // represents the size of the entity (all objects are circles so radius)
    bool _flag; // boolean flag to be used 

    std::vector<std::thread> _threads; // holds all threads that have been launched within this object
    static std::mutex _mtx; // mutex shared by all entity objects for protecting cout 

private:
    static int _idCnt; // global variable for counting object ids
};

#endif