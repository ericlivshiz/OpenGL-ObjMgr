#pragma once

#include "Square.h"
#include "Cube.h"
#include "Sphere.h"

#include "../irl-controls/ControlsMgr.h"

#define SHOULD_LOAD_SQUARE 0
#define SHOULD_LOAD_CUBE 0
#define SHOULD_LOAD_SPHERE 0
#define SHOULD_LOAD_DEMO_CUBES 0
#define SHOULD_LOAD_DEMO_SPHERES 1

class ObjMgr
{
public:
	void SetupObjects()
	{
		if (SHOULD_LOAD_SQUARE)
			square.SetupSquare();

		if (SHOULD_LOAD_CUBE)
			cube.SetupCube();

		if (SHOULD_LOAD_SPHERE)
			sphere.SetupSphere();

		if (SHOULD_LOAD_DEMO_CUBES)
			cube.SetupDemo();

		if (SHOULD_LOAD_DEMO_SPHERES)
			sphere.SetupDemo();
	}


	Square square;
	Cube cube;
	Sphere sphere;
};