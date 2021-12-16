typedef struct IUnknown IUnknown;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <ctime>
#include "ChessBoard.h"
#include "GameSound.h"
#include "GameMusic.h"
#include "Mouse.h"
#include "Game.h"

using namespace sf;
using namespace std;

void turnoffConsole() {
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);
}

int main() {
	/*ChessBoard cb;

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

	cb.showToConsole();*/

	ShowCursor(false);

	turnoffConsole();

	Game game;
	while (game.getGameStatus() != MenuStatus::EXITING) {
		game.initGame();
		game.handleMenuInput();
	}

	return 0;
}