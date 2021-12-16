#include "Game.h"

Game::Game() {
	this->initGame();
}

Game::~Game() {

}

void Game::initBackgroundLocation(string location) {
	this->_backgroundTexture.loadFromFile(location);
	this->_backgroundSprite.setTexture(this->_backgroundTexture);
}

void Game::initGameIcon() {
	this->_undoButtonTexture.loadFromFile("images/icons/UndoButton.png");
	this->_undoButtonSprite.setTexture(this->_undoButtonTexture);

	this->_indoButtonTexture.loadFromFile("images/icons/IndoButton.png");
	this->_indoButtonSprite.setTexture(this->_indoButtonTexture);

	this->_optionButtonTexture.loadFromFile("images/icons/OptionButton.png");
	this->_optionButtonSprite.setTexture(this->_optionButtonTexture);

	this->_undoButtonSprite.setPosition(900, 550);
	this->_indoButtonSprite.setPosition(900, 650);
	this->_optionButtonSprite.setPosition(900, 24);
}

Vector2u Game::getBackgroundSize() {
	return this->_backgroundTexture.getSize();
}

void Game::initGame() {
	this->_blackMoves = "";
	this->_whiteMoves = "";

	this->_inGameSpriteDrawing = false;

	this->_inGameMusic.setMusic("musics/MainMusic.ogg");

	this->_chessBoard.setBoardImage("images/chessboards/ChessBoard.png", "images/chessboards/PieceSelection.png", "images/chessboards/PieceSelection.png", "images/chessboards/Selection.png");
	this->_chessBoard.createChessBoard();

	this->_gameMouse.setLocation("images/mouses/Mouse1.png");

	this->_gameSound.setSoundBuffer("musics/GameSound.wav");

	this->_gameClickingSound.setSoundBuffer("musics/GameClick.wav");
	this->_buttonClickingSound.setSoundBuffer("musics/ButtonClick.wav");

	this->initBackgroundLocation("images/chessboards/Background.png");

	this->_gameMenuTexture.loadFromFile("images/chessboards/GameMenu.png");
	this->_gameMenuSprite.setTexture(this->_gameMenuTexture);

	this->_blackPawnPromotionTexture.loadFromFile("images/chessboards/BlackPawnPromotion.png");
	this->_blackPawnPromotionSprite.setTexture(this->_blackPawnPromotionTexture);
	this->_whitePawnPromotionTexture.loadFromFile("images/chessboards/WhitePawnPromotion.png");
	this->_whitePawnPromotionSprite.setTexture(this->_whitePawnPromotionTexture);

	this->initGameIcon();

	this->_playerTurn = PlayerTurn::PLAYER_1;

	this->_playerColor = GameColor::White;

	this->_isDrawingStatus = IconType::NO_DRAW;
	this->_isChoosingStatus = IconType::NO_WAIT_FOR_CHOOSING;

	this->_gameStatus = MenuStatus::WAIT;

	this->_isPawnPromoted = IconType::NO_PROMOTE_PAWN;

	this->_position = "";

	this->_isCastled = false;
}

void Game::promotePawnToAPiece(string pieceName) {
	this->_gameMouse.changeImage("images/mouses/Mouse2.png");

	if (this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE) {
		this->_buttonClickingSound.playSound();

		if (this->_chessBoard.getSelectedPieceMove()->getPieceColor() == GameColor::White) {
			this->_chessBoard._whitePieces->pawnPromotion(this->_chessBoard.getSelectedPieceMove(), pieceName);
		}
		else {
			this->_chessBoard._blackPieces->pawnPromotion(this->_chessBoard.getSelectedPieceMove(), pieceName);
		}

		this->_isPawnPromoted = IconType::NO_PROMOTE_PAWN;
	}
}

