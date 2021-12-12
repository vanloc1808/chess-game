#include "GameSound.h"

GameSound::GameSound() {
	this->_isRepeated = false;
	this->_soundVolume = 100;
}

GameSound::~GameSound() {

}

void GameSound::setSoundBuffer(string location) {
	if (this->_buffer.loadFromFile(location) == false) {
		cout << "Error! Cannot find sound file\n";
	}
	else {
		this->_gameSound.setBuffer(this->_buffer);
	}
}

void GameSound::setRepeatedSound() {
	this->_isRepeated = true;

	this->_gameSound.setLoop(this->_isRepeated);
}

void GameSound::playSound() {
	this->_gameSound.play();
}

void GameSound::pauseSound() {
	this->_gameSound.pause();
}

void GameSound::stopSound() {
	this->_gameSound.stop();
}

void GameSound::changeSoundVolume(int v) {
	this->_gameSound.setVolume(v);
}