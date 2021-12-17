#ifndef _CHESSMOVE_H_
#define _CHESSMOVE_H_

#include <SFML/Graphics.hpp>

using namespace sf;

enum class MoveType {
        PROMOTION,
        LONG_CASTLING,
        SHORT_CASTLING,
        NONE
};

class ChessMove {

private:
    Vector2i _position;

    MoveType _type;
protected:

public:
    ChessMove(const Vector2i& pos, MoveType t); //fully-parameterized constructor

    ChessMove(const Vector2i& pos); //partly-parameterized constructor
    
    ChessMove(); //default constructor

    ~ChessMove(); //destructor
};

#endif //_CHESSMOVE_H_