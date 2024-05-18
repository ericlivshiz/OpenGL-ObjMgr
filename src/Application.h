#pragma once

#include "util/Window.h"
#include "util/Renderer.h"
#include "objects/ObjMgr.h"
#include "irl-controls/Keyboard.h"


class Application
{
public:
	void Start();

private:
	void Stop();
	void Setup();
	void AppLoop();
	void Handle_Input();
	void Update();
	void Display();

	bool program_running = false;

private:
	Window window;
	Renderer renderer{ window };
	Keyboard keyboard;
	ObjMgr objmgr;
};