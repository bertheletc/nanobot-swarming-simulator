#ifndef PILE_H
#define PILE_H

#include "entity.h"
#include "static.h"

enum PileStock
{
    kFilled,
    kEmpty,
}; // tells nanobots if there are pieces to take

// child of Entity and Static classes
// objects of this class represent the pile of pieces for nanobots to retrieve
class Pile : public Entity, public Static, public std::enable_shared_from_this<Pile>
{
public:
    // METHODS
    Pile(int id, int size, float bias, int pieces); // Constructor
    // FUTURE IMPROVEMENTS: WASN'T ABLE TO IMPLEMENT IN TIME
    // // overriden methods from abstract Dynamic and Entity classes
    // void simulate();
    // void exist();
    // getters and setters
    PileStock getPileStock() { return _stock; }
    void setPileStockEmpty() { _stock = PileStock::kEmpty; }
    int getPiecesLeft() { return _pieces; }
    // method to add to the collected tally and switch a bot to searching
    void removePiece() { _pieces--; };

    // miscellaneous
    std::shared_ptr<Pile> get_shared_this() { return shared_from_this(); }

private:
    // ATTRIBUTES
    PileStock _stock; // tells if pile has pieces or is empty
    int _pieces; // represents the amount of pieces left in the pile for collection (1 piece per nanobot)
};

#endif