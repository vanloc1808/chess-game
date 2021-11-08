#include <iostream>
#include "Cell.h"

//here we don't check the conditions for it to be a valid cell
//because we know that it is valid (only we can create it, users can't)
Cell::Cell(int coordinate) {
    this->cellCoordinate = coordinate;
}

int Cell::getCoordinate() {
    return this->cellCoordinate;
}


//of course an empty cell isn't occupied
bool EmptyCell::isOccupied() {
    return false;
}

std::string EmptyCell::toString() {
    return "-";
}

bool OccupiedCell::isOccupied() {
    return true;
}