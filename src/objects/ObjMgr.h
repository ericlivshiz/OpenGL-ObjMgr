#pragma once

#include "Square.h"
#include "Cube.h"

#include "../irl-controls/ControlsMgr.h"

#define SHOULD_LOAD_SQUARE 0
#define SHOULD_LOAD_CUBE 0
#define SHOULD_LOAD_DEMO_CUBES 1

class ObjMgr
{
public:
	void SetupObjects()
	{
		if (SHOULD_LOAD_SQUARE)
			square.SetupSquare();

		if (SHOULD_LOAD_CUBE)
			cube.SetupCube();

		if (SHOULD_LOAD_DEMO_CUBES)
			cube.SetupDemo();
	}

	Square square;
	Cube cube;
};