#include "Knight.h"

Knight::Knight(int c, int r, GameColor color) {
	this->_isSelected = false;
	this->_isErase = false;

	this->_currentPlace.change(c, r);

	this->_pieceColor = color;

	this->setImage();
}

void Knight::setImage() {
	if (this->_pieceColor == GameColor::White) {
		this->_pieceTexture.loadFromFile("images/pieces/WhiteKnight.png");
	}
	else {
		this->_pieceTexture.loadFromFile("images/pieces/BlackKnight.png");
	}

	this->_pieceSprite.setTexture(this->_pieceTexture);
}

void Knight::setPosition() {
	this->_pieceSprite.setPosition(LANDMARK + this->_currentPlace.getColumn() * PIECE_SIZE, LANDMARK + this->_currentPlace.getRow() * PIECE_SIZE);
}

Square Knight::getCurrentPlace() {
	return this->_currentPlace;
}

GameColor Knight::getPieceColor() {
	return this->_pieceColor;
}

void Knight::setSelected() {
	this->_isSelected = true;
}

void Knight::unsetSelected() {
	this->_isSelected = false;
}

void Knight::getPML(PieceBoard pb[][8]) {
	//eight cases:
	//x + 2, y + 1
	//x + 2, y - 1
	//x + 1, y + 2
	//x + 1, y - 2
	//x - 1, y + 2
	//x - 1, y - 2
	//x - 2, y + 1
	//x - 2, y - 1

	//x + 2, y + 1
	Vector2i v(this->_currentPlace.getColumn() + 2, this->_currentPlace.getRow() + 1);
	if (v.x <= BOARD_LENGTH && v.y <= BOARD_WIDTH) {
		checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
	}

	//x + 2, y - 1
	v = Vector2i(this->_currentPlace.getColumn() + 2, this->_currentPlace.getRow() - 1);
	if (v.x <= BOARD_LENGTH && v.y >= 0) {
		checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
	}

	//x + 1, y + 2
	v = Vector2i(this->_currentPlace.getColumn() + 1, this->_currentPlace.getRow() + 2);
	if (v.x <= BOARD_LENGTH && v.y <= BOARD_WIDTH) {
		checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
	}

	//x + 1, y - 2
	v = Vector2i(this->_currentPlace.getColumn() + 1, this->_currentPlace.getRow() - 2);
	if (v.x <= BOARD_LENGTH && v.y >= 0) {
		checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
	}

	//x - 1, y + 2
	v = Vector2i(this->_currentPlace.getColumn() - 1, this->_currentPlace.getRow() + 2);
	if (v.x >= 0 && v.y <= BOARD_WIDTH) {
		checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
	}

	//x - 1, y - 2
	v = Vector2i(this->_currentPlace.getColumn() - 1, this->_currentPlace.getRow() - 2);
	if (v.x >= 0 && v.y >= 0) {
		checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
	}

	//x - 2, y + 1
	v = Vector2i(this->_currentPlace.getColumn() - 2, this->_currentPlace.getRow() + 1);
	if (v.x >= 0 && v.y <= BOARD_WIDTH) {
		checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
	}

	//x - 2, y - 1
	v = Vector2i(this->_currentPlace.getColumn() - 2, this->_currentPlace.getRow() - 1);
	if (v.x >= 0 && v.y >= 0) {
		checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
	}

	//end of cases
}

void Knight::moveToNewPlace(int c, int r) {
	this->_currentPlace.change(c, r);
}