#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <thread>

// forward declaration
class World;

enum EntityType
{
    none,
    nanobot,
    nest,
    obstacle,
    pile,
    predator,
};

enum Color 
{
    blue, 
    green, 
    red, 
    yellow, 
    orange,
    purple, 
    black,
}; //

// abstract parent of Obstacle, Nest, and Heap classes
class Entity
{
public:
    // // METHODS
    Entity(); // Constructor
    ~Entity(); // Destructor

    // getter and setter
    int getID() { return _id; }
    void setPosition(double x, double y);
    void getPosition(double &x, double &y);
    EntityType getType() { return _type; }

    virtual void simulate(){}; // method to be overriden by each child class

protected:
    EntityType _type;                 // identifies the class type
    int _id;                          // every traffic object has its own unique id
    double _posX, _posY;              // vehicle position in pixels
    // TODO: change this to a smart pointer because it will be accessed by many objects
    World *world; // pointer to instance of World that the Static object belongs to
    Color color; // rendered color of object
    float sizeRadius; // represents the size of the object (all objects are circles) 
    std::vector<std::thread> threads; // holds all threads that have been launched within this object

    // // ???
    // std::vector<std::thread> threads; // holds all threads that have been launched within this object
    // static std::mutex _mtx;           // mutex shared by all traffic objects for protecting cout 

private:
    // ???
    static int _idCnt; // global variable for counting object ids
    
};

#endif