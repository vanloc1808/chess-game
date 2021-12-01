#include "Pawn.h"

Pawn::Pawn(int c, int r, GameColor color) {
	this->_isSelected = false;
	this->_isErase = false;

	this->_isFirstMove = true;

	this->_currentPlace.change(c, r);

	this->_pieceColor = color;

	this->setImage();
}

void Pawn::setImage() {
	if (this->_pieceColor == GameColor::White) {
		this->_pieceTexture.loadFromFile("images/pieces/WhitePawn.png");
	}
	else {
		this->_pieceTexture.loadFromFile("images/pieces/BlackPawn.png");
	}

	this->_pieceSprite.setTexture(this->_pieceTexture);
}

void Pawn::setPosition() {
	this->_pieceSprite.setPosition(LANDMARK + this->_currentPlace.getColumn() * PIECE_SIZE, LANDMARK + this->_currentPlace.getRow() * PIECE_SIZE);
}

Square Pawn::getCurrentPlace() {
	return this->_currentPlace;
}

GameColor Pawn::getPieceColor() {
	return this->_pieceColor;
}

void Pawn::setSelected() {
	this->_isSelected = true;
}

void Pawn::unsetSelected() {
	this->_isSelected = false;
}

void Pawn::getPML(PieceBoard pb[][8]) {
	if (this->_pieceColor == GameColor::White) {
		Vector2i v(this->_currentPlace.getColumn(), this->_currentPlace.getRow() - 1);
		if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard && v.y >= 0) {
			addPML(v);
		}

		v = Vector2i(this->_currentPlace.getColumn() + 1, this->_currentPlace.getRow() - 1);
		if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard && v.x <= BOARD_LENGTH && v.y >= 0) {
			addPML(v);
		}

		v = Vector2i(this->_currentPlace.getColumn() - 1, this->_currentPlace.getRow() - 1);
		if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard && v.x >= 0 && v.y >= 0) {
			addPML(v);
		}

		if (this->_isFirstMove == true) {
			//do not need to check bound because this is first move
			v = Vector2i(this->_currentPlace.getColumn(), this->_currentPlace.getRow() - 2);
			if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard) {
				addPML(v);
			}
		}
	}
	else {
		Vector2i v(this->_currentPlace.getColumn(), this->_currentPlace.getRow() + 1);
		if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard && v.y <= BOARD_LENGTH) {
			addPML(v);
		}

		v = Vector2i(this->_currentPlace.getColumn() + 1, this->_currentPlace.getRow() + 1);
		if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard && v.x <= BOARD_WIDTH && v.y <= BOARD_LENGTH) {
			addPML(v);
		}

		v = Vector2i(this->_currentPlace.getColumn() - 1, this->_currentPlace.getRow() + 1);
		if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard && v.x >= 0 && v.y <= BOARD_LENGTH) {
			addPML(v);
		}

		if (this->_isFirstMove == true) {
			//do not need to check bound because this is first move
			v = Vector2i(this->_currentPlace.getColumn(), this->_currentPlace.getRow() + 2);
			if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard) {
				addPML(v);
			}
		}
	}
}

void Pawn::moveToNewPlace(int c, int r) {
	this->_currentPlace.change(c, r);
	this->setFirstMoveFalse();
}

bool Pawn::getFirstMove() {
	return this->_isFirstMove;
}

void Pawn::setFirstMoveFalse() {
	this->_isFirstMove = false;
}