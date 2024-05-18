#pragma once

#include "Square.h"
#include "Cube.h"

#define SHOULD_LOAD_SQUARE 0
#define SHOULD_LOAD_CUBE 1

class ObjMgr
{
public:
	void SetupObjects()
	{
		if (SHOULD_LOAD_SQUARE)
			square.SetupSquare();

		if (SHOULD_LOAD_CUBE)
			cube.SetupCube();
	}

	Square square;
	Cube cube;
};