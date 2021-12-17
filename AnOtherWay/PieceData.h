#ifndef _PIECEDATA_H_
#define _PIECEDATA_H_

//an enum class to define the type of a pieec
enum class PieceType {
    KING,
    QUEEN,
    BISHOP,
    KNIGHT,
    ROOK,
    PAWN,
};

//enum class to define the direction of a piece (used for pawns)
enum class PieceDirection {
    UP = -1,
    DOWN = 1,

};

enum class PieceColor{
    BLACK,
    WHITE,
};

#endif //_PIECEDATA_H_