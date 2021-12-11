#ifndef _EVENTINPUT_H_
#define _EVENTINPUT_H_

#include <SFML/Graphics.hpp>
#include "GameWindow.h"

using namespace sf;

enum class ClickType {
	LEFT_MOUSE,
	RIGHT_MOUSE,
	MOUSE_WAIT
};

class EventInput {
private:
	Event _event;

	GameWindow* _window;

public:
	ClickType _mouseClickType;

	void setWindow(GameWindow* w);

	void checkEvent();

	void checkEvent(Sprite& s);

	Event getEvent();
};

#endif // !_EVENTINPUT_H_


