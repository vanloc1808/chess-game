#include "GameMusic.h"

GameMusic::GameMusic() {
	this->_isRepeated = false;
	
	this->_musicVolume = 100;

	this->_musicStatus = MusicStatus::STOP;
}

GameMusic::~GameMusic() {

}

void GameMusic::setMusic(string location) {
	this->_gameMusic.openFromFile(location);
}

void GameMusic::setRepeatedMusic() {
	this->_isRepeated = true;

	this->_gameMusic.setLoop(this->_isRepeated);
}

void GameMusic::playMusic() {
	this->_gameMusic.play();

	this->_musicStatus = MusicStatus::PLAY;
}

void GameMusic::pauseMusic() {
	this->_gameMusic.pause();

	this->_musicStatus = MusicStatus::PAUSE;
}

void GameMusic::stopMusic() {
	this->_gameMusic.stop();

	this->_musicStatus = MusicStatus::STOP;
}

void GameMusic::continueMusic() {
	if (this->_musicStatus == MusicStatus::PAUSE) {
		this->_gameMusic.play();
	}

	this->_musicStatus = MusicStatus::PLAY;
}

void GameMusic::changeMusicVolume(int volume) {
	this->_gameMusic.setVolume(volume);
}

MusicStatus GameMusic::getMusicStatus() {
	return this->_musicStatus;
}