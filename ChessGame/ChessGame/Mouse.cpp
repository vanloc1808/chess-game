#include "Mouse.h"

//default constructor and default destructor
//do nothing
GameMouse::GameMouse() {

}

GameMouse::~GameMouse() {

}

void GameMouse::setLocation(string location) {
	this->_imageLocation = location;
}

void GameMouse::setImage() {
	if (this->_mouseTexture.loadFromFile(this->_imageLocation) == false) {
		cout << "Error when opening mouse file\n";

		return;
	}

	this->_mousePicture.setTexture(this->_mouseTexture);
}

void GameMouse::getPosition(RenderWindow& window) {
	this->_mousePosition = Mouse::getPosition(window);

	this->_mousePicture.setPosition(this->_mousePosition.x, this->_mousePosition.y);
}

void GameMouse::draw(RenderWindow& window) {
	window.draw(this->_mousePicture);
}

bool GameMouse::checkGetGlobalBounds(Sprite image) {
	return (image.getGlobalBounds().contains(this->_mousePosition.x, this->_mousePosition.y));
}

bool GameMouse::checkGetGlobalBounds(Vector2i v) {
	bool first = this->_mousePosition.x >= PIECE_SIZE * v.x  + LANDMARK;
	bool second = this->_mousePosition.x <= PIECE_SIZE * (v.x + 1) + LANDMARK;
	bool third = this->_mousePosition.y >= PIECE_SIZE * v.y + LANDMARK;
	bool fourth = this->_mousePosition.y <= PIECE_SIZE * (v.y + 1) + LANDMARK;

	return (first && second && third && fourth);
}

bool GameMouse::checkGetGlobalBounds(Vector2i v, int x, int y) {
	bool first = this->_mousePosition.x >= v.x;
	bool second = this->_mousePosition.x <= v.x + x;
	bool third = this->_mousePosition.y >= v.y;
	bool fourth = this->_mousePosition.y <= v.y + y;

	return (first && second && third && fourth);

}

void GameMouse::changeImage(string location) {
	this->setLocation(location);
	this->setImage();
}

Vector2f GameMouse::getPosVector() {
	Vector2f res;

	res.x = this->_mousePosition.x;
	res.y = this->_mousePosition.y;

	return res;
}

void GameMouse::consolePositionOutput() {
	cout << this->_mousePosition.x << ":" << this->_mousePosition.y << "\n";
}