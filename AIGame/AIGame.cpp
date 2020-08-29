//project includes
#include "Cube.h"
#include "Enemy.h"
#include "Bullet.h"
#include <iostream>
#include <time.h>

using namespace std;

#define GRID_WIDTH 21
#define MAX_CUBES 422

//global variables
int lightFrame = 0;
int windowW = 800;
int windowH = 800;
int resizeWindowW;
int resizeWindowH;
int gamestate = 0;
int numberOfCubes = 0;
int newMazeArray[GRID_SIZE*GRID_SIZE] =
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
	 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 
	 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
	 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 
	 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
	 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1,
	 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 
	 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 
	 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
	 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 
	 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
	 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
	 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1,
	 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
	 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1,
	 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
	 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1,
	 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1,
	 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1,
	 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1};

double FOV = 90.0f;

float mouseX;
float mouseY;
float fraction = 1.0f;

float cardRot = 0;
float cardX;
float cardZ;
int xOrigin = -1;

bool lightingOn = false;
bool keyLeftPressed = false;
bool keyRightPressed = false;
bool keyUpPressed = false;
bool keyDownPressed = false;
bool lookLeft = false;
bool lookRight = false;
bool camTurn = false;
bool map = false;
bool fullscreen = false;
bool mazeFinished = false;
bool flashActive = false;
bool shoot = false;
bool setBulletPos = false;
bool cardCollected = false;
bool finish = false;

float cameraX = 50.0f, cameraY = 0.0f, cameraZ = 30.0f;
float speed = 5.5f;

//game objects
Camera Cam(cameraX, cameraY, cameraZ);
Cube* myCubes[MAX_CUBES];
Bullet* bulletPosX = new Bullet(-10, -10);
Bullet* bulletNegX = new Bullet(-10, -10);
Bullet* bulletPosZ = new Bullet(-10, -10);
Bullet* bulletNegZ = new Bullet(-10, -10);
Enemy* Monster = new Enemy(90, 150);


//texture ID variables
GLuint _textureId;					
GLuint _textureId2;
GLuint _textureId3;
GLuint _textureId4;
GLuint _textureId5;
GLuint _textureId6;


struct gridPos
{
	int x, z;
};

gridPos gridArray[MAX_CUBES];

//fucntion that returns the index in the array for a grid position
int findInArray(int x, int z)
{
	int index = (x * 21) + z;

	return index;
}

//loads an image and assings it a pointer for OpenGL use
GLuint loadTexture(Image* image) 
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 image->width, image->height,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 image->pixels);
	return textureId;
}

//checks the surrounding cells for collision
void checkBounds()
{
	float newPosX = Cam.Transform[12] + 5;
	float newPosZ = Cam.Transform[14] + 5;
	int gridX = (int)(newPosX / 10);
	int gridZ = (int)(newPosZ / 10);

	int camIndex = findInArray(gridX, gridZ);
	int camUp = findInArray(gridX, gridZ - 1);
	int camDown = findInArray(gridX, gridZ + 1);
	int camLeft = findInArray(gridX - 1, gridZ);
	int camRight = findInArray(gridX + 1, gridZ);

	float newGridZ = gridZ;
	float newGridX = gridX;
	if ((newMazeArray[camUp] == 1) || (newMazeArray[camUp] == 2 && !cardCollected))
	{
		if (newPosZ < newGridZ * 10 + 0.8)
		{
			Cam.Transform[14] = newGridZ * 10 - 4.2;
			//cout << "top hit" << endl;
		}
	}
	
	if ((newMazeArray[camDown] == 1) || (newMazeArray[camDown] == 2 && !cardCollected))
	{
		if (newPosZ > (newGridZ + 1) * 10 - 0.8)
		{
			Cam.Transform[14] = (newGridZ + 1) * 10 - 5.8;
			//cout << "down hit" << endl;
		}
	}
	if ((newMazeArray[camRight] == 1) || (newMazeArray[camRight] == 2 && !cardCollected))
	{
		if (newPosX > (newGridX + 1) * 10 - 0.8)
		{
			Cam.Transform[12] = (newGridX + 1) * 10 - 5.8;
			//cout << "right hit" << endl;
		}
	}
	if ((newMazeArray[camLeft] == 1) || (newMazeArray[camLeft] == 2 && !cardCollected))
	{
		if (newPosX < newGridX * 10 + 0.8)
		{
			Cam.Transform[12] = newGridX * 10 - 4.2;
			//cout << "left hit" << endl;
		}
	}
	if (gridX == (int)cardX / 10 && gridZ == (int)cardZ / 10)
	{
		cardCollected = true;
	}
}

