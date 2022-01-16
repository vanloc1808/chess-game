#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "Piece.h"

class Queen : public Piece {
private:
    static const int _pieceValue = 9; //the Quen is the strongest piece, so its value is 9
protected:

public:
    //https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
    explicit Queen(PieceColor pieceColor = PieceColor::WHITE); //fully-parameterized constructor

    ~Queen();

    //re-define pure virtual methods in class Piece
    int getPieceValue();

    void draw(RenderWindow& window);

    vector<ChessMove> computePossbibleMoves(const vector<vector<Cell>>& cells);
};

#endif // _QUEEN_H_