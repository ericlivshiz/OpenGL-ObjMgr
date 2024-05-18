#include "Keyboard.h"

void Keyboard::ProcessKeyInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		ESC_PRESS = true;
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
	{
		ESC_PRESS = false;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		L_SHIFT_PRESS = true;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		L_SHIFT_PRESS = false;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		L_CTRL_PRESS = true;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
	{
		L_CTRL_PRESS = false;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		W_PRESS = true;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		A_PRESS = true;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		S_PRESS = true;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		D_PRESS = true;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		SPACE_PRESS = true;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
	{
		W_PRESS = false;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
	{
		A_PRESS = false;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
	{
		S_PRESS = false;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
	{
		D_PRESS = false;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
	{
		SPACE_PRESS = false;
	}

};