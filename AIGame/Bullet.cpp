#include "Bullet.h"

//bullet constructor
Bullet::Bullet(float _posX, float _posZ)
{
	posX = _posX;
	posZ = _posZ;
	radius = 1;
	speed = 5;
	updatePos = false;
}

Bullet::~Bullet(){}

//draws the bullet
void Bullet::drawBullet()
{
	glPushMatrix();			
		glTranslatef(posX, 0, posZ);
		glutSolidSphere(radius, 100, 100);
	glPopMatrix();
}

//get and set functions
int Bullet::getGridX()
{
	int a = (int)(posX + 5.0f) / 10;
	return a;
}
int Bullet::getGridZ()
{
	int b = (int)(posZ + 5.0f) / 10;
	return b;
}
float Bullet::getPos()
{
	return (posX, posZ);
}
void Bullet::setPos(float x, float z)
{
	posX = x;
	posZ = z;
}

//updates the bullet
void Bullet::Update(bool pX, bool nX, bool pZ, bool nZ)
{
	if (updatePos)
	{
		if (pX)
			posX += speed;
		if (nX)
			posX -= speed;
		if (pZ)
			posZ += speed;
		if (nZ)
			posZ -= speed;
	}
}