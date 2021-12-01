#include "Bishop.h"

Bishop::Bishop(int c, int r, GameColor color) {
	this->_isSelected = false;
	this->_isErase = false;

	this->_currentPlace.change(c, r);

	this->_pieceColor = color;

	this->setImage();
}

void Bishop::setImage() {
	if (this->_pieceColor == GameColor::White) {
		this->_pieceTexture.loadFromFile("images/pieces/WhiteBishop.png");
	}
	else {
		this->_pieceTexture.loadFromFile("images/pieces/BlackBishop.png");
	}

	this->_pieceSprite.setTexture(this->_pieceTexture);
}

void Bishop::setPosition() {
	this->_pieceSprite.setPosition(LANDMARK + this->_currentPlace.getColumn() * PIECE_SIZE, LANDMARK + this->_currentPlace.getRow() * PIECE_SIZE);
}

Square Bishop::getCurrentPlace() {
	return this->_currentPlace;
}

GameColor Bishop::getPieceColor() {
	return this->_pieceColor;
}

void Bishop::setSelected() {
	this->_isSelected = true;
}

void Bishop::unsetSelected() {
	this->_isSelected = false;
}

void Bishop::getPML(PieceBoard pb[][8]) {
	//four cases:
	//x + 1, y + 1
	//x + 1, y - 1
	//x - 1, y + 1
	//x - 1, y - 1

	//x + 1, y + 1
	Vector2i v(this->_currentPlace.getColumn() + 1, this->_currentPlace.getRow() + 1);
	while (v.x <= BOARD_LENGTH && v.y <= BOARD_WIDTH) {
		if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard) {
			addPML(v);

			v += Vector2i(1, 1);
		}
		else if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard) {
			addPML(v);
			break;
		}
		else {
			break;
		}
	}

	//x + 1, y - 1
	v = Vector2i(this->_currentPlace.getColumn() + 1, this->_currentPlace.getRow() - 1);
	while (v.x <= BOARD_LENGTH && v.y >= 0) {
		if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard) {
			addPML(v);

			v += Vector2i(1, -1);
		}
		else if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard) {
			addPML(v);
			break;
		}
		else {
			break;
		}
	}

	//x - 1, y + 1
	v = Vector2i(this->_currentPlace.getColumn() - 1, this->_currentPlace.getRow() + 1);
	while (v.x >= 0 && v.y <= BOARD_WIDTH) {
		if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard) {
			addPML(v);

			v += Vector2i(-1, 1);
		}
		else if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard) {
			addPML(v);
			break;
		}
		else {
			break;
		}
	}

	//x - 1, y - 1
	v = Vector2i(this->_currentPlace.getColumn() - 1, this->_currentPlace.getRow() - 1);
	while (v.x >= 0 && v.y >= 0) {
		if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard) {
			addPML(v);

			v += Vector2i(-1, -1);
		}
		else if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard) {
			addPML(v);
			break;
		}
		else {
			break;
		}
	}

	//end of all cases
}

void Bishop::moveToNewPlace(int c, int r) {
	this->_currentPlace.change(c, r);
}