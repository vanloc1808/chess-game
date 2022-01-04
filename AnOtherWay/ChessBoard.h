#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_

#include <SFML/Graphics.hpp>
#include "GameAudioPlayer.h"
#include <vector>
#include <memory>
#include <iostream>
#include "Cell.h"
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "GameUser.h"
#include "Settings.h"
#include "Utility.h"
#include "GameAudioPlayer.h"

using namespace sf;
using namespace std;

class ChessBoard {
private:
    float _cellSize; //size of cell

    RenderWindow& _window; //game window
    //document of RenderWindow of SFML here:
    //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderWindow.php
    //We see others use RenderWindow&, so we do the same

    vector<vector<Cell>> _cells; //the 2D vector of cells

    Vector2i _selectedPosition; //the position of the selected cell

    vector<ChessMove> _possibleMoves; //vector of possible moves

    GameUser _whiteUser; //white player

    GameUser _blackUser; //black player

    shared_ptr<GameUser> _currentUser; //current player

    //the following methods are marked as private to ensure encapsulation
    //the others class will only know the run() and reset() methods
    //they will not know how they process
    void initializeBoard(); //initialize the board

    void populateBoard(); //populate the board

    void drawBoard(); //draw the board

    void showPossibleMoves(const vector<ChessMove>& positions); //show possible positions that can be moved to

    void movePiece(Cell& originCell, Cell& destinationCell); //move the piece from origin cell to destination cell

    void capturePiece(Cell& cell); //capture the piece in the cell

    void promotePiece(Cell& cell); //promote the Pawn

    void clearHighlightedCells(); //clear the highlighted cells

    //document for Mouse class of SFML here:
    //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Mouse.php
    void onMouseClicked(const Vector2i& position); //process the mouse click event

    void onOccupiedCellClicked(const Vector2i& position); //process the mouse click event on occupied cell

    void onHighlightedCellClicked(const Vector2i& position); //process the mouse click event on highlighted cell
protected:

public:
    enum {
        BOARD_WIDTH = 8,
        BOARD_HEIGHT = 8
    };

    ChessBoard(RenderWindow& window); //partly-parameterized constructor

    ChessBoard(const string& name, RenderWindow& window); //fully-parameterized constructor

    ~ChessBoard(); //destructor

    void run(); //run the chessboard

    void reset(); //reset the chessboard
};


#endif // _CHESSBOARD_H_