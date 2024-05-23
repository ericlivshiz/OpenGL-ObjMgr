#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../objects/ObjMgr.h"
#include "../irl-controls/ControlsMgr.h"
#include "Window.h"


class Renderer
{
public:
	Renderer(Window& window, ControlsMgr& ctrlmgr);

	void PreRender();
	void Render(ObjMgr& objmgr);
	void PostRender();

	void ToggleWireframe();

private:
	void RenderSquare(ObjMgr& objmgr);
	void RenderCube(ObjMgr& objmgr);
	void RenderDemoCubes(ObjMgr& objmgr);

private:
	bool frame_state; // 0 -> WireFrameOff. 1-> WireFramesOn.

private:
	Window& window;
	ControlsMgr& ctrlmgr;
};