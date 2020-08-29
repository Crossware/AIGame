#pragma once

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include <glut.h>
#include <cstring>
#include <sstream>
#include <math.h>
#include "GameAI.h"
#pragma comment(lib, "glut/opengl32.lib")
#pragma comment(lib, "glut/glut32")
#pragma comment(lib, "glu32")

class Enemy
{
public:
	Enemy(float _posX = 0, float _posZ = 0);
	~Enemy();
	void DrawEnemy();

	float posX, posZ;
	int fleeIndex;
	bool killed;

	brainWaves properties;

	GameAI* brain;

	void updateEnemy(float x, float z);
private:

};