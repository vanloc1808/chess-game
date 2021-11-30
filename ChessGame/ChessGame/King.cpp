#include "King.h"

King::King(int c, int r, GameColor color) {
	this->_isSelected = false;
	this->_isErase = false;

	this->_currentPlace.change(c, r);

	this->_pieceColor = color;

	//this->setImage();
}

void King::setImage() {
	if (this->_pieceColor == GameColor::White) {
		cout << "Opened white file!\n";
		this->_pieceTexture.loadFromFile("images/pieces/WhiteKing.png");
	}
	else {
		cout << "Opened black file!\n";
		this->_pieceTexture.loadFromFile("images/pieces/BlackKing.png");
	}

	this->_pieceSprite.setTexture(this->_pieceTexture);
}

void King::setPosition() {
	this->_pieceSprite.setPosition(LANDMARK + this->_currentPlace.getColumn() * PIECE_SIZE, LANDMARK + this->_currentPlace.getRow() * PIECE_SIZE);
}

Square King::getCurrentPlace() {
	return this->_currentPlace;
}

GameColor King::getPieceColor() {
	return this->_pieceColor;
}

void King::setSelected() {
	this->_isSelected = true;
}

void King::unsetSelected() {
	this->_isSelected = false;
}

void King::getPML(PieceBoard pb[][8]) {
	if (this->_pieceColor == GameColor::White) {
		Vector2i v(this->_currentPlace.getColumn() - 1, this->_currentPlace.getRow() - 1);

		if (v.x >= 0 && v.y >= 0) {
			for (int i = 0; i < 3; i++, v.y++) {
				if (v.y >= 0 && v.y <= BOARD_WIDTH) {
					checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
				}
			}
		}

		v = Vector2i(this->_currentPlace.getColumn() + 1, this->_currentPlace.getRow() - 1);
		if (v.x <= BOARD_LENGTH && v.y >= 0) {
			for (int i = 0; i < 3; i++, v.y++) {
				if (v.y >= 0 && v.y <= BOARD_WIDTH) {
					checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
				}
			}
		}

		v = Vector2i(this->_currentPlace.getColumn(), this->_currentPlace.getRow() + 1);
		if (v.y <= BOARD_LENGTH) {
			checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
		}

		v = Vector2i(this->_currentPlace.getColumn(), this->_currentPlace.getRow() - 1);
		if (v.y >= 0) {
			checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
		}
	}
	else {
		Vector2i v(this->_currentPlace.getColumn() - 1, this->_currentPlace.getRow() + 1);
		if (v.x >= 0 && v.x <= BOARD_LENGTH) { /**/
			for (int i = 0; i < 3; i++, v.y--) {
				if (v.y >= 0 && v.y <= BOARD_WIDTH) {
					checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
				}
			}
		}

		v = Vector2i(this->_currentPlace.getColumn() + 1, this->_currentPlace.getRow() + 1);
		if (v.x >= 0 && v.x <= BOARD_LENGTH) {
			for (int i = 0; i < 3; i++, v.y--) {
				if (v.y >= 0 && v.y <= BOARD_WIDTH) {
					checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
				}
			}
		}

		v = Vector2i(this->_currentPlace.getColumn(), this->_currentPlace.getRow() + 1);
		if (v.y <= BOARD_LENGTH) {
			checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
		}

		v = Vector2i(this->_currentPlace.getColumn(), this->_currentPlace.getRow() - 1);
		if (v.y >= 0) {
			checkAndAddPML(v.x, v.y, pb, this->_pieceColor);
		}
	}
}

void King::moveToNewPlace(int r, int c) {

}