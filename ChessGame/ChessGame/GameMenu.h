#ifndef _GAMEMENU_H_
#define _GAMEMENU_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "Mouse.h"
#include "EventInput.h"
#include "GameMusic.h"
#include "GameSound.h"
#include "GameWindow.h"

using namespace std;
using namespace sf;

enum class MenuStatus {
	WAIT,
	PLAYING,
	OPTION,
	EXITING,
};

enum class GameMode {
	PvP,
	PvE,
	WAIT,
};

struct Volume {
	int sound;
	int music;
};

class GameMenu {
private:
	Volume _volume;

	GameMouse _menuMouse;

	GameMusic _menuMusic;

	GameSound _menuSound;

	MenuStatus _menuStatus;

	GameWindow _gameWindow;

	EventInput _eventInput;

	GameMode _gameMode;

public:
	GameMenu(); //constructor

	~GameMenu(); //destructor

	void initMouseMusicSound(); //initialize mouse, music and sound

	MenuStatus initMenu(); //initialize menu

	GameMode getGameMode();

	void dragAndDrop(Sprite& s, bool& isMoving, Vector2i pos);

	void setGameVolume(Volume& vol);
};

#endif // !_GAMEMENU_H_

