#pragma once

#include "../util/Window.h"

class Keyboard
{
public:
	void ProcessKeyInput(GLFWwindow* window);

public:
	bool ESC_PRESS = false;
	bool W_PRESS = false;
	bool A_PRESS = false;
	bool S_PRESS = false;
	bool D_PRESS = false;
	bool L_TAB_PRESS = false;
	bool L_SHIFT_PRESS = false;
	bool L_CTRL_PRESS = false;
	bool SPACE_PRESS = false;
};