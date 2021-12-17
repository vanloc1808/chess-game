#ifndef _CELL_H_
#define _CELL_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Settings.h"
#include "Piece.h"

using namespace std;
using namespace sf;

//enum class tell the status of a cell (square) in the board
enum class CellStatus {
    EMPTY,
    OCCUPIED,
    HIGHLIGHTED,
};

//"forward" the definition of Piece class in Piece.h 
class Piece; 

class Cell {
private:
    bool _isChecked = false;
protected:

public:
    RectangleShape _rect; //it's a square actually
    RectangleShape _checkedRect;

    CircleShape _highlightedCircle;

    shared_ptr<Piece> _piece; //at most one piece on each cell, so we use the pointer, not the vector

    CellStatus _status;

    bool getIsChecked();

    void highlight(bool highlightSlot);

    void setIsChecked(bool check);

};
#endif // _CELL_H_