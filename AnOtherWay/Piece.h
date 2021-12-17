#ifndef _PIECE_H_
#define _PIECE_H_

#include <SFML/Graphics.hpp>
#include <map>
#include "Cell.h"
#include "PieceData.h"
#include "ChessMove.h"
#include "Utility.h"

using namespace std;
using namespace sf;

//this is an abstract class
class Piece {
private:

protected:
    static map<PieceColor, map<PieceType, Texture>> _textureMap;

    PieceType _pieceType;

    PieceDirection _pieceDirection;

    PieceColor _pieceColor;

    Sprite _pieceSprite;

    bool _hasMoved = false;

    void loadTexture();
public:
    Piece();

    virtual ~Piece();

    virtual int getPieceValue() = 0;

    virtual void draw(RenderWindow& window) = 0;

    //CellList = 2D vector of Cell
    virtual vector<ChessMove> computePossbibleMoves(const CellList& cells) = 0;

    //getters
    PieceType getPieceType();

    PieceDirection getPieceDirection();

    PieceColor getPieceColor();

    Sprite& getPieceSprite();

    Vector2i getPosition();

    bool getHasMoved();

    void markAsMoved();
};

#endif // _PIECE_H_