#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window
{
public:
	Window();

	GLFWwindow* Get_Window()	{ return window; }
	int Get_Width()				{ return width; }
	int Get_Height()			{ return height; }
	float Get_AspectRatio()		{ return aspect_ratio; }
	float Get_ZNear()			{ return z_near; }
	float Get_ZFar()			{ return z_far; }
	static void  Framebuffer_Size_Callback(GLFWwindow* window, int width, int height);


private:
	unsigned int width;
	unsigned int height;
	float aspect_ratio;
	float z_near;
	float z_far;

	GLFWwindow* window;
};