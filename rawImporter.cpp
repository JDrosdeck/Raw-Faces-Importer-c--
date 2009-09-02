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
	string line;
	float **vertexList;
	int arrayIndex = 0;	
	int index = 0;
	
		
	getline(model, line);
	if(model) 
	{

		//The model is OK for reading, Allocate some space for the first numbers
		
		vertexList = (float **) malloc(1 * sizeof(float));
		if(vertexList == NULL)
		{
			cout << "Error: Malloc unable to allocate enough memory" << endl;
			exit(1);
		}
		vertexList[arrayIndex] = (float *) malloc(3 * sizeof(float));
		if(vertexList[arrayIndex] == NULL)
		{
			cout << "Error: Malloc unable to allocate enough memory" << endl;
			exit(1);
		}
	}
	
	
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
			vertexList[arrayIndex][index] = pointCoord;
			
						
			index++; 
			if(index == 3)
			{
				//We've just read a full set of vertex coordinates, Allocate some space for the next set
				arrayIndex++;
				vertexList = (float **)realloc(vertexList, (arrayIndex+1) * sizeof(float));
				if(vertexList == NULL)
				{
					cout << "Error: Malloc unable to allocate enough memory" << endl;
					exit(1);
				}
				vertexList[arrayIndex] = (float *) malloc(3 * sizeof(float));
				if(vertexList[arrayIndex] == NULL)
				{
					cout << "Error: Malloc unable to allocate enough memory" << endl;
					exit(1);
				}
				index = 0;
				Length = arrayIndex;
			}
		}
		
		line.clear(); //reset the line;
		getline(model, line);// get the next line	
	}
	
	return vertexList;
}

int main(int argc, char *argv[])
{
	float **value = readModel("cylinder.RAW");
	
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