#pragma once

#include "Keyboard.h"

#include "Camera.h"

class ControlsMgr
{
public:
	ControlsMgr(Window& window)
		:
		window{window}
	{
	}

	Keyboard keyboard;
	Camera camera;

private:
	Window& window;
};