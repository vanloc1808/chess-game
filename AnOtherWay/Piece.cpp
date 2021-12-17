#include "Piece.h"

map<PieceColor, map<PieceType, Texture>> Piece::_textureMap;

void Piece::loadTexture() {
    //check if the texture has been loaded yet, if not, load it
    bool condition1 = Piece::_textureMap.find(this->_pieceColor) == Piece::_textureMap.end();
    bool condition2 = Piece::_textureMap[this->_pieceColor].find(this->_pieceType) == Piece::_textureMap[this->_pieceColor].end();
    if (condition1 || condition2) {
        string fileLocation = utilities::assisstants::getPieceLocation(this->_pieceColor, this->_pieceType);
        Piece::_textureMap[this->_pieceColor][this->_pieceType].loadFromFile(fileLocation);
    }

    //set texture for sprite
    this->_pieceSprite.setTexture(Piece::_textureMap[this->_pieceColor][this->_pieceType]);

    //set scale for sprite
    float xscale = utilities::Settings::getCellSize() / this->_pieceSprite.getTexture()->getSize().x;
    float yscale = utilities::Settings::getCellSize() / this->_pieceSprite.getTexture()->getSize().y;

    this->_pieceSprite.setScale(xscale, yscale);
}

PieceType Piece::getPieceType() {
    return this->_pieceType;
}

PieceDirection Piece::getPieceDirection() {
    return this->_pieceDirection;
}

PieceColor Piece::getPieceColor() {
    return this->_pieceColor;
}

Sprite& Piece::getPieceSprite() {
    return this->_pieceSprite;
}

Vector2i Piece::getPosition() {
    return utilities::assisstants::convertToBoardIndex(this->_pieceSprite.getPosition());
}

bool Piece::getHasMoved() {
    return this->_hasMoved;
}

void Piece::markAsMoved() {
    this->_hasMoved = true;
}