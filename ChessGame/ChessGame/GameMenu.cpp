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
		this->_menuMouse.getPosition(*(this->_gameWindow).getGameWindow());
		this->_eventInput.checkEvent();
		this->_gameWindow.beginDrawing();
		this->_gameWindow.draw(s1);

		if (this->_menuMouse.checkGetGlobalBounds(s2) == true) {
			Texture tempTe;
			this->_menuMouse.changeImage("images/mouses/Mouse2.png");
			tempTe.loadFromFile("images/menus/BigPlayButton.png");

			Sprite tempSpr(tempTe);
			tempSpr.setPosition((float)(background.getSize().x - tempTe.getSize().x) / 2, (float)130);
			this->_gameWindow.draw(tempSpr);

			if (this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE) {
				this->_menuSound.playSound();

				//create a new screen for choosing game mode
				Texture modeChoosingTexture;
				modeChoosingTexture.loadFromFile("images/menus/ModeChoosing.png");
				Sprite modeChoosingSprite;
				modeChoosingSprite.setTexture(modeChoosingTexture);

				while (true) {
					this->_menuMouse.changeImage("images/mouses/Mouse1.png");
					this->_eventInput.checkEvent();

					this->_menuMouse.getPosition(*(this->_gameWindow).getGameWindow());
					this->_gameWindow.beginDrawing();
					this->_gameWindow.draw(modeChoosingSprite);

					Texture tickModeTexture;
					tickModeTexture.loadFromFile("images/menus/GreenTick.png");
					Sprite tickModeSprite;
					tickModeSprite.setTexture(tickModeTexture);

					//if they choose PvP mode
					if (this->_menuMouse.checkGetGlobalBounds(Vector2i(176, 178), 80, 150) == true) {
						this->_menuMouse.changeImage("images/mouses/Mouse2.png");

						if (this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE) {
							this->_eventInput._mouseClickType = ClickType::MOUSE_WAIT;

							this->_menuSound.playSound();

							this->_gameMode == GameMode::PvP;
						}
					}
					else if (this->_menuMouse.checkGetGlobalBounds(Vector2i(560, 162), 130, 115) == true) {
						//if they choose PvE mode
						this->_menuMouse.changeImage("images/mouses/Mouse2.png");

						if (this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE) {
							this->_eventInput._mouseClickType = ClickType::MOUSE_WAIT;

							this->_menuSound.playSound();

							this->_gameMode == GameMode::PvE;
						}
					}

					//if they begin to play game
					if (this->_menuMouse.checkGetGlobalBounds(Vector2i(391, 346), 52, 58) == true) {
						this->_menuMouse.changeImage("images/mouses/Mouse2.png");

						if (this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE && this->_gameMode != GameMode::WAIT) {
							this->_eventInput._mouseClickType = ClickType::MOUSE_WAIT;

							this->_menuSound.playSound();

							this->_gameWindow.close();

							this->_menuMusic.stopMusic();

							return MenuStatus::PLAYING;
						}
					}

					//if they return back to main menu
					if (this->_menuMouse.checkGetGlobalBounds(Vector2i(770, 18), 45, 52) == true) {
						this->_menuMouse.changeImage("images/mouses/Mouse2.png");

						if (this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE) {
							this->_eventInput._mouseClickType = ClickType::MOUSE_WAIT;
							this->_menuSound.playSound();

							break;
						}
					}

					//if they return to the green tick when choosing mode
					if (this->_gameMode == GameMode::PvP) {
						tickModeSprite.setPosition(190, 300);
						this->_gameWindow.draw(tickModeSprite);
					}
					else if (this->_gameMode == GameMode::PvE) {
						tickModeSprite.setPosition(600, 300);
						this->_gameWindow.draw(tickModeSprite);
					}

					//finish drawing :(
					this->_menuMouse.draw(*(this->_gameWindow).getGameWindow());
					this->_gameWindow.endDDrawing();
				}
			}
		}
		else {
			this->_menuMouse.changeImage("images/mouses/Mouse1.png");

			s2.setPosition((background.getSize().x - playButton.getSize().x) / 2, 130);
			this->_gameWindow.draw(s2);
		}

		if (this->_menuMouse.checkGetGlobalBounds(s4)) {
			this->_menuMouse.changeImage("images/mouses/Mouse2.png");

			Texture tempTe;
			tempTe.loadFromFile("images/menus/BigOptionButton.png");
			Sprite tempSpr(tempTe);
			tempSpr.setPosition((float)(background.getSize().x - tempTe.getSize().x) / 2, 220);
			this->_gameWindow.draw(tempSpr);

			if (this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE) {
				this->_menuSound.playSound();

				Texture optionChoosingTexture;
				Sprite optionChoosingSprite;
				optionChoosingTexture.loadFromFile("images/menus/OptionChoosing.png");
				optionChoosingSprite.setTexture(optionChoosingTexture);

				Texture changeVolumeTexture;
				Sprite changeVolumeSprite1, changeVolumeSprite2;
				changeVolumeTexture.loadFromFile("images/menus/Volume.png");
				changeVolumeSprite1.setTexture(changeVolumeTexture);
				changeVolumeSprite2.setTexture(changeVolumeTexture);
				changeVolumeSprite1.setPosition(this->_volume.music * 2.15 + 300, 168);
				changeVolumeSprite2.setPosition(this->_volume.sound * 2.15 + 300, 255);

				Vector2f newPos = changeVolumeSprite1.getPosition();

				bool isMovings1 = false, isMovings2 = false; //in the original version, it is not initialized
				bool isMoving = false;

				ClickType clickType;
				
				while (true) {
					int dx = 0, dy = 0;

					Event eve;
					Vector2i pos = Mouse::getPosition(*(this->_gameWindow).getGameWindow());

					while (this->_gameWindow.getGameWindow()->pollEvent(eve)) {
						clickType = ClickType::MOUSE_WAIT;

						if (eve.type == Event::MouseButtonPressed) {
							//in this case, mouse button has been pressed, we get the position, and set moving as true
							if (eve.mouseButton.button == 0 && changeVolumeSprite1.getGlobalBounds().contains(this->_menuMouse.getPosVector().x, this->_menuMouse.getPosVector().y) == true) {
								isMoving = true;

								dx = pos.x - changeVolumeSprite1.getPosition().x;
								dy = pos.y - changeVolumeSprite1.getPosition().y;

								isMovings1 = true;
							}
							else if (eve.mouseButton.button == 0 && changeVolumeSprite2.getGlobalBounds().contains(this->_menuMouse.getPosVector().x, this->_menuMouse.getPosVector().y) == true) {
								isMoving = true;

								dx = pos.x - changeVolumeSprite2.getPosition().x;
								dy = pos.y - changeVolumeSprite2.getPosition().y;

								isMovings2 = true;
							}
							else if (eve.mouseButton.button == 0) {
								clickType = ClickType::LEFT_MOUSE;
							}

							break;
						}
						else if (eve.type == Event::MouseButtonReleased) {
							//in this case, mouse button has no longer been pressed, don't move anymore
							if (eve.mouseButton.button == 0) {
								isMoving = false;
								isMovings1 = false;
								isMovings2 = false;
							}

							break;
						}
					}

					if (isMoving == true) {
						if (isMovings1 == true && pos.x - dx >= 300 && pos.x - dx <= 515) {
							changeVolumeSprite1.setPosition(pos.x - dx, changeVolumeSprite1.getPosition().y);
						}

						if (isMovings2 == true && pos.x - dx >= 300 && pos.x - dx <= 515) {
							changeVolumeSprite2.setPosition(pos.x - dx, changeVolumeSprite2.getPosition().y);
						}
					}

					this->_menuMouse.changeImage("images/mouses/Mouse1.png");

					if (this->_menuMouse.checkGetGlobalBounds(Vector2i(750, 18), 70, 70) == true) {
						this->_menuMouse.changeImage("images/mouses/Mouse2.png");

						if (clickType == ClickType::LEFT_MOUSE) {
							clickType = ClickType::MOUSE_WAIT;

							this->_menuSound.playSound();

							this->_volume.music = (changeVolumeSprite1.getPosition().x - 300) / 2.15;
							this->_volume.sound = (changeVolumeSprite2.getPosition().x - 300) / 2.15;

							break;
						}
					}

					this->_menuMouse.getPosition(*(this->_gameWindow.getGameWindow()));

					this->_gameWindow.beginDrawing();
					this->_gameWindow.draw(optionChoosingSprite);
					this->_gameWindow.draw(changeVolumeSprite1);
					this->_gameWindow.draw(changeVolumeSprite2);
					this->_menuMouse.draw(*(this->_gameWindow.getGameWindow()));
					this->_gameWindow.endDDrawing();
				}
			}
		}
		else {
			s4.setPosition((background.getSize().x - optionButton.getSize().x) / 2, 220);
			this->_gameWindow.draw(s4);
		}

		if (this->_menuMouse.checkGetGlobalBounds(s5)) {
			this->_menuMouse.changeImage("images/mouses/Mouse2.png");

			Texture tempTe;
			tempTe.loadFromFile("images/menus/BigExitButton.png");
			Sprite tempSpr(tempTe);
			tempSpr.setPosition((background.getSize().x - tempTe.getSize().x) / 2, 320);
			this->_gameWindow.draw(tempSpr);

			if (this->_eventInput._mouseClickType == ClickType::LEFT_MOUSE) {
				this->_menuSound.playSound();

				this->_menuMusic.stopMusic();

				this->_gameWindow.close();

				return MenuStatus::EXITING;
			}
		}
		else {
			s5.setPosition((background.getSize().x - exitButton.getSize().x) / 2, 320);
			this->_gameWindow.draw(s5);
		}

		s3.setPosition(308, 20);
		this->_gameWindow.draw(s3);

		this->_menuMouse.draw(*(this->_gameWindow.getGameWindow()));
		this->_gameWindow.endDDrawing();
	}

	this->_gameWindow.close();
	
	return MenuStatus::EXITING;
}

GameMode GameMenu::getGameMode() {
	return this->_gameMode;
}

void GameMenu::setGameVolume(Volume& vol) {
	this->_volume.music = vol.music;
	this->_volume.sound = vol.sound;
}