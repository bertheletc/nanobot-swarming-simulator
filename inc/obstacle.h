#ifndef OBSTACLE_H
#define OBSTACLE_H

// child of Static class
// objects of this class represent the obstacles nanobots must avoid
class Obstacle : public Static {
public:
    // METHODS
    // Constructor
    Obstacle();
    // TODO: find correct format for this function declaration
    double bias() override; // overriden function to calculate the bias

    // ATTRIBUTES

private:
}

#endif