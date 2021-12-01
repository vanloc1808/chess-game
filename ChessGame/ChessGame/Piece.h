#ifndef _PIECE_H_
#define _PIECE_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "GameWindow.h"
#include "Mouse.h"
#include "Square.h"

using namespace std;
using namespace sf;

const int BOARD_LENGTH = 7;
const int BOARD_WIDTH = 7;

enum class GameColor {
	Black,

	White
};

enum class PieceBoard {
	WhiteBoard,

	BlackBoard,

	EmptyBoard,

	EnemyBoard,

	AllyBoard
};

class Piece {
protected:
	Square _currentPlace; //current place of this piece

	GameColor _pieceColor; //color of this piece

	vector<Vector2i> _possibleLocation; //possible destination on which this piece can go to

public:
	bool _isSelected; //this is a variable to check that if this piece is selected

	bool _isErase; //this is a variable to check that if this piece is erased (?)

	Sprite _pieceSprite; //figure of piece

	Texture _pieceTexture; //figure of piece

	virtual void setImage() = 0; //setup image

	virtual void setPosition() = 0; //setup image position

	virtual Square getCurrentPlace() = 0; //get the current place of this piece

	virtual GameColor getPieceColor() = 0; //get the color of this piece

	virtual void setSelected() = 0; //setup the selected piece

	virtual void unsetSelected() = 0; //un-setup the selected piece

	//PML = Possible Move Location

	virtual void getPML(PieceBoard pb[][8]) = 0; //set up the location that this piece can move to

	void addPML(Vector2i pos); //add a new square to possible move location

	PieceBoard checkPML(int c, int r, PieceBoard pb[][8], GameColor color); //check possbible move location

	void checkAndAddPML(int c, int r, PieceBoard pb[][8], GameColor color); //check and add

	void consolePMLOutput(); //output the positions to console

	void clearPML();

	int getPMLSize();

	Vector2i getPMLAtIndex(int i); //get the element i of possible move location

	virtual void moveToNewPlace(int c, int r) = 0; //move the piece to a new position

	int checkinVectorPML(GameMouse* mouse);  //check mouse and possible move (?)

	void setCaptured(); //set the captured status

	void unsetCaptured(); //un-set the captured status

	bool checkPieceChange(); //check piece change

	void consoleCurrentPlaceOutput(); //output the current place to console

	void changeTextureLocation(string fileName);
};

#endif // !_PIECE_H_

