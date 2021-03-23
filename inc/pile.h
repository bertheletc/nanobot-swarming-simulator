#ifndef PILE_H
#define PILE_H

#include "entity.h"
#include "static.h"

enum PileStock
{
    kFilled,
    kEmpty,
};

// child of Static class
// objects of this class represent the pile of items for nanobots to retrieve
class Pile : public Entity, public Static, public std::enable_shared_from_this<Pile>
{
public:
    // METHODS
    Pile(int id, int size, float bias, int pieces); // Constructor
    // TODO: find correct format for this function declaration
    //double bias() override; // overriden function to calculate the bias
    void simulate();
    void exist();
    PileStock getPileStock() { return _stock; }
    void removePiece() { _pieces--; }; // Method to add to the collected tally and switch a bot to searching

    // miscellaneous
    std::shared_ptr<Pile> get_shared_this() { return shared_from_this(); }

    // ATTRIBUTES

private:
    // ATTRIBUTES
    PileStock _stock;
    int _pieces; // represents the amount of pieces left in the pile for collection (1 piece per nanobot)
};

#endif