void Game::createPvPGame() {
	this->_inGameMusic.playMusic();
	this->_inGameMusic.setRepeatedMusic();
	this->_inGameMusic.changeMusicVolume(this->_gameVolume.music);
	this->_gameClickingSound.changeSoundVolume(this->_gameVolume.music);
	this->_buttonClickingSound.changeSoundVolume(this->_gameVolume.music);
	this->_gameSound.changeSoundVolume(this->_gameVolume.sound);

	this->_gameWindow.setup("Chess game", this->getBackgroundSize());

	Image icon;
	icon.loadFromFile("images/icons/ChessIcon.png");
	this->_gameWindow.getGameWindow()->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	this->_gameMouse.setImage();
	this->_chessBoard.showToConsole();
	this->_gameWindow.getGameWindow()->setFramerateLimit(60);

	Clock clock;
	double timer = 0, delay = 0.30;

	while (this->_gameWindow.isDone() == true) {
		float time = clock.getElapsedTime().asSeconds();

		this->_eventInput.setWindow(&(this->_gameWindow));
		this->_eventInput.checkEvent();

		this->_gameWindow.beginDrawing();
		this->_gameWindow.draw(this->_backgroundSprite);
		this->_chessBoard.drawBoard(&(this->_gameWindow));

		//draw pieces
		for (int i = 0; i < this->_chessBoard._blackPieces->getPieceNumber(); i++) {
			this->_chessBoard._blackPieces->_pieces[i]->setPosition();

			this->_gameWindow.draw(this->_chessBoard._blackPieces->_pieces[i]->_pieceSprite);
		}

		for (int i = 0; i < this->_chessBoard._whitePieces->getPieceNumber(); i++) {
			this->_chessBoard._whitePieces->_pieces[i]->setPosition();

			this->_gameWindow.draw(this->_chessBoard._whitePieces->_pieces[i]->_pieceSprite);
		} //finish drawing pieces

		if (this->_isChoosingStatus == IconType::NO_WAIT_FOR_CHOOSING) {
			this->selectPiecePvP();

			if (this->_inGameSpriteDrawing == true) {
				this->selectPlaceToMove();
				this->_chessBoard.checkmate(); //check for checkmate

				if (typeid(*(this->_chessBoard.getSelectedPieceMove())) == typeid(Pawn)) {
					if (this->_chessBoard.getSelectedPieceMove()->checkPieceChange() == true) {
						this->_isPawnPromoted = IconType::PROMOTE_PAWN;
					}
				}
				else if (typeid(*(this->_chessBoard.getSelectedPieceMove())) == typeid(King)) {
					if (this->_chessBoard.getSelectedPieceMove()->getPieceColor() == GameColor::Black) {
						this->_isCastled = this->_chessBoard._blackPieces->castling(this->_chessBoard.getSelectedPieceMove(), this->_chessBoard._pieceboard);
					}
					else if (this->_chessBoard.getSelectedPieceMove()->getPieceColor() == GameColor::White) {
						this->_isCastled = this->_chessBoard._whitePieces->castling(this->_chessBoard.getSelectedPieceMove(), this->_chessBoard._pieceboard);
					}
				}
			}
		}

		if (this->_isPawnPromoted == IconType::PROMOTE_PAWN) {
			this->_isChoosingStatus = IconType::WAIT_FOR_CHOOSING;
			this->drawChosenPieceToPromote();

			if (this->_gameMouse.checkGetGlobalBounds(Vector2i(345, 365), 90, 90) == true) { //Rook
				this->promotePawnToAPiece("Rook");
			}
			else if (this->_gameMouse.checkGetGlobalBounds(Vector2i(435, 365), 90, 90) == true) { //Knight
				this->promotePawnToAPiece("Knight");
			}
			else if (this->_gameMouse.checkGetGlobalBounds(Vector2i(525, 365), 90, 90) == true) { //Queen
				this->promotePawnToAPiece("Queen");
			}
			else if (this->_gameMouse.checkGetGlobalBounds(Vector2i(615, 365), 90, 90) == true) { //Bishop
				this->promotePawnToAPiece("Bishop");
			}
			else {
				this->_gameMouse.changeImage("images/mouses/Mouse1.png");
			}

			this->_isChoosingStatus = IconType::NO_WAIT_FOR_CHOOSING;
		}

		this->drawInGameIcon();
		this->drawPlayerTurn();
		this->outputGameMenu();

		this->_chessBoard.drawEatenPiece(&(this->_gameWindow));
		this->_chessBoard.updateChessBoard();

		this->_gameMouse.getPosition(*(this->_gameWindow.getGameWindow()));
		this->_gameMouse.draw(*(this->_gameWindow.getGameWindow()));

		this->_gameWindow.endDDrawing();
	}
}

