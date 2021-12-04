#include "Player.h"

Player::Player() {
	this->_name = "";
	this->_address = "";
	this->_gender = "";
	this->_movedPiece = "";

	this->_age = 0;
	this->_elo = 0;
	this->_winNumber = 0;
	this->_loseNumber = 0;
}

Player::Player(string n, int a) {
	this->_name = n;
	this->_age = a;
}

Player::~Player() {

}

string Player::getName() {
	return this->_name;
}

int Player::getElo() {
	return this->_elo;
}

string Player::getAddress() {
	return this->_address;
}

string Player::getGender() {
	return this->_gender;
}

void Player::addMovedPiece(string p) {
	this->_movedPiece.append(p);
}

void Player::removeMovedPiece() {
	for (int i = 0; i < 4; i++) {
		this->_movedPiece.pop_back();
	}
}