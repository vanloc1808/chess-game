#ifndef _GAMEUSER_H_
#define _GAMEUSER_H_

#include "Piece.h"
#include "King.h"
#include "Cell.h"
#include "Utility.h"
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

class GameUser {
private:
    int _score;

    PieceColor _userColor;

    unordered_map<PieceType, vector<weak_ptr<Piece>>> _pieces;

protected:

public:
    GameUser(PieceColor color);

    ~GameUser();

    //getters
    int getScore();

    PieceColor getColor();

    //setters
    void setScore(int scr);

    void addPiece(PieceType type, const shared_ptr<Piece>& piece);

    void clearPieces();

    bool isChecked(const vector<vector<Cell>>& cells);

    bool hasLegalMoves(const vector<vector<Cell>>& cells);

    void checkKingSlot(bool check, vector<vector<Cell>>& cells);
};

#endif // _GAMEUSER_H_