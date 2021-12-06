#include <iostream>
#include "ChessBoard.h"

int main() {
	ChessBoard cb;

	cb.createChessBoard();

	cout << "Initialization:\n";

	cb.showToConsole();

	system("pause");

	for (int i = 0; i < 16; i++) {
		cb.movePieceToNewPlace(cb._blackPieces->_pieces[i], cb._blackPieces->_pieces[i]->getCurrentPlace().getColumn(), cb._blackPieces->_pieces[i]->getCurrentPlace().getRow() + 1);
		cb.movePieceToNewPlace(cb._whitePieces->_pieces[i], cb._whitePieces->_pieces[i]->getCurrentPlace().getColumn(), cb._whitePieces->_pieces[i]->getCurrentPlace().getRow() - 1);
	}


	cb.updateChessBoard();

	cout << "After updating:\n";

	cb.showToConsole();

	return 0;
}