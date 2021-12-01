#include "Piece.h"

void Piece::addPML(Vector2i pos) {
	this->_possibleLocation.push_back(pos);
}

PieceBoard Piece::checkPML(int c, int r, PieceBoard pb[][8], GameColor color) {
	if (color == GameColor::Black) {
		if (pb[c][r] == PieceBoard::EmptyBoard) {
			return PieceBoard::EmptyBoard;
		}
		else if (pb[c][r] == PieceBoard::WhiteBoard) {
			return PieceBoard::EnemyBoard;
		}
		else {
			return PieceBoard::AllyBoard;
		}
	}
	else {
		if (pb[c][r] == PieceBoard::EmptyBoard) {
			return PieceBoard::EmptyBoard;
		}
		else if (pb[c][r] == PieceBoard::BlackBoard) {
			return PieceBoard::EnemyBoard;
		}
		else {
			return PieceBoard::AllyBoard;
		}
	}
}

void Piece::checkAndAddPML(int c, int r, PieceBoard pb[][8], GameColor color) {
	if (checkPML(c, r, pb, color) == PieceBoard::EmptyBoard || checkPML(c, r, pb, color) == PieceBoard::EnemyBoard) {
		addPML(Vector2i(c, r));
	}
}

void Piece::consolePMLOutput() {
	for (int i = 0; i < this->_possibleLocation.size(); i++) {
		cout << this->_possibleLocation[i].x << " " << this->_possibleLocation[i].y << "\n";
	}
}

void Piece::clearPML() {
	this->_possibleLocation.clear();
}

int Piece::getPMLSize() {
	return this->_possibleLocation.size();
}

Vector2i Piece::getPMLAtIndex(int i) {
	return this->_possibleLocation[i];
}

int Piece::checkinVectorPML(GameMouse* mouse) {
	//aka it is not empty
	if (this->_possibleLocation.empty() == false) { 
		for (int i = 0; i < this->_possibleLocation.size(); i++) {
			if (mouse->checkGetGlobalBounds(this->_possibleLocation[i]) == true) {
				return i;
			}
		}
		return -1;
	}

	return -1;
}

void Piece::setCaptured() {
	this->_isErase = true;
}

void Piece::unsetCaptured() {
	this->_isErase = false;
}

bool Piece::checkPieceChange() {
	if (this->getPieceColor() == GameColor::Black) {
		return (this->getCurrentPlace().getRow() == BOARD_WIDTH);
	}
	else {
		return (this->getCurrentPlace().getRow() == 0);
	}
}

void Piece::consoleCurrentPlaceOutput() {
	cout << "Current place: " << this->getCurrentPlace().getColumn() << ":" << this->getCurrentPlace().getRow() << "\n";
}

void Piece::changeTextureLocation(string fileName) {
	this->_pieceTexture.loadFromFile(fileName);

	this->_pieceSprite.setTexture(this->_pieceTexture);
}