//loads texture data and enables OpenGL environment directives
void initRendering() 
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_FOG);
	glClearColor(0.0f, 0.0f, 0.0f, 1);
	//quad2 = gluNewQuadric();
	
	Image* image1 = loadBMP("hedgeTexture.bmp"); //For Win
	_textureId = loadTexture(image1);
	delete image1;
	Image* image2 = loadBMP("keycard.bmp"); //For Win
	_textureId2 = loadTexture(image2);
	delete image2;
	Image* image3 = loadBMP("exit.bmp"); //For Win
	_textureId3 = loadTexture(image3);
	delete image3;
	Image* image4 = loadBMP("need.bmp"); //For Win
	_textureId4 = loadTexture(image4);
	delete image4;
	Image* image5 = loadBMP("finish.bmp"); //For Win
	_textureId5 = loadTexture(image5);
	delete image5;
	Image* image6 = loadBMP("died.bmp"); //For Win
	_textureId6 = loadTexture(image6);
	delete image6;

	srand(time(NULL));
}

//resizes elements in the view based on the new screen resolution when it is resized
void handleResize(int w, int h) 
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV, (float)w / (float)h, 1.0, 5000.0);
	resizeWindowH = h;
	resizeWindowW = w;
}

//key processing
void handleKeypress(unsigned char key, int x, int y) 
{
	switch (key) 
	{	
	  case 'a' :
		  keyLeftPressed = true;
		  break;
      case 'd' :
		  keyRightPressed = true;
		  break;
      case 'w' :
		  keyUpPressed = true;
		  break;
      case 's' :
		  keyDownPressed = true;
		  break;
	  case 'f' :
		  if(!fullscreen)
		  {
			glutFullScreen();
			fullscreen = true;
		  } 
		  else if(fullscreen)
		  {
			glutReshapeWindow(800, 800);
		    glutPositionWindow(100,100);
			fullscreen = false;
		  }	
		  break;
	  case 32 :
		  shoot = true;
		  break;
	  case 'q' :
		  if(!camTurn)
		  {
			  Cam.rotateLoc(180, 0,1,0);
			  camTurn = true;
		  }
		  keyLeftPressed = false;
		  keyRightPressed = false;
		  //keyUpPressed = false;
		  keyDownPressed = false;
		  break;
	  case 27:		//Esc key			 
		exit(0);
	}
}
void keyboardUp(unsigned char key, int x, int y)
{
	switch (key) 
	{	
	  case 'a' :
		  keyLeftPressed = false;
		  break;
      case 'd' :
		  keyRightPressed = false;
		  break;
      case 'w' :
		  keyUpPressed = false;
		  break;
      case 's' :
		  keyDownPressed = false;
		  break;
	  case 'q' :
		  Cam.rotateLoc(180, 0,-1,0);
		  camTurn = false;
		  break;
	  case 'e' :
		  Cam.rotateLoc(180, 0,-1,0);
		  camTurn = false;
		  break;
	}
}
void handleSpecialKeypress (int key, int x, int y) 
{ 
	switch(key)
	{
		case GLUT_KEY_LEFT :
			//keyLeftPressed = true;
			lookLeft = true;
			speed += 0.05;
			break;
		case GLUT_KEY_RIGHT :
			lookRight = true;
			speed += 0.05;
			//keyRightPressed = true;
			break;
		case GLUT_KEY_UP :
			//deltaMove = 0.5f; break;
			//keyUpPressed = true;
			break;
		case GLUT_KEY_DOWN :
			//deltaMove = -0.5f; break;
			//keyDownPressed = true;
			break;
		case GLUT_KEY_F5 :
			if(!lightingOn)
			{
				lightingOn = true;
			} 
			else if(lightingOn)
			{
				lightingOn = false;
			}	
			break;
	}
}
void specialKeyUp(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT :
			lookLeft = false;
			speed = 2.5f;
			break;
		case GLUT_KEY_RIGHT :
			lookRight = false;
			speed = 2.5f;
			break;
		case GLUT_KEY_UP :
			break;
		case GLUT_KEY_DOWN :
			break;
	}
}

