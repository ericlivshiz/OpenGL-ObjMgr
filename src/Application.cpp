#include "Application.h"

Application* Application::instance = nullptr;

Application::Application()
{
	instance = this;
}

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

	glfwSetCursorPosCallback(window.Get_Window(), mouse_callback);
	glfwSetScrollCallback(window.Get_Window(), scroll_callback);
	glfwSetInputMode(window.Get_Window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	objmgr.SetupObjects();

	AppLoop();
}

void Application::AppLoop()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	while (program_running)
	{
		Handle_Input();
		Update();
		Display();
	}
}

void Application::Handle_Input()
{
	ctrlmgr.keyboard.ProcessKeyInput(window.Get_Window());

	if (ctrlmgr.keyboard.ESC_PRESS)
	{
		program_running = false;
	}

	if (ctrlmgr.keyboard.L_CTRL_PRESS)
	{
		renderer.ToggleWireframe();
	}

	if (ctrlmgr.keyboard.W_PRESS)
	{
		ctrlmgr.camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (ctrlmgr.keyboard.A_PRESS)
	{
		ctrlmgr.camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (ctrlmgr.keyboard.S_PRESS)
	{
		ctrlmgr.camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (ctrlmgr.keyboard.D_PRESS)
	{
		ctrlmgr.camera.ProcessKeyboard(RIGHT, deltaTime);
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

void Application::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	if (instance)
	{
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (instance->firstMouse)
		{
			instance->lastX = xpos;
			instance->lastY = ypos;
			instance->firstMouse = false;
		}

		float xoffset = xpos - instance->lastX;
		float yoffset = instance->lastY - ypos;

		instance->lastX = xpos;
		instance->lastY = ypos;

		instance->ctrlmgr.camera.ProcessMouseMovement(xoffset, yoffset, true);
	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (instance)
	{
		instance->ctrlmgr.camera.ProcessMouseScroll(static_cast<float>(yoffset));
	}
}