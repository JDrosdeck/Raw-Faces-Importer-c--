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


int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("Usage: ./optimizer modelToLoad.raw outPut.raw\n");
		exit(1);
	}
	
	int matches = 0;
	char * modelLoad = argv[1];
	char * outFile = argv[2];
	printf("Loading Model-> %s\n", modelLoad);
	float **model = readModel(modelLoad, 0.0, -5.0, -3.0);
	printf("Model Sucessfully Loaded\n");
	printf("Optimizing\n");
	int x,y;
	for(x = 0; x < getLength(); x++)
	{
		for(y = 0; y < getLength()-x; y++)
		{
			if((model[x][0] == model[y][0]) && (model[x][1] == model[y][1]))
			{
				matches++;	
				model[y][0] = '\0';
				model[y][1] = '\0';
				model[y][2] = '\0';
			}
		}
	}

	printf("Able to optimize %i verticies\n", matches);
	ofstream myfile;
	
	myfile.open(outFile);
	for(x = 0; x < getLength(); x++)
	{
		if(model[x][0] != '\0')
		{
			myfile << model[x][0] << " " << model[x][1] << " " << model[x][2] << endl;
		}
		free(model[x]);
	}

	free(model);
	myfile.close();
	return 0;
}