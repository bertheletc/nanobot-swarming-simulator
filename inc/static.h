#ifndef STATIC_H
#define STATIC_H

enum VisualState 
{
    kUnseen, 
    kSeen,
};

// abstract parent of Obstacle, Nest, and Heap classes
class Static 
{
public:
    // METHODS
    Static(); // Constructor
    float getBias() { return _bias; }
    VisualState getVisualState() { return _visualState; }
    
protected:
    virtual void exist(){}; // method to be overriden by each child class

    VisualState _visualState;
    int _bias;
    int _timeOn;
};

#endif