//draws 2D crosshair at the center of the screen
void drawCrosshair()
{
	float aspect = (float)resizeWindowW/(float)resizeWindowH;
	glPushMatrix();
		glLineWidth(3.0);
		glBegin(GL_LINES);
			glVertex3f(10.0 / aspect, 0.0, 0.0);
			glVertex3f(26.0 / aspect, 0.0, 0.0);
			glVertex3f(-10.0 / aspect, 0.0, 0.0);
			glVertex3f(-26.0 / aspect, 0.0, 0.0);

			glVertex3f(0.0, 10.0, 0.0);
			glVertex3f(0.0, 26.0, 0.0);
			glVertex3f(0.0, -10.0, 0.0);
			glVertex3f(0.0, -26.0, 0.0);
		glEnd();
	glPopMatrix();
}

//draws the ground of the maze
void drawPad(float x, float y, float z, float angle, float rotX, float rotY, float rotZ)
{
	glColor3ub(138,127,128);
	glTranslatef(x, y, z);
	glRotatef(angle, rotX, rotY, rotZ);
	glPushMatrix();
		glutSolidCube(10);
	glPopMatrix();
}

//draws the key card
void drawCard(float cardX, float cardZ)
{
	//glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	
	glTranslatef(cardX , 0, cardZ );
	glRotatef(45, 0, 0, 1);
	glRotatef(cardRot += 5, 1, 1, 0);
	glScalef(0.2, 0.3, 0.02);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId2);
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

//draws the minimap at the top left of the screen
void drawMinimap()
{
	glPushMatrix();
	glPointSize(5);
	glBegin(GL_POINTS);	
				
	for(int i = 0; i < GRID_SIZE; i++)
	{
		for(int j = 0; j < GRID_SIZE; j++)
		{
			if(newMazeArray[findInArray(i,j)] == 1 || newMazeArray[findInArray(i,j)] == 2)
			{
				if(!fullscreen)
					glVertex3f((-windowW/2.2) + i*5 , (windowH/2.2) - j*5, 0);
				else glVertex3f((-windowW/2.2) + i*2 , (windowH/2.2) - j*3.6, 0);
				
			}
		}		
	}
		
	
	glColor3f(1,0,0);


	if(!fullscreen)
	{
		glVertex3f((-windowW/2.2) + Cam.Transform[12]/2, (windowH/2.2) - Cam.Transform[14]/2 , 0);
	}
	else 
	{
		glVertex3f((-windowW/2.2) + Cam.Transform[12]/5, (windowH/2.2) - Cam.Transform[14]/3.6 , 0);
	}
	
	//glVertex3f(0,0 , 0);
	glEnd();
	glPopMatrix();
}

//draws the screen that informs the user that 
//they need to collect the key card to exit the maze
void drawCNeed()
{
	glPushMatrix();
		glTranslatef(0.0f, -windowH/2.28, 0.0f);
		glColor3f(1,1,1);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId4);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBegin(GL_QUADS);
				glNormal3f(0.0, 0.0f, 1.0f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex2f(-600/2, -100/2);		//Bottom Left
				glTexCoord2f(1.0f, 0.0f);	
				glVertex2f(600/2, -100/2);		//Bottom Right
				glTexCoord2f(1.0f, 1.0f);
				glVertex2f(600/2, 100/2);		//Top Right
				glTexCoord2f(0.0f, 1.0f);
				glVertex2f(-600/2, 100/2);		//Top Left 
			glEnd();
	glPopMatrix();
}

