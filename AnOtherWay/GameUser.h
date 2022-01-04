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
    int _score; //score of this player

    PieceColor _userColor; //color of this player

    unordered_map<PieceType, vector<weak_ptr<Piece>>> _pieces; //pieces of this player
    //weak_ptr is used to hold an object that is managed by share_ptr
    //documents of weak_ptr here:
    //https://en.cppreference.com/w/cpp/memory/weak_ptr

protected:

public:
    GameUser(PieceColor color); //constructor

    ~GameUser(); //destructor

    //the following two are getters
    int getScore(); //getter for score

    PieceColor getColor(); //getter for color

    void setScore(int scr); //setter for score

    void addPiece(PieceType type, const shared_ptr<Piece>& piece); //add a piece to this player

    void clearPieces(); //clear piece of this player

    bool isChecked(const vector<vector<Cell>>& cells); //check if this player is checked

    bool hasLegalMoves(const vector<vector<Cell>>& cells); //check if this player has legal moves

    void checkKingCell(bool check, vector<vector<Cell>>& cells); //check the King cell of this player
};

#endif // _GAMEUSER_H_