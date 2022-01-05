#ifndef _KING_H_
#define _KING_H_

#include "Piece.h"

class King : public Piece {
private:
    static const int _pieceValue = 10; //value of the King is a special number, if we lose the King, we lose the game
protected:

public:
    //https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
    explicit King(PieceColor pieceColor = PieceColor::WHITE); //fully-parameterized constructor

    ~King();

    //re-define pure virtual methods in class Piece
    int getPieceValue();

    void draw(RenderWindow& window);

    vector<ChessMove> computePossbibleMoves(const vector<vector<Cell>>& cells);

};

#endif // _KING_H_