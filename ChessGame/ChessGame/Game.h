#ifndef _GAME_H_
#define _GAME_H_

#include "ChessBoard.h"
#include "GameWindow.h"
#include "GameMenu.h"
#include "GameMusic.h"
#include "GameSound.h"
#include "Mouse.h"
#include "Player.h"
#include "EventInput.h"
#include "AIPlayer.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

enum class PlayerTurn {
	PLAYER_1,
	PLAYER_2,
};

enum class IconType {
	DRAW,
	NO_DRAW,
	OPTION_BUTTON,
	UNDO_BUTTON,
	INDO_BUTTON,
	WAIT_FOR_CHOOSING,
	NO_WAIT_FOR_CHOOSING,
	PROMOTE_PAWN,
	NO_PROMOTE_PAWN,
};

class Game {
private:
	string _position; //string that contains moves, PvE

	AIPlayer _aiPlayer; //engine game PvE

	IconType _isPawnPromoted; //check if the pawn is promoted

	bool _isCastled; //check if the King is castled (castling)?

	MenuStatus _gameStatus; //game status

	IconType _isChoosingStatus; //check if the icon is being chosen

	IconType _isDrawingStatus; //check if the icon is being drawn

	PlayerTurn _playerTurn; //turn

	PlayerTurn _gameBeginningPlayer; //player who begins the game

	GameMenu _gameMenu; //game menu

	GameMouse _gameMouse; //game mouse

	GameSound _gameSound; //game sound

	GameSound _gameClickingSound; //sound when clicking the mouse button to choose

	GameSound _buttonClickingSound; //sound when clicking the game button

	GameMusic _menuMusic; //music of menu

	GameMusic _inGameMusic; //in-game music

	GameMode _gameMode; //game mode (PvP or PvE)

	GameWindow _gameWindow; //game window

	Player _player1; //player 1

	Player _player2; //player 2

	ChessBoard _chessBoard; //chess board of game

	EventInput _eventInput; //event of game

	Volume _gameVolume; //game volume

	bool _inGameSpriteDrawing; //checking variable, return available moves

	GameColor _playerColor; //color of player, used when in PvE mode

	Vector2i _oldPos; //old position, used when in PvE mode

	Vector2i _newPos; //new position, used when in PvE mode

	string _blackMoves; //moves of black side

	string _whiteMoves; //moves of white side

	//images of game
	//background
	Texture _backgroundTexture;

	Sprite _backgroundSprite; 

	//undo button
	Texture _undoButtonTexture;

	Sprite _undoButtonSprite;

	//indo button
	Texture _indoButtonTexture;

	Sprite _indoButtonSprite;

	//option button
	Texture _optionButtonTexture;

	Sprite _optionButtonSprite;

	//game menu
	Texture _gameMenuTexture;

	Sprite _gameMenuSprite;

	//black pawn promotion
	Texture _blackPawnPromotionTexture;

	Sprite _blackPawnPromotionSprite;

	//white pawn promotion
	Texture _whitePawnPromotionTexture;

	Sprite _whitePawnPromotionSprite;

public:
	Game(); //constructor

	~Game(); //destructor

	void initBackgroundLocation(string location); //initialize the background image location

	void initGameIcon(); //initialize game icon

	Vector2u getBackgroundSize(); //get size of background image

	void initGame(); //initialize the game

	void promotePawnToAPiece(string pieceName);

	void createPvPGame(); //create a PvP game

	void createPvEGame(); //create a PvE game

	void handleMenuInput(); //handle menu

	void showPossibleMove(PieceSet* pieceSet);

	void selectPiecePvP(); //select piece in PvP mode

	void selectPiecePvE(GameColor color); //select piece in PvE mode

	void castlingProcess(PieceSet* pieceSet, int idx);

	void capturingProcess(PieceSet* pieceSet, int check);

	void selectPlaceToMove(); //choose the destination place

	GameWindow* gameGameWindow(); //get game window

	string getMoveString(Vector2i pos); //get move string

	Vector2i moveStringToCoordinate(char a, char b); //get the coordinate of move

	void drawInGameIcon(); //draw icon

	IconType getIconProcessingType(); //get the type of processing icon

	void outputGameMenu(); //output game menu

	void drawPlayerTurn(); //draw player turn 

	MenuStatus getGameStatus(); //get the game status

	void drawChosenPieceToPromote(); //draw the chosen piece to promote pawns

	int winner(); //identify the winner

	void pieceMoveAnimation(Piece* p, Vector2f newPos, Vector2f oldPos); //animation of piece moving

	void drawCheckmate(); //draw checkmate
}; 

#endif // !_GAME_H_

