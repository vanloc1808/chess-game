#ifndef _CELL_H
#define _CELL_H

#include <vector>

//LIBRARIES FOR CELLS ON BOARD

class Cell {
protected:
    int cellCoordinate; // cell's coordinates, we use only int because we will create from 0 to 63

private:
    static std::vector<EmptyCell> cachedEmptyCells;

public:
    //pure virtual function, because we will create different types of cells
    //check if a cell is occupied
    virtual bool isOccupied() = 0; 
    virtual std::string toString() = 0;

public:
    Cell();
    //parameterized constructor, we use it to create cell with coordinates
    Cell(int coordinate);

    //getter for coordinate
    int getCoordinate();

public:
    std::vector<EmptyCell> createCachedEmptyCells();

};

class EmptyCell : public Cell { 
public:
    //parameterized constructor of EmptyCell is the same as the base class
    EmptyCell(int coordinate) : Cell(coordinate) {};

    bool isOccupied();

    std::string toString();

};

class OccupiedCell : public Cell {
//This will be uncommented when we've define class Piece
// private:
//     Piece pieceOnCell;

// public:
//     OccupiedCell(int coordinate, Piece piece) : Cell(coordinate) {
//         this->pieceOnCell = piece;
//     };

public:
    bool isOccupied();

    //Piece getPiece();

    std::string toString();
};

#endif