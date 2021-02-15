#ifndef PILE_H
#define PILE_H

// child of Static class
// objects of this class represent the pile of items for nanobots to retrieve
class Pile : public Static {
public:
    // METHODS
    Pile(); // Constructor
    // TODO: find correct format for this function declaration
    double bias() override; // overriden function to calculate the bias
    void removePiece(); // function to remove a single piece from pile
    void removePile(); // function to remove rendered pile from the world

    // ATTRIBUTES

private:
    // ATTRIBUTES
    int _pieces; // represents the amount of pieces left in the pile for collection (1 piece per nanobot)
}

#endif