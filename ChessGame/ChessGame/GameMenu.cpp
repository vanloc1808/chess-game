#include "GameMenu.h"

GameMenu::GameMenu() {

}

GameMenu::~GameMenu() {

}

void GameMenu::initMouseMusicSound() {
	//music
	this->_menuMusic.setMusic("musics/MenuMusic.wav");
	this->_menuMusic.setRepeatedMusic();
	this->_menuMusic.playMusic();

	//sound 
	this->_menuSound.setSoundBuffer("musics/Click.wav");
	this->_menuSound.changeSoundVolume(50);

	//mouse
	this->_menuMouse.setLocation("images/mouses/Mouse1.png");
	this->_menuMouse.setImage();
}

MenuStatus GameMenu::initMenu() {
	this->_volume.music = 40;
	this->_volume.sound = 60;

	this->_menuStatus = MenuStatus::WAIT;

	this->_gameMode = GameMode::WAIT;

	this->_eventInput.setWindow(&(this->_gameWindow));

	this->initMouseMusicSound();

	//initialize images
	Texture background, playButton, gameName, optionButton, exitButton;
	background.loadFromFile("images/menus/Background.png");
	playButton.loadFromFile("images/menus/PlayButton.png");
	gameName.loadFromFile("images/menus/GameName.png");
	optionButton.loadFromFile("images/menus/OptionButton.png");
	exitButton.loadFromFile("images/menus/ExitButton.png");

	Vector2u imageSize;
	imageSize = background.getSize();
	Sprite s1(background);
	Sprite s2(playButton);
	Sprite s3(gameName);
	Sprite s4(optionButton);
	Sprite s5(exitButton);

	//setup game window
	this->_gameWindow.setup("Chess game", imageSize);

	Image gameIcon;
	gameIcon.loadFromFile("images/icons/ChessIcon.png");

	this->_gameWindow.getGameWindow()->setIcon(gameIcon.getSize().x, gameIcon.getSize().y, gameIcon.getPixelsPtr());

	while (this->_gameWindow.isDone() == true) {
		this->_menuMouse.getPosition(*(this->_gameWindow.getGameWindow()));
		this->_eventInput.checkEvent();
		this->_gameWindow.beginDrawing();
		this->_gameWindow.draw(s1);

		if (this->_menuMouse.checkGetGlobalBounds(s2) == true) {
			Texture tempTe;
			this->_menuMouse.changeImage("images/mouses/Mouse2.png");
		}
	}
}