//draws the success screen when the user has escaped
void drawFinish()
{
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glColor3f(1,1,1);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId5);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBegin(GL_QUADS);
				glNormal3f(0.0, 0.0f, 1.0f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex2f(-400, -400);		//Bottom Left
				glTexCoord2f(1.0f, 0.0f);	
				glVertex2f(400, -400);		//Bottom Right
				glTexCoord2f(1.0f, 1.0f);
				glVertex2f(400, 400);		//Top Right
				glTexCoord2f(0.0f, 1.0f);
				glVertex2f(-400, 400);		//Top Left 
			glEnd();
	glPopMatrix();
}

//draws the failure screen to inform the user that they have been caught
void drawDeath()
{
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glColor3f(1,1,1);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId6);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBegin(GL_QUADS);
				glNormal3f(0.0, 0.0f, 1.0f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex2f(-400, -400);		//Bottom Left
				glTexCoord2f(1.0f, 0.0f);	
				glVertex2f(400, -400);		//Bottom Right
				glTexCoord2f(1.0f, 1.0f);
				glVertex2f(400, 400);		//Top Right
				glTexCoord2f(0.0f, 1.0f);
				glVertex2f(-400, 400);		//Top Left 
			glEnd();
	glPopMatrix();
}

//loops through the maze array, drawing the cubes
void newSetupMaze()
{
	if (!mazeFinished)
	{
		
		int x = 0;
		int z = 0;
		int index = 0;
		for(int i = 0; i < sizeof(newMazeArray)/sizeof(newMazeArray[0]); i++)
		{
			if (newMazeArray[i] == 1)
			{
				myCubes[index++] = new Cube(x, z, _textureId);
				numberOfCubes++;
			}
			if (newMazeArray[i] == 2)
			{
				myCubes[index++] = new Cube(x, z, _textureId3);
				numberOfCubes++;
			}
		
			z++;
			if (z > GRID_WIDTH - 1)
			{
				z = 0;
				x++;
			}
		}

		//key card random positioning
		int a, b;

		do
		{
			a = rand() % 19 + 1;
			b = rand() % 19 + 1;
		} while (newMazeArray[findInArray(a, b)] == 1);

		cardX = a * 10;
		cardZ = b * 10;

		

		mazeFinished = true;
	}

	for(int i = 0; i < numberOfCubes; i++)
	{
		myCubes[i]->DrawCube();
	}

}

//draws 3D elements in OpenGL
void draw3D()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	//glEnable(GL_CULL_FACE);
	if(!lightingOn)
	{
		glDisable(GL_FOG);
	}
	else if(lightingOn)
	{
		glEnable(GL_FOG);
	}
	
	GLfloat fogColor[] = {0.0f, 0.0f, 0.0f, 1};
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 0.0f);
	glFogf(GL_FOG_END, 20.0f);
	glFogf(GL_FOG_DENSITY, 1.0f);

	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV, (float)resizeWindowW/(float)resizeWindowH, 1.0, 5000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	Cam.setView(); 

	glDisable(GL_TEXTURE_2D);
	Monster->DrawEnemy();
	Monster->updateEnemy(Cam.Transform[12], Cam.Transform[14]);

	bulletNegX->drawBullet();
	bulletPosX->drawBullet();
	bulletNegZ->drawBullet();
	bulletPosZ->drawBullet();

	glPushMatrix();
		newSetupMaze();
	glPopMatrix();
	
	glPushMatrix();
		if (!cardCollected)
			drawCard(cardX, cardZ);
	glPopMatrix();

	glPushMatrix();
		glScalef(23.0, 1.0, 23.0);
		drawPad(4, -10.0, 4, 0.0, 0.0, 0.0, 0.0);
	glPopMatrix();
}

