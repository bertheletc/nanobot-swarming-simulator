#ifndef PILE_H
#define PILE_H

#include "entity.h"
#include "static.h"

// child of Static class
// objects of this class represent the pile of items for nanobots to retrieve
class Pile : public Entity, public Static, public std::enable_shared_from_this<Pile>
{
public:
    // METHODS
    Pile(int id, float bias, int pieces); // Constructor
    // TODO: find correct format for this function declaration
    //double bias() override; // overriden function to calculate the bias
    void removePiece(); // function to remove a single piece from pile
    void removePile(); // function to remove rendered pile from the world
    void simulate();
    void exist();

    // miscellaneous
    std::shared_ptr<Pile> get_shared_this() { return shared_from_this(); }

    // ATTRIBUTES

private:
    // ATTRIBUTES
    int _pieces; // represents the amount of pieces left in the pile for collection (1 piece per nanobot)
};

#endif