#ifndef NEST_H
#define NEST_H

#include "entity.h"
#include "static.h"

// child of Static class
// objects of this class represent the nest where nanobots go from and come back to
class Nest : public Entity
{
public:
    // METHODS
    Nest(); // Constructor
    // TODO: find correct format for this function declaration
    //double bias() override; // overriden function to calculate the bias
    void pieceRetrieved(); // Method to add to the collected tally and switch a bot to searching

private:
    // ATTRIBUTES
    int _botsContained; // number of bots inside the nest
    int _piecesCollected; // number of pieces retrieved and brought back to the nest
};

#endif