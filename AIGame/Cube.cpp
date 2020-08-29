#include "Cube.h"
#include "imageloader.h"


//cube constructor
Cube::Cube(int _gridX, int _gridZ, GLuint tex)
{
	gridX = _gridX;
	gridZ = _gridZ;
	width = CUBE_SIZE;
	height = CUBE_SIZE;
	textureID = tex;
}

Cube::~Cube(){}

//draws the cube
void Cube::DrawCube()
{
	glPushMatrix();
		glTranslatef(gridX * CUBE_SIZE, 0, gridZ * CUBE_SIZE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBegin(GL_QUADS);

		//Top face
		glNormal3f(0.0, 1.0f, 0.0f);
		glVertex3f(-CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);
		glVertex3f(-CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2);
		glVertex3f(CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2);
		glVertex3f(CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);
	
		//Bottom face
		glNormal3f(0.0, -1.0f, 0.0f);
		glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);
		glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);
		glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2);
		glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2);
	
		//Left face
		glNormal3f(-1.0, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);
	
		//Right face
		glNormal3f(1.0, 0.0f, 0.0f);	
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);	
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);	
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2);	
	
		//Front face
		glNormal3f(0.0, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2);
	
		//Back face
		glNormal3f(0.0, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);
	
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

//get and set functions
int Cube::getGridX()
{
	return gridX;
}
int Cube::getGridZ()
{
	return gridZ;
}
void Cube::setGridX(int newX)
{
	gridX = newX;
}
void Cube::setGridZ(int newZ)
{
	gridZ = newZ;
}
