#include "Enemy.h"

//enemy constructor
Enemy::Enemy(float _posX, float _posZ)
{
	posX = _posX;
	posZ = _posZ;
	properties.initialisedStartGoal = false;
	properties.foundGoal = false;
	properties.speed = 0.3;
	brain = new GameAI();
	properties.previousGridX = (int)_posX/10;
	properties.previousGridZ = (int)_posZ/10;
	properties.hit = false;
	fleeIndex = 1;
	killed = false;
	brain->enemyState = brain->pursue;
}

Enemy::~Enemy(){}

//draws enemy
void Enemy::DrawEnemy()
{
	glColor3f(1.0,1.0,1.0);
	//Front Cone
	glPushMatrix();
		glTranslatef(posX, 0, posZ + 2);
		glutSolidCone( 0.3, 1.0, 40, 40);
	glPopMatrix();
	//Back Cone
	glPushMatrix();
		glTranslatef(posX, 0, posZ - 2);
		glRotatef(180, 0,1,0);
		glutSolidCone( 0.3, 1.0, 40, 40);
	glPopMatrix();
	//Right Cone
	glPushMatrix();
		glTranslatef(posX + 2, 0, posZ);
		glRotatef(90, 0,1,0);
		glutSolidCone( 0.3, 1.0, 40, 40);
	glPopMatrix();
	//Left Cone
	glPushMatrix();
		glTranslatef(posX - 2, 0, posZ);
		glRotatef(-90, 0,1,0);
		glutSolidCone( 0.3, 1.0, 40, 40);
	glPopMatrix();
	//Top Cone
	glPushMatrix();
		glTranslatef(posX, 2, posZ);
		glRotatef(-90, 1,0,0);
		glutSolidCone( 0.3, 2, 40, 40);
	glPopMatrix();
	//Bottom Cone
	glPushMatrix();
		glTranslatef(posX, -2, posZ);
		glRotatef(90, 1,0,0);
		glutSolidCone( 0.3, 2, 40, 40);
	glPopMatrix();
	//Sphere
	glPushMatrix();
		glTranslatef(posX ,0, posZ);
		glutSolidSphere(1.5, 40, 20);
	glPopMatrix();
}

//enemy update protocols including state machine and pathfinding directives
void Enemy::updateEnemy(float x, float z)
{
	properties.gridX = floor((posX+5)/10);
	properties.gridZ = floor((posZ+5)/10);
	properties.foundGoal = false;
	properties.initialisedStartGoal = false;
	int goalX = floor((x+5)/10);
	int goalZ = floor((z+5)/10);

	if (properties.nextGridX * 10 > posX)
	{
		posX += properties.speed; 
	}
	if (properties.nextGridX * 10 < posX)
	{
		posX -= properties.speed; 
	}

	if (properties.nextGridZ * 10 > posZ)
	{
		posZ += properties.speed; 
	}
	if (properties.nextGridZ * 10 < posZ)
	{
		posZ -= properties.speed; 
	}

	switch(brain->enemyState)
	{
	case brain->pursue:
		brain->FindPath(goalX, goalZ, &properties);		
	
		if ((properties.gridX > properties.previousGridX || properties.gridX < properties.previousGridX)
			|| (properties.gridZ > properties.previousGridZ || properties.gridZ < properties.previousGridZ))
		{
			for (int i = 9; i >= 0; i--)
			{
				properties.fleeSpace[i] = properties.fleeSpace[i - 1];
			}
			properties.fleeSpace[0].xPos = properties.gridX;
			properties.fleeSpace[0].zPos = properties.gridZ;
		}
		properties.previousGridX = properties.gridX;
		properties.previousGridZ = properties.gridZ;
		break;

	case brain->flee:
		brain->FindPath(properties.fleeSpace[9].xPos, properties.fleeSpace[9].zPos, &properties);
		if (properties.gridX == properties.fleeSpace[9].xPos &&
			properties.gridZ == properties.fleeSpace[9].zPos)
		{
			brain->enemyState = brain->pursue;
			properties.speed = 0.3;
		}
		break;

	case brain->kill:
		killed = true;
		break;

	default:
		break;
	}

	if((properties.gridX == goalX) && (properties.gridZ == goalZ))
	{
		brain->enemyState = brain->kill;
	}
}