void Game::createPvEGame() {
	this->_inGameMusic.playMusic();
	this->_inGameMusic.setRepeatedMusic();
	this->_inGameMusic.changeMusicVolume(40);

	this->_chessBoard.createChessBoard();

	this->_gameClickingSound.changeSoundVolume(40);
	this->_buttonClickingSound.changeSoundVolume(60);

	this->_gameWindow.setup("Chess game", this->getBackgroundSize());

	Image icon;
	icon.loadFromFile("images/icons/ChessIcon.png");
	this->_gameWindow.getGameWindow()->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
	this->_gameMouse.setImage();
	this->_chessBoard.showToConsole();

	Clock clock;
	double timer = 0, delay = 0.3;

	while (this->_gameWindow.isDone() == true) {
		this->_gameWindow.getGameWindow()->setFramerateLimit(60);

		float time = clock.getElapsedTime().asSeconds();

		this->_eventInput.setWindow(&(this->_gameWindow));
		this->_eventInput.checkEvent();

		this->_gameWindow.beginDrawing();
		this->_gameWindow.draw(this->_backgroundSprite);

		this->_chessBoard.drawBoard(&(this->_gameWindow));

		for (int i = 0; i < this->_chessBoard._blackPieces->getPieceNumber(); i++) {
			this->_chessBoard._blackPieces->_pieces[i]->setPosition();

			this->_gameWindow.draw(this->_chessBoard._blackPieces->_pieces[i]->_pieceSprite);
		}

		for (int i = 0; i < this->_chessBoard._whitePieces->getPieceNumber(); i++) {
			this->_chessBoard._whitePieces->_pieces[i]->setPosition();

			this->_gameWindow.draw(this->_chessBoard._whitePieces->_pieces[i]->_pieceSprite);
		}

		this->selectPiecePvE(this->_playerColor);

		if (this->_inGameSpriteDrawing == true) {
			this->selectPlaceToMove();
		}

		this->drawInGameIcon();
		this->drawPlayerTurn();
		this->outputGameMenu();

		this->_chessBoard.drawEatenPiece(&(this->_gameWindow));
		this->_chessBoard.updateChessBoard();

		this->_gameMouse.getPosition(*(this->_gameWindow.getGameWindow()));
		this->_gameMouse.draw(*(this->_gameWindow.getGameWindow()));

		this->_gameWindow.endDDrawing();
	}
}

void Game::handleMenuInput() {
	MenuStatus tempStatus = this->_gameMenu.initMenu();

	if (tempStatus == MenuStatus::EXITING) {
		this->_gameStatus = MenuStatus::EXITING;
	}
	else if (tempStatus == MenuStatus::PLAYING) {
		this->_gameStatus = MenuStatus::PLAYING;

		this->_gameMode = this->_gameMenu.getGameMode();

		this->_gameMenu.setGameVolume(this->_gameVolume);

		if (this->_gameMode == GameMode::PvP) {
			this->createPvPGame();
		}
		else if (this->_gameMode == GameMode::PvE) {
			this->createPvEGame();
		}
	}
	else if (tempStatus == MenuStatus::OPTION) {
		//do nothing?
	}
}

void Game::showPossibleMove(PieceSet* pieceSet) {
	for (int i = 0; i < pieceSet->getPieceNumber(); i++) {
		if (this->_gameMouse.checkGetGlobalBounds(pieceSet->_pieces[i]->_pieceSprite) == true) {
			this->_chessBoard._blackPieces->unselectPiece();
			this->_chessBoard._whitePieces->unselectPiece();

			pieceSet->_pieces[i]->setSelected();
			this->_chessBoard.drawSelectedPiece(&(this->_gameWindow));

			if (this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE) {
				this->_gameClickingSound.playSound();
				this->_inGameSpriteDrawing = true;

				this->_chessBoard.setSelectedPiece(pieceSet->_pieces[i]);

				cout << pieceSet->_pieces[i]->getCurrentPlace().getRow() << " ";
				cout << pieceSet->_pieces[i]->getCurrentPlace().getColumn() << "\n";
				this->_chessBoard.showToConsole();

				pieceSet->_pieces[i]->clearPML();
				pieceSet->_pieces[i]->getPML(this->_chessBoard._pieceboard);
				pieceSet->_pieces[i]->consolePMLOutput();
			}
		}
	}
}

