#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "Piece.h"

class Bishop : public Piece {
private:
    static const int _pieceValue = 3;
protected:

public:
    //https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
    explicit Bishop(PieceColor pieceColor = PieceColor::WHITE); //fully-parameterized constructor

    ~Bishop();

    //re-define pure virtual methods in class Piece
    int getPieceValue();

    void draw(RenderWindow& window);

    vector<ChessMove> computePossbibleMoves(const vector<vector<Cell>>& cells);

};

#endif // _BISHOP_H_