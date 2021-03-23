#ifndef STATIC_H
#define STATIC_H

enum VisualState 
{
    kUnseen, 
    kSeen,
}; // describes if static object is seen by nanobots

// abstract parent of Obstacle, Nest, and Pile classes
class Static 
{
public:
    // METHODS
    Static(); // Constructor
    // getters
    float getBias() { return _bias; }
    VisualState getVisualState() { return _visualState; }
    
protected:
    // METHODS
    virtual void exist(){}; // method to be overriden by each child class
    
    // ATTRIBUTES
    VisualState _visualState; // visual state of static object as seen by nanobots
    int _bias; // amount of bias injected into nanobot movement if it is seen
    // FUTURE IMPROVEMENTS: WASN'T ABLE TO IMPLEMENT IN TIME
    //int _timeOn; 
};

#endif