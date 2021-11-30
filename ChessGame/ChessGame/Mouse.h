#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

const int PIECE_SIZE = 90;
const int LANDMARK = 24;

class GameMouse {
private:
	Sprite _mousePicture;

	Texture _mouseTexture;

	string _imageLocation; //address

	Vector2i _mousePosition; //position of mouse on the screen

public:
	GameMouse(); //constructor

	~GameMouse(); //destructor

	void setLocation(string location);

	void setImage();

	void getPosition(RenderWindow& window);

	void draw(RenderWindow& window);

	bool checkGetGlobalBounds(Sprite image);

	bool checkGetGlobalBounds(Vector2i v);

	bool checkGetGlobalBounds(Vector2i v, int x, int y);

	Vector2f getPosVector();

	void changeImage(string location); //change the image

	void consolePositionOutput(); //print the position to console
};

#endif
