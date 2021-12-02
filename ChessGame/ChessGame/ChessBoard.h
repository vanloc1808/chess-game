#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_

#include <SFML/Graphics.hpp>
#include "PieceSet.h"
#include "GameWindow.h"
#include <string>

using namespace std;
using namespace sf;

const int IMAGE_SIZE = 90;

class ChessBoard {
private:
	Texture _boardTexture; //picture of board

	Sprite _boardSprite; //picture of board

	Texture _selectBlackTexture; //picture of black selection

	Sprite _selectBlackSprite; //picture of black selection

	Texture _selectWhiteTexture; //picture of white selection

	Sprite _selectWhiteSprite; //picture of white selection

	Piece* _pieceMoveSelection; //selected pieces

	Piece* _pieceEatenSelection; //selected eaten pieces

	Texture _possibleMoveTexture; //picture of possible move

	Sprite _possibleMoveSprite; //picture of possible move

	Vector2i boardPosition; //position of board

public:
	PieceBoard _pieceboard[8][8]; //2-dimension array of board

	PieceSet* _whitePieces; //set of white pieces

	PieceSet* _blackPieces; //set of black pieces

private:
	PieceBoard squareColor(int c, int r); //return the number of cell (square) on the board

public:
	ChessBoard(); //constructor

	~ChessBoard(); //destructor

	void createChessBoard(); //create the chess board

	void updateChessBoard(); //update the chess board

	void showToConsole(); //show board to console

	PieceBoard getPieceBoard(int c, int r); //white, black or empty?

	void setBoardImage(string l, string b, string w, string s); //initialize the images

	void drawBoard(GameWindow* w); //draw the board

	Vector2u getBoardImageSize(); //get the size of board image

	void drawSelectedPiece(GameWindow* w); //draw the selected piece

	void setSelectedPiece(Piece* p); //set the selected piece to the pointer

	void setEatenPiece(Piece* p); //set the eaten piece to the pointer

	void showPossibleMove(Piece* p, GameWindow* w, bool check); //show possible move location

	Piece* getSelectedPieceMove();

	Piece* getSelectedPieceEaten();

	void moveToNewPlace(Piece* p, int c, int r); //move the piece to a new position

	void drawEatenPiece(GameWindow* w); //draw the eaten piece

	GameColor winPiece();

	void checkmate();
};

#endif // !_CHESSBOARD_H_
