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
    RectangleShape _rect; //rectangle (square) to represent the cell
    RectangleShape _checkedRect;

    CircleShape _highlightedCircle; //cirlce to represent highlighted cell

    //each cell contains at most one piece, so we don't need to use a vector here
    //use a shared pointer of STL, so that we will not have memory leak
    shared_ptr<Piece> _piece;

    CellStatus _status; //status of the cell

    Cell(); //default constructor

    ~Cell(); //destructor

    bool getIsChecked(); //getter for isChecked status

    void highlight(bool highlightCell); //highlight the cell

    void setIsChecked(bool check); //setter for isChecked status

};
#endif // _CELL_H_