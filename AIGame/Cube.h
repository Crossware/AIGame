#pragma once

#include <windows.h>		// Must have for Windows platform builds
#include <iostream>
#include <fstream>
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include <glut.h>
#include <cstring>
#include <sstream>
#include <math.h>

#include "imageloader.h"
#include "Camera.h"

#pragma comment(lib, "glut/opengl32.lib")
#pragma comment(lib, "glut/glut32")
#pragma comment(lib, "glu32")
#define CUBE_SIZE 10

class Cube
{
public:
	Cube(int _gridX = 1, int _gridZ = 1, GLuint tex = 0);
	~Cube();
	int getGridX();
	int getGridZ();
	GLuint textureID;
	
	GLuint loadTexture(Image* image);
	void DrawCube();
	void setGridX(int);
	void setGridZ(int);
	
private:
	int width;
	int height;
	int gridX;
	int gridZ;
	
	
};