//draws 2D elements in OpenGL
void draw2D()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glEnable(GL_LINE_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-windowW/2, windowW/2, -windowH/2, windowH/2, -1000.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
		glColor3ub(127, 255, 212);
		drawCrosshair();
	glPopMatrix();

	glPushMatrix();
		glColor3ub(255, 255, 255);
		drawMinimap();
	glPopMatrix();

	if(cardCollected)
	{
		glPushMatrix();
			glColor3f(1,1,1);
			glTranslatef(windowW/2.8, windowH/2.5, 0.0f);
		
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId2); 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBegin(GL_QUADS);

			glColor3f(1,1,1);
			glTranslatef(500, -windowH/2.2, 0.0f);
			//glRotatef(90, 0,1,0);

			glNormal3f(0.0, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(-130/2, -75/2);		//Bottom Left
			glTexCoord2f(0.0f, 0.0f);
			
			glVertex2f(130/2, -75/2);		//Bottom Right
			glTexCoord2f(1.0f, 0.0f);
		
			glVertex2f(130/2, 75/2);		//Top Right
			glTexCoord2f(1.0f, 1.0f);
		
			glVertex2f(-130/2, 75/2);		//Top Left 

			glEnd();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	if((Cam.Transform[12] == 194.2f && Cam.Transform[14] > 185.8f) && cardCollected == false)
	{
		drawCNeed();
	}
	if(finish == true)
	{
		drawFinish();
	}
	if(Monster->killed)
	{
		drawDeath();
	}
	glDisable(GL_LINE_SMOOTH);
}
void drawScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	draw3D();
	draw2D();	
	glDisable(GL_TEXTURE_2D);	
	glutSwapBuffers();
}

