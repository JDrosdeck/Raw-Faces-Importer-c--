#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "rawImporter.h"
#include <pthread.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#else
#include <GL/glut.h>

#endif

using namespace std;

#define WIRE 1
#define POINT 2
#define ROTATE 3
#define FULL 4


float _angle = 0;            //The rotation
float xpos = 0.0;
float ypos = 0.0;
float zpos = 0.0;

bool spin = false;
bool wire = false;
bool point = false;


void handleKeypress(unsigned char key, int x, int y)
 {
	switch (key) {
		case 'w':
			zpos+=5;
			break;
		case 's':
			zpos-=5;
			break;
		case 'd':
			xpos-=5;
			break;
		case 'a':
			xpos+=5;
			break;		
		case 'o':
			ypos+=5;
			break;
		case 'l':
			ypos-=5;
			break;
		case 27: //Escape key
			exit(0);
	}
}




void initRendering() 
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void drawScene() 
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	glTranslatef(xpos, ypos, zpos);
	
	//gluLookAt(xpos, ypos, zpos, xpos,0.0,0.0,0.0,1.0,0.0);

	
	GLfloat ambientLight[] = {0.6f, 0.6f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	GLfloat lightColor[] = {0.7f, 1.0f, 0.7f, 1.0f};
	GLfloat lightPos[] = {0, 0, 1.0f};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	
	
	
	glRotatef(-_angle, 0.0f, 1.0f, 1.0f);
	
	glBegin(GL_QUADS);


	/*
	Code for importing a model.
	NOTE: Remember to free each row of vertex's after you load them. Otherwise you'll get a huge memory leak
	*/
	
	
	
	
	float **model = readModel("small_blimp.RAW", 0.0, -5.0, -3.0);
	int x;
	for(x = 0; x < getLength(); x++)
	{
		glVertex3f(model[x][0], model[x][1], model[x][2]);
		free(model[x]);
	}
	free(model);
	
	
	
	
	
	
	
	
	
	
	

	glEnd();
	//glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
	//glFlush();
}

//Called every 25 milliseconds
void update(int value) 
{
	if(spin == true)
	{
		_angle += 10.0f;
		if (_angle > 360) 
		{
			_angle -= 360;
		}
	}
		glutPostRedisplay();
		glutTimerFunc(25, update, 0);
	
}

void processMenu(int option) {

	switch (option) {
		case WIRE : 
			if(wire == false)
		 	{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				point = false;
				wire = true;
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				wire = false;
			}
			
			break;
		case POINT:
			if(point == false)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				wire = false;
				point = true;
				
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				point = false;
				
			}
			break;
			
		case ROTATE:
			if(spin == false)
				spin = true;
			else
				spin = false;
			break;
		case FULL:
			glutFullScreen();
			break;
			

	}
}

void createMenu() {

	int menu;

	// create the menu and
	// tell glut that "processMenuEvents" will 
	// handle the events
	menu = glutCreateMenu(processMenu);
	
	//add entries to our menu
	glutAddMenuEntry("Wire",WIRE);
	glutAddMenuEntry("Point", POINT);
	glutAddMenuEntry("Rotate", ROTATE);
	glutAddMenuEntry("Fullscreen", FULL);
	
	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}





int main(int argc, char** argv) 
{
	
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Model Viewer");
	initRendering();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	createMenu();
	glutMainLoop();

	
	return 0;
}









