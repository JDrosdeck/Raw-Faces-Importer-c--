#include <iostream>
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

float _angle = 0;            //The rotation
float xpos = 0.0;
float ypos = 0.0;
float zpos = 0.0;
bool spin = false;

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
		case 't':
			if(spin == false)
				spin = true;
			else
				spin = false;
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

	
	GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	GLfloat lightColor[] = {0.7f, 1.7f, 0.7f, 1.0f};
	GLfloat lightPos[] = {0, 0, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	
	glRotatef(-_angle, 0.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);


	/*
	Code for importing a model.
	NOTE: Remember to free each row of vertex's after you load them. Otherwise you'll get a huge memory leak
	*/
	
	
	float **model = readModel("MayanTemple.RAW", 1.0, 2.0, 1.0);
	int x;
	for(x = 0; x < getLength(); x++)
	{
		glVertex3f(model[x][0], model[x][1], model[x][2]);
		free(model[x]);
	}
	free(model);	

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
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


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Model Viewer");
	initRendering();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	glutMainLoop();
	return 0;
}