//loops and handles frame updates
void update(int value)
{
	if(Cam.Transform[12] > 195.0f && Cam.Transform[14] > 185.0f)
	{
		finish = true;
	}
	if(finish == true)
	{
		//cout << "WELL DONE" << endl;
	}
	if (shoot == true)
	{
		if (!setBulletPos)
		{
			bulletNegX->setPos(((int)(Cam.Transform[12] + 5.0f) / 10) * 10, ((int)(Cam.Transform[14] + 5.0f) / 10) * 10);
			bulletNegX->updatePos = true;
			bulletPosX->setPos(((int)(Cam.Transform[12] + 5.0f) / 10) * 10, ((int)(Cam.Transform[14] + 5.0f) / 10) * 10);
			bulletPosX->updatePos = true;
			bulletNegZ->setPos(((int)(Cam.Transform[12] + 5.0f) / 10) * 10, ((int)(Cam.Transform[14] + 5.0f) / 10) * 10);
			bulletNegZ->updatePos = true;
			bulletPosZ->setPos(((int)(Cam.Transform[12] + 5.0f) / 10) * 10, ((int)(Cam.Transform[14] + 5.0f) / 10) * 10);
			bulletPosZ->updatePos = true;
			setBulletPos = true;
		}
		

		bulletNegX->Update(false, true, false, false);
		bulletPosX->Update(true, false, false, false);
		bulletNegZ->Update(false, false, false, true);
		bulletPosZ->Update(false, false, true, false);
		
		if (newMazeArray[findInArray(bulletNegX->getGridX(), bulletNegX->getGridZ())] == 1)
		{
			cout << "boo" << endl;
			bulletNegX->updatePos = false;
			bulletNegX->setPos(-10, -10);
		}
		if ((bulletNegX->getGridX() == Monster->properties.gridX) && (bulletNegX->getGridZ() == Monster->properties.gridZ))
		{
			bulletNegX->updatePos = false;
			bulletNegX->setPos(-10, -10);
			Monster->brain->enemyState = Monster->brain->flee;
			Monster->properties.speed = 0.6;
		}

		if (newMazeArray[findInArray(bulletPosX->getGridX(), bulletPosX->getGridZ())] == 1)
		{
			bulletPosX->updatePos = false;
			bulletPosX->setPos(-10, -10);
		}
		if ((bulletPosX->getGridX() == Monster->properties.gridX) && (bulletPosX->getGridZ() == Monster->properties.gridZ))
		{
			bulletPosX->updatePos = false;
			bulletPosX->setPos(-10, -10);
			Monster->brain->enemyState = Monster->brain->flee;
			Monster->properties.speed = 0.6;
		}

		if (newMazeArray[findInArray(bulletPosZ->getGridX(), bulletPosZ->getGridZ())] == 1)
		{
			bulletPosZ->updatePos = false;
			bulletPosZ->setPos(-10, -10);
		}
		if ((bulletPosZ->getGridX() == Monster->properties.gridX) && (bulletPosZ->getGridZ() == Monster->properties.gridZ))
		{
			bulletPosZ->updatePos = false;
			bulletPosZ->setPos(-10, -10);
			Monster->brain->enemyState = Monster->brain->flee;
			Monster->properties.speed = 0.6;
		}

		if (newMazeArray[findInArray(bulletNegZ->getGridX(), bulletNegZ->getGridZ())] == 1)
		{
			bulletNegZ->updatePos = false;
			bulletNegZ->setPos(-10, -10);
		}
		if ((bulletNegZ->getGridX() == Monster->properties.gridX) && (bulletNegZ->getGridZ() == Monster->properties.gridZ))
		{
			bulletNegZ->updatePos = false;
			bulletNegZ->setPos(-10, -10);
			Monster->brain->enemyState = Monster->brain->flee;
			Monster->properties.speed = 0.6;
		}

		if (bulletNegX->updatePos == false &&
			bulletPosX->updatePos == false &&
			bulletNegZ->updatePos == false &&
			bulletPosZ->updatePos == false)
		{
			shoot = false;
			setBulletPos = false;
		}
		
	}
	if(!flashActive)
	{
		int flashChance = rand() % 1000;
		if(flashChance < 5)
			flashActive = true;
	}
	if(flashActive && lightFrame < 5)
	{
		lightingOn = false;
		lightFrame++;
		//PlaySound(TEXT("thunder.wav"), NULL, SND_ASYNC);
	}
	else 
	{
		lightingOn = true;
		lightFrame = 0;
		flashActive = false;
	}
	if(keyLeftPressed == true)
	{
		//Cam.rotateGlob(3, 0,-1, 0);
		Cam.moveLoc(0.5, 0, 0, -1);
	}
	if(keyRightPressed == true)
	{
		//Cam.rotateGlob(3, 0, 1, 0);
		Cam.moveLoc(0.5, 0, 0, 1);
	}
	if(keyUpPressed == true)
	{
		//Cam.rotateLoc(3, -1, 0, 0);
		if(!camTurn)Cam.moveLoc(0, 0, 0.5, 1);
		else Cam.moveLoc(0, 0, 0.5, -1);
	}
	if(keyDownPressed == true)
	{
		//Cam.rotateLoc(3, 1, 0, 0);
		Cam.moveLoc(0, 0, 0.5, -1);
	}
	if(lookLeft == true)
	{
		Cam.rotateLoc(speed, 0,-1,0);
	}
	if(lookRight == true)
	{
		Cam.rotateLoc(speed, 0,1,0);
	}
	checkBounds();
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}


//OpenGL initilaising function, leading to game loop
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowW, windowH);	
	glutCreateWindow("The Maze ugghh sprinter...");
	initRendering();	
	glutDisplayFunc(drawScene);
	PlaySound(TEXT("Spookyforest.wav"), NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);	
	glutKeyboardFunc(handleKeypress);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialUpFunc(specialKeyUp);
	glutSpecialFunc(handleSpecialKeypress);		//"SpecialKeypress" for special key presses , arrow keys
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);	
	glutMainLoop();
	return 0;
}

