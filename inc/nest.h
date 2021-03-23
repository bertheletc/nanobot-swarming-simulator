#ifndef NEST_H
#define NEST_H

#include "entity.h"
#include "static.h"

// child of Entity and Static classes
// objects of this class represent the nest where nanobots go from and come back to with pieces
class Nest : public Entity, public Static, public std::enable_shared_from_this<Nest>
{
public:
    // METHODS
    Nest(int id, int size, float bias, int pilePieces); // Constructor
    void depositPiece() { _piecesCollected++; }; // Method to add to the collected tally and switch a bot to searching
    int getPiecesCollected() { return _piecesCollected; }
    int getPiecesToCollect() { return _piecesToCollect; }

    // miscellaneous
    std::shared_ptr<Nest> get_shared_this() { return shared_from_this(); }

private:
    // ATTRIBUTES
    int _piecesCollected; // number of pieces retrieved and brought back to the nest
    int _piecesToCollect;
};

#endif