void Game::selectPiecePvP() {
	if (this->_playerTurn == PlayerTurn::PLAYER_1) {
		this->showPossibleMove(this->_chessBoard._whitePieces);
	}
	else if (this->_playerTurn == PlayerTurn::PLAYER_2) {
		this->showPossibleMove(this->_chessBoard._blackPieces);
	}

	this->_chessBoard.showPossibleMove(this->_chessBoard.getSelectedPieceMove(), &(this->_gameWindow), this->_inGameSpriteDrawing);

	if (this->_inGameSpriteDrawing == true) {
		this->_chessBoard.drawSelectedPiece(&(this->_gameWindow));
	}
}

void Game::selectPiecePvE(GameColor color) {
	if (color == GameColor::White) {
		this->showPossibleMove(this->_chessBoard._whitePieces);
	}
	else if (color == GameColor::Black) {
		this->showPossibleMove(this->_chessBoard._blackPieces);
	}

	this->_chessBoard.showPossibleMove(this->_chessBoard.getSelectedPieceMove(), &(this->_gameWindow), this->_inGameSpriteDrawing);

	if (this->_inGameSpriteDrawing == true) {
		this->_chessBoard.drawSelectedPiece(&(this->_gameWindow));
	}
}

void Game::castlingProcess(PieceSet* pieceSet, int idx) {
	if (this->_gameMouse.checkGetGlobalBounds(Vector2i(0, idx)) == true) {
		if (this->_eventInput._mouseClickType == ClickType::RIGHT_MOUSE) {
			this->_gameSound.playSound();

			this->_chessBoard.getSelectedPieceMove()->moveToNewPlace(2, idx);
			pieceSet->_pieces[pieceSet->findPieceInVector(pieceSet->cpuSelectionPiece(0, idx))]->moveToNewPlace(3, idx);

			this->_inGameSpriteDrawing = false;
			this->_isCastled = false;
		}
	}
	else if (this->_gameMouse.checkGetGlobalBounds(Vector2i(7, idx)) == true) {
		if (this->_eventInput._mouseClickType == ClickType::RIGHT_MOUSE) {
			this->_gameSound.playSound();

			this->_chessBoard.getSelectedPieceMove()->moveToNewPlace(6, idx);
			pieceSet->_pieces[pieceSet->findPieceInVector(pieceSet->cpuSelectionPiece(7, idx))]->moveToNewPlace(5, idx);

			this->_inGameSpriteDrawing = false;
			this->_isCastled = false;
		}
	}
}

void Game::capturingProcess(PieceSet* pieceSet, int check) {
	for (int i = 0; i < pieceSet->getPieceNumber(); i++) {
		bool condition1 = pieceSet->_pieces[i]->getCurrentPlace().getColumn() == this->_chessBoard.getSelectedPieceMove()->getPMLAtIndex(check).x;
		bool condition2 = pieceSet->_pieces[i]->getCurrentPlace().getRow() == this->_chessBoard.getSelectedPieceMove()->getPMLAtIndex(check).y;

		if (condition1 && condition2) {
			pieceSet->unselecEaten();

			this->_chessBoard.setEatenPiece(pieceSet->_pieces[i]);

			pieceSet->erasePiece();
		}
	}
}

