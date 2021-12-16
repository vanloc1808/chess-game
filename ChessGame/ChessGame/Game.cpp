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