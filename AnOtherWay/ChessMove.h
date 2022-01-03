#ifndef _CHESSMOVE_H_
#define _CHESSMOVE_H_

#include <SFML/Graphics.hpp>

using namespace sf;

//enum class to define the type of moves on the chess board
enum class MoveType {
        PROMOTION, //promotion for pawn
        LONG_CASTLING, //long castling (King and Rook)
        SHORT_CASTLING, //short castling (King and Rook)
        NONE, //none of the above, a normal move
};

class ChessMove {

private:
    
protected:

public:
    Vector2i _position; //position of the move

    MoveType _type; //type of the move
    
    ChessMove(const Vector2i& pos, MoveType t); //fully-parameterized constructor

    ChessMove(const Vector2i& pos); //partly-parameterized constructor
    
    ChessMove(); //default constructor

    ~ChessMove(); //destructor
};

#endif //_CHESSMOVE_H_