void Game::selectPlaceToMove() {
	string res;

	int check = this->_chessBoard.getSelectedPieceMove()->checkinVectorPML(&(this->_gameMouse));

	if (check != -1) {
		this->_oldPos = Vector2i(this->_chessBoard.getSelectedPieceMove()->getCurrentPlace().getColumn(), this->_chessBoard.getSelectedPieceMove()->getCurrentPlace().getRow());

		if (this->_isCastled == true) {
			if (this->_chessBoard.getSelectedPieceMove()->getPieceColor() == GameColor::White) {
				this->castlingProcess(this->_chessBoard._whitePieces, 7);
			}
			else if (this->_chessBoard.getSelectedPieceMove()->getPieceColor() == GameColor::Black) {
				this->castlingProcess(this->_chessBoard._blackPieces, 0);
			}

			if (this->_gameMode == GameMode::PvP && this->_isCastled == false) {
				if (this->_playerTurn == PlayerTurn::PLAYER_1) {
					this->_playerTurn = PlayerTurn::PLAYER_2;
				}
				else {
					this->_playerTurn = PlayerTurn::PLAYER_1;
				}
			}
		}
		else if (this->_isCastled == false && this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE) {
			this->_inGameSpriteDrawing = false;

			if (this->_chessBoard.getSelectedPieceMove()->getPieceColor() == GameColor::White) {
				this->capturingProcess(this->_chessBoard._blackPieces, check);
			}
			else if (this->_chessBoard.getSelectedPieceMove()->getPieceColor() == GameColor::Black) {
				this->capturingProcess(this->_chessBoard._whitePieces, check);
			}

			Vector2f tempNewPos = Vector2f(this->_chessBoard.getSelectedPieceMove()->getPMLAtIndex(check).x * 90 + 24, this->_chessBoard.getSelectedPieceMove()->getPMLAtIndex(check).y * 90 + 24);
			Vector2f tempOldPos = Vector2f(this->_chessBoard.getSelectedPieceMove()->getCurrentPlace().getColumn() * 90 + 24, this->_chessBoard.getSelectedPieceMove()->getCurrentPlace().getRow() * 90 + 24);
			this->pieceMoveAnimation(this->_chessBoard.getSelectedPieceMove(), tempNewPos, tempOldPos);

			this->_gameSound.playSound();

			this->_chessBoard.getSelectedPieceMove()->moveToNewPlace(this->_chessBoard.getSelectedPieceMove()->getPMLAtIndex(check).x, this->_chessBoard.getSelectedPieceMove()->getPMLAtIndex(check).y);
			this->_chessBoard.getSelectedPieceMove()->getPML(this->_chessBoard._pieceboard);

			cout << this->_chessBoard.getSelectedPieceMove()->getPMLAtIndex(check).x << " " << this->_chessBoard.getSelectedPieceMove()->getPMLAtIndex(check).y << "\n";

			if (this->_gameMode == GameMode::PvP) {
				if (this->_playerTurn == PlayerTurn::PLAYER_1) {
					this->_playerTurn = PlayerTurn::PLAYER_2;
				}
				else {
					this->_playerTurn = PlayerTurn::PLAYER_1;
				}
			}
			else {
				this->_newPos = Vector2i(this->_chessBoard.getSelectedPieceMove()->getPMLAtIndex(check).x, this->_chessBoard.getSelectedPieceMove()->getPMLAtIndex(check).y);
				
				cout << "Old position: " << this->_oldPos.x << " " << this->_oldPos.y << "\n";
				cout << "New position: " << this->_newPos.x << " " << this->_newPos.y << "\n";

				this->_position += this->getMoveString(this->_oldPos) + getMoveString(this->_newPos) + " ";

				res = this->_aiPlayer.getNextMove(this->_position);

				this->_oldPos = this->moveStringToCoordinate(res[0], res[1]);
				cout << this->_oldPos.x << " " << this->_oldPos.y << "\n";
				this->_newPos = this->moveStringToCoordinate(res[2], res[3]);
				cout << this->_newPos.x << " " << this->_newPos.y << "\n";

				if (this->_playerColor == GameColor::White) {
					this->_chessBoard.setSelectedPiece(this->_chessBoard._blackPieces->cpuSelectionPiece(this->_oldPos.x, this->_oldPos.y));
					if (this->_chessBoard.getSelectedPieceMove()->getPieceColor() == GameColor::Black) {
						for (int i = 0; i < this->_chessBoard._whitePieces->getPieceNumber(); i++) {
							bool condition1 = this->_chessBoard._whitePieces->_pieces[i]->getCurrentPlace().getColumn() == this->_newPos.x;
							bool condition2 = this->_chessBoard._whitePieces->_pieces[i]->getCurrentPlace().getRow() == this->_newPos.y;

							if (condition1 && condition2) {
								this->_chessBoard._whitePieces->unselecEaten();
								this->_chessBoard.setEatenPiece(this->_chessBoard._whitePieces->_pieces[i]);
								this->_chessBoard._whitePieces->erasePiece();
							}
						}
					}

					Vector2f otherNewPos = Vector2f(this->_newPos.x * 90 + 24, this->_newPos.y * 90 + 24);
					Vector2f otherOldPos = Vector2f(this->_oldPos.x * 90 + 24, this->_oldPos.y * 90 + 24);
					this->pieceMoveAnimation(this->_chessBoard.getSelectedPieceMove(), otherNewPos, otherOldPos);

					this->_gameSound.playSound();

					this->_chessBoard.getSelectedPieceMove()->moveToNewPlace(this->_newPos.x, this->_newPos.y);
				}

				this->_position += res + " ";
			}
		}
	}
}

