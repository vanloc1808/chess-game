#ifndef _PIECE_H
#define _PIECE_H

class PieceType {
private:
    std::string pieceName;

    //values of pieces from this link:
    //https://www.chesskid.com/article/view/chess-pieces-values
    int pieceValue;

public:
    static PieceType PAWN;
    static PieceType KNIGHT;
    static PieceType BISHOP;
    static PieceType ROOK;
    static PieceType QUEEN ;
    static PieceType KING;

public:
    PieceType(std::string name, int value);

    std::string toString();

    bool isEqual(PieceType diffType);

    std::string getPieceName();

    int getPieceValue();
};

PieceType PieceType::PAWN = PieceType("Pawn", 1);
PieceType PieceType::KNIGHT = PieceType("Knight", 3);
PieceType PieceType::BISHOP = PieceType("Bishop", 3);
PieceType PieceType::ROOK = PieceType("Rook", 5);
PieceType PieceType::QUEEN = PieceType("Queen", 9);
PieceType PieceType::KING = PieceType("King", 0); //the KING is special, it has no value because if we lose the king, we lose the game.

#endif