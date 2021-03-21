#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

enum EntityType
{
    kNone,
    kNanobot,
    kNest,
    kObstacle,
    kPile,
    kPredator,
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
}; 

// abstract parent of Obstacle, Nest, and Pile classes
class Entity
{
public:
    // // METHODS
    Entity(); // Constructor

    // getter and setter
    int getID() { return _id; }
    void setPosition(int x, int y);
    void getPosition(int &x, int &y);
    EntityType getType() { return _type; }

protected:
    EntityType _type;                 // identifies the class type
    int _id;                          // every traffic object has its own unique id
    int _posX, _posY;              // vehicle position in pixels
    // TODO: change this to a smart pointer because it will be accessed by many objects
    Color _color; // rendered color of object
    float _sizeRadius; // represents the size of the object (all objects are circles) 

private:
    // ???
    static int _idCnt; // global variable for counting object ids
};

#endif