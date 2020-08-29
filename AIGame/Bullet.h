#pragma once

#include <windows.h>		// Must have for Windows platform builds
#include <iostream>
#include <fstream>
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include <glut.h>
#include <cstring>
#include <sstream>
#include <math.h>

class Bullet
{
public:
	Bullet(float _posX = 0, float _posZ = 0);
	~Bullet();

	float posX, posZ, radius, speed;
	bool updatePos;

	void drawBullet();
	void setPos(float x, float z);
	float getPos();
	int getGridX();
	int getGridZ();
	void Update(bool pX, bool nX, bool pZ, bool nZ);
private:

};