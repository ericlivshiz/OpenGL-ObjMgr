#include "Application.h"

void Application::Start()
{
	program_running = true;
	Setup();
}

void Application::Stop()
{
	program_running = false;
	glfwTerminate();
}

void Application::Setup()
{
	// Anything that needs to be run once

	objmgr.SetupObjects();

	AppLoop();
}

void Application::AppLoop()
{
	while (program_running)
	{
		Handle_Input();
		Update();
		Display();
	}
}

void Application::Handle_Input()
{
	keyboard.ProcessKeyInput(window.Get_Window());

	if (keyboard.ESC_PRESS)
	{
		program_running = false;
	}

	if (keyboard.L_CTRL_PRESS)
	{
		renderer.ToggleWireframe();
	}
}

void Application::Update()
{
	
}

void Application::Display()
{
	renderer.PreRender();
	renderer.Render(objmgr);
	renderer.PostRender();
}