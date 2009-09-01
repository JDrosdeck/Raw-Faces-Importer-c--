#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;

int Length;
int Width = 3; //(x,y,z)



/*
readModel will read in the vertex coordinates from a .RAW file and return a 2D matrix
of the vertex's (x,y,z)
*/
float** readModel(string filePath)
{
	ifstream model;
	model.open(filePath.c_str());
	if(!model)
	{
		cout << "Unable to open file" << endl;
		exit(1);
	}
	
	//Loop through once so we can determine how large to make the array
	int maxVerticies = 1;
	int numberOfPoints = 1;
	float *points;
	string line;
	getline(model, line);
	if(model) 
	{
		points = (float *) malloc(1 * sizeof(float));
		if(points == NULL)
		{
			cout << "Error: Malloc unable to allocate enough memory" << endl;
			exit(1);
		}
	}
	
	int arrayIndex = 0;	
	while(model) //the model was successfully read
	{
		
		//Tokenize the line based on " "
		string token;
		istringstream iss(line);
		while(getline(iss, token, ' '))
		{
			//convert the token to a float value
			float pointCoord;
			if(EOF == sscanf(token.c_str(), "%f", &pointCoord))
			{
				cout << "Error converting string to float" << endl;
			}
			
			points[arrayIndex] = pointCoord;
			token.clear();
			arrayIndex++;
			points = (float *)realloc(points, (arrayIndex + 1) * sizeof(float));
			if(points == NULL)
			{
				cout << "Error: Malloc unable to allocate enough memory" << endl;
				exit(1);
			}
		}
		
		line.clear(); //reset the line;
		getline(model, line);// get the next line	
	}
	
	
	//At this point we know the total number of points, Dividing by 3 will give us the right amount of values
	maxVerticies = arrayIndex / 3;
	Length = maxVerticies;
	line.clear();
	
	float **vertexList;
	
	vertexList = (float **) malloc(maxVerticies * sizeof(float));
	if(vertexList == NULL)
	{
		cout << "Error: malloc could not allocate enough space" << endl;
		exit(1);
	}
	
	int i;
	//Allocate space for the floats
	for(i = 0; i < maxVerticies; i++)
	{
		vertexList[i] = (float *) malloc(3 * sizeof(float)); //3 is used because we have X, Y, Z values
		if(vertexList[i] == NULL)
		{
			cout << "Error: malloc could not allocate enough space" << endl;
			exit(1);
		}
	}
	
	model.close();

	
	//Fill the actual matrix with the values that are being temporarily stored
	//in the array.
	

	int x = 0;
	int y = 0;
	int pointLoop = 0;
	
	for(x = 0; x < maxVerticies; x++)
	{
		for(y = 0; y < 3; y++)
		{
			vertexList[x][y] = points[pointLoop];
			pointLoop++;
		}
	}
	
	
	
	free(points); //free the memory associated with this array	
	
	return vertexList;
}

int main(int argc, char *argv[])
{
	float **value = readModel("cube.RAW");

	cout << Length << endl;
	
	int x,y;
	for(x = 0; x < Length; x++)
	{
		cout << x << ": ";
		for(y = 0; y < Width; y++)
		{
			cout << value[x][y] << " ";
		}
		
		cout << endl;
	}
	
	free(value);
	exit(0);
	
}