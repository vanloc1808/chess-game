#include "Queen.h"

Queen::Queen(int c, int r, GameColor color) {
	this->_isSelected = false;
	this->_isErase = false;

	this->_currentPlace.change(c, r);

	this->_pieceColor = color;

	this->setImage();
}

void Queen::setImage() {
	if (this->_pieceColor == GameColor::White) {
		this->_pieceTexture.loadFromFile("images/pieces/WhiteQueen.png");
	}
	else {
		this->_pieceTexture.loadFromFile("images/pieces/BlackQueen.png");
	}

	this->_pieceSprite.setTexture(this->_pieceTexture);
}

void Queen::setPosition() {
	this->_pieceSprite.setPosition(LANDMARK + this->_currentPlace.getColumn() * PIECE_SIZE, LANDMARK + this->_currentPlace.getRow() * PIECE_SIZE);
}

Square Queen::getCurrentPlace() {
	return this->_currentPlace;
}

GameColor Queen::getPieceColor() {
	return this->_pieceColor;
}

void Queen::setSelected() {
	this->_isSelected = true;
}

void Queen::unsetSelected() {
	this->_isSelected = false;
}

void Queen::getPML(PieceBoard pb[][8]) {
	//eight cases:
	//x - 1, y
	//x + 1, y
	//x, y - 1
	//x, y + 1
	//x + 1, y + 1
	//x - 1, y - 1
	//x + 1, y - 1
	//x - 1, y + 1

	//x - 1, y
	Vector2i v(this->_currentPlace.getColumn() - 1, this->_currentPlace.getRow());
	while (v.x >= 0) {
		if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard) {
			addPML(v);

			v += Vector2i(-1, 0);
		}
		else if (this->checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard) {
			addPML(v);

			break;
		}
		else {
			break;
		}
	}

	//x + 1, y
	v = Vector2i(this->_currentPlace.getColumn() + 1, this->_currentPlace.getRow());
	while (v.x <= BOARD_LENGTH) {
		if (checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard) {
			addPML(v);

			v += Vector2i(1, 0);
		}
		else if (checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard) {
			addPML(v);

			break;
		}
		else {
			break;
		}
	}

	//x, y - 1
	v = Vector2i(this->_currentPlace.getColumn(), this->_currentPlace.getRow() - 1);
	while (v.y >= 0) {
		if (checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard) {
			addPML(v);

			v += Vector2i(0, -1);
		}
		else if (checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard) {
			addPML(v);

			break;
		}
		else {
			break;
		}
	}

	//x, y + 1
	v = Vector2i(this->_currentPlace.getColumn(), this->_currentPlace.getRow() + 1);
	while (v.y <= BOARD_WIDTH) {
		if (checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard) {
			addPML(v);

			v += Vector2i(0, 1);
		}
		else if (checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard) {
			addPML(v);

			break;
		}
		else {
			break;
		}
	}

	//x + 1, y + 1
	v = Vector2i(this->_currentPlace.getColumn() + 1, this->_currentPlace.getRow() + 1);
	while (v.x <= BOARD_LENGTH && v.y <= BOARD_WIDTH) {
		if (checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard) {
			addPML(v);

			v += Vector2i(1, 1);
		}
		else if (checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard) {
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
		if (checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard) {
			addPML(v);

			v += Vector2i(-1, -1);
		}
		else if (checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard) {
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
		if (checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard) {
			addPML(v);

			v += Vector2i(1, -1);
		}
		else if (checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard) {
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
		if (checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EmptyBoard) {
			addPML(v);

			v += Vector2i(-1, 1);
		}
		else if (checkPML(v.x, v.y, pb, this->_pieceColor) == PieceBoard::EnemyBoard) {
			addPML(v);

			break;
		}
		else {
			break;
		}
	}

	//end of cases 
}

void Queen::moveToNewPlace(int c, int r) {
	this->_currentPlace.change(c, r);
}