GameWindow* Game::getGameWindow() {
	return &(this->_gameWindow);
}

string Game::getMoveString(Vector2i pos) {
	string res;

	res += char(pos.x + 97);
	res += char(7 - pos.y + 49);

	return res;
}

Vector2i Game::moveStringToCoordinate(char a, char b) {
	int x = (int)a - 97;
	int y = 7 - (int)b + 49;

	return Vector2i(x, y);
}

void Game::drawInGameIcon() {
	this->_gameWindow.draw(this->_optionButtonSprite);
	this->_gameWindow.draw(this->_undoButtonSprite);
	this->_gameWindow.draw(this->_indoButtonSprite);
}

IconType Game::getIconProcessingType() {
	if (this->_gameMouse.checkGetGlobalBounds(this->_optionButtonSprite) == true) {
		this->_gameMouse.changeImage("images/mouses/Mouse2.png");

		if (this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE) {
			cout << "Option button\n";

			this->_isDrawingStatus = IconType::DRAW;

			this->_buttonClickingSound.playSound();

			return IconType::OPTION_BUTTON;
		}
	}
	else if (this->_gameMouse.checkGetGlobalBounds(this->_undoButtonSprite) == true) {
		this->_gameMouse.changeImage("images/mouses/Mouse2.png");

		if (this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE) {
			cout << "Undo button\n";

			return IconType::UNDO_BUTTON;
		}
	}
	else if (this->_gameMouse.checkGetGlobalBounds(this->_indoButtonSprite) == true) {
		this->_gameMouse.changeImage("images/mouses/Mouse2.png");

		if (this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE) {
			cout << "Indo butotn\n";

			return IconType::INDO_BUTTON;
		}
	}
	else {
		this->_gameMouse.changeImage("images/mouses/Mouse1.png");
	}
}

void Game::outputGameMenu() {
	if (this->getIconProcessingType() == IconType::OPTION_BUTTON && this->_isDrawingStatus == IconType::DRAW) {
		this->_isChoosingStatus = IconType::WAIT_FOR_CHOOSING;

		this->_gameWindow.draw(this->_gameMenuSprite);

		if (this->_gameMouse.checkGetGlobalBounds(Vector2i(325, 360), 90, 90) == true) { //save button
			this->_gameMouse.changeImage("images/mouses/Mouse2.png");
		}
		else if (this->_gameMouse.checkGetGlobalBounds(Vector2i(465, 360), 90, 90) == true) { //play or pause music button
			this->_gameMouse.changeImage("images/mouses/Mouse2.png");

			if (this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE) {
				this->_buttonClickingSound.playSound();

				if (this->_inGameMusic.getMusicStatus() == MusicStatus::PLAY) {
					this->_inGameMusic.pauseMusic();
				}
				else {
					this->_inGameMusic.playMusic();
				}
			}
		}
		else if (this->_gameMouse.checkGetGlobalBounds(Vector2i(600, 360), 90, 90) == true) { //exit button
			this->_gameMouse.changeImage("images/mouses/Mouse2.png");

			if (this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE) {
				this->_buttonClickingSound.playSound();

				this->_inGameMusic.stopMusic();

				this->_gameWindow.close();
			}
		}
		else if (this->_gameMouse.checkGetGlobalBounds(Vector2i(690, 230), 45, 45) == true) {
			this->_gameMouse.changeImage("images/mouses/Mouse2.png");

			if (this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE) {
				this->_buttonClickingSound.playSound();

				this->_isDrawingStatus = IconType::NO_DRAW;

				this->_isChoosingStatus = IconType::NO_WAIT_FOR_CHOOSING;
			}
		}
		else {
			this->_gameMouse.changeImage("images/mouses/Mouse1.png");
		}

		this->_gameMouse.consolePositionOutput();
	}
}