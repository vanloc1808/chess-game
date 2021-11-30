#ifndef  _GAMEWINDOW_H_
#define _GAMEWINDOW_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;

using namespace std;

class GameWindow {
private:
	RenderWindow _gameWindow; //game window

	Vector2u _windowSize; //size of game window

	string _windowTitle; //name of game window

	bool _isFullScreen; //is in full-screen status?

	bool _isDone; //is in process?

public:
	GameWindow(); //constructor

	~GameWindow(); //destructor

	void create(); //create window

	void close(); //close window

	void setup(const string& title, const Vector2u& size); //set up for window name and window size

	void beginDrawing();

	void endDDrawing();

	bool isDone();

	bool isFullScreen();

	void Draw(Drawable& dr);

	Vector2u getWindowSize(); //get the window size

	RenderWindow* getGameWindow(); //get game window

};

#endif // ! _GAMEWINDOW_H_

