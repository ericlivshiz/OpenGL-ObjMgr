#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../objects/ObjMgr.h"
#include "Window.h"


class Renderer
{
public:
	Renderer(Window& window);

	void PreRender();
	void Render(ObjMgr& objmgr);
	void PostRender();

	void ToggleWireframe();

private:
	void RenderSquare(ObjMgr& objmgr);
	void RenderCube(ObjMgr& objmgr);

private:
	bool frame_state; // 0 -> WireFrameOff. 1-> WireFramesOn.

private:
	Window& window;


};