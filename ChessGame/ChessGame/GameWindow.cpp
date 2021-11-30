#include "GameWindow.h"

//default constructor, set isFullScreen and isDone false
GameWindow::GameWindow() {
	this->_isFullScreen = false;
	this->_isDone = false;
}

GameWindow::~GameWindow() {
	this->close();
}

void GameWindow::create() {
	auto style = (this->_isFullScreen ? Style::Fullscreen : Style::Default); // if (isFullScreen) {style = Style::FullScr} else {style = Default}
	this->_gameWindow.create(VideoMode(this->_windowSize.x, this->_windowSize.y), this->_windowTitle, style);
}

void GameWindow::close() {
	this->_gameWindow.close();
}

void GameWindow::setup(const string& title, const Vector2u& size) {
	this->_windowTitle = title;
	this->_windowSize = size;
	this->create();
}

void GameWindow::beginDrawing() {
	this->_gameWindow.clear(Color::Black);
}

void GameWindow::endDDrawing() {
	this->_gameWindow.display();
}

bool GameWindow::isDone() {
	return this->_gameWindow.isOpen();
}

bool GameWindow::isFullScreen() {
	return this->_isFullScreen;
}

void GameWindow::Draw(Drawable& dr) {
	this->_gameWindow.draw(dr);
}

Vector2u GameWindow::getWindowSize() {
	return this->_windowSize;
}

//get pointer to game window only,
//not allocate new memory
RenderWindow* GameWindow::getGameWindow() {
	return &this->_gameWindow;
}