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
    float _cellSize;

    RenderWindow& _window;

    vector<vector<Cell>> _cells;

    Vector2i _selectedPosition;

    vector<ChessMove> _possibleMoves;

    GameUser _whiteUser;

    GameUser _blackUser;

    shared_ptr<GameUser> _currentUser;

    void initializeBoard();

    void populateBoard();

    void drawBoard();

    void showPossibleMoves(const vector<ChessMove>& positions);

    void movePiece(Cell& originCell, Cell& destinationCell);

    void capturePiece(Cell& cell);

    void promotePiece(Cell& cell);

    void clearHighlightedCells();

    void onMouseClicked(const Vector2i& position);

    void onOccupiedCellClicked(const Vector2i& position);

    void onHighlightedCellClicked(const Vector2i& position);
protected:

public:
    enum {
        BOARD_WIDTH = 8,
        BOARD_HEIGHT = 8
    };

    ChessBoard(RenderWindow& window);

    ChessBoard(const string& name, RenderWindow& window);

    void run();

    void reset();
};


#endif // _CHESSBOARD_H_