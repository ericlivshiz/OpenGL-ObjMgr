#pragma once

#include "Keyboard.h"

#include "Camera.h"

// currently doesn't do anything
#define SHOULD_PROCESS_KEYBOARD 1
#define SHOULD_PROCESS_CAMERA   1
#define SHOULD_PROCESS_MOUSE    1

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