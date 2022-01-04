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

class Cell;


//this is an abstract class, to define the general class Piece
//we can use this class to define the general class of all chess pieces
//6 classes (King, Queen, Rook, Bishop, Knight, Pawn) inherit from this class
class Piece {
private:

//define the attributes as protected so that the derived classes can access them
protected:
    //map of textures
    //documents of Texture class of SFML here:
    //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Texture.php
    static map<PieceColor, map<PieceType, Texture>> _textureMap; 

    PieceType _pieceType; //type of the piece (K, Q, B, Kn, R, P)

    PieceDirection _pieceDirection; //direction of piece (for pawns)

    PieceColor _pieceColor; //color of piece (B/W)

    //sprite of piece
    //documents of Sprite class of SFML here:
    //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Sprite.php
    Sprite _pieceSprite; 

    //attributes to determine that if this piece has moved or not
    //mostly use for the King and Rook when considering if we can take a castling
    bool _hasMoved = false;

    void loadTexture(); //method for loading texture from file location
public:
    Piece(); //default constructor

    //virtual ~Piece(); //I dont know why it says that there is an error here, so I commented it

    //the following three are pure virtual functions
    //it will be defined in the derived classes
    virtual int getPieceValue() = 0; //get the value of piece

    virtual void draw(RenderWindow& window) = 0; //draw this piece

    virtual vector<ChessMove> computePossbibleMoves(const vector<vector<Cell>>& cells) = 0; //compute the current possible moves of this piece

    //the following six methods are getters for the attributes
    PieceType getPieceType(); //get the type of piece

    PieceDirection getPieceDirection(); //get the direction of piece

    PieceColor getPieceColor(); //get the color of piece

    Sprite& getPieceSprite(); //get the sprite of piece

    Vector2i getPosition(); //get the position of piece

    bool getHasMoved(); //get if this piece has moved or not

    void markAsMoved(); //mark this piece as moved
};

#endif // _PIECE_H_