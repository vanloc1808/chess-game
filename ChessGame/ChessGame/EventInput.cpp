#include "EventInput.h"

void EventInput::setWindow(GameWindow* w) {
	this->_window = w;
	this->_mouseClickType = ClickType::MOUSE_WAIT;
}

void EventInput::checkEvent() {
	while (this->_window->getGameWindow()->pollEvent(this->_event)) {
		if (this->_event.type == Event::Closed) {
			this->_window->close();
		}

		this->_mouseClickType = ClickType::MOUSE_WAIT;

		if (this->_event.type == Event::MouseButtonPressed) {
			if (this->_event.key.code == Mouse::Left) {
				this->_mouseClickType = ClickType::LEFT_MOUSE;
			}
			else if (this->_event.key.code == Mouse::Right) {
				this->_mouseClickType = ClickType::RIGHT_MOUSE;
			}
		}
	}
}

void EventInput::checkEvent(Sprite& s) {
	bool isMoving = false;

	int dx= 0, dy = 0;

	while (this->_window->getGameWindow()->pollEvent(this->_event)) {
		this->_mouseClickType = ClickType::MOUSE_WAIT;

		if (this->_event.type == Event::MouseButtonPressed) {
			if (this->_event.key.code == Mouse::Left) {
				if (s.getGlobalBounds().contains(Mouse::getPosition(*(this->_window)->getGameWindow()).x, Mouse::getPosition(*(this->_window)->getGameWindow()).y)) {
					isMoving = true;

					cout << Mouse::getPosition(*(this->_window)->getGameWindow()).x << "\n";
					cout << Mouse::getPosition(*(this->_window)->getGameWindow()).y << "\n";

					dx = Mouse::getPosition(*(this->_window)->getGameWindow()).x - s.getPosition().x;
					dy = Mouse::getPosition(*(this->_window)->getGameWindow()).y - s.getPosition().y;
				}
				else {
					this->_mouseClickType = ClickType::LEFT_MOUSE;
				}
			}
		}

		if (this->_event.type == Event::MouseButtonReleased) {
			if (this->_event.key.code == Mouse::Left) {
				isMoving = false;
			}
		}
	}

	if (isMoving == true) {
		s.setPosition(Mouse::getPosition(*(this->_window)->getGameWindow()).x - dx, s.getPosition().y);
		cout << Mouse::getPosition(*(this->_window)->getGameWindow()).x << "\n";
	}
}

Event EventInput::getEvent() {
	return this->_event;
}