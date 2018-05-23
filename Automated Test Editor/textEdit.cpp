#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

string line;
string xCoord, yCoord;
const char* xCoords;
const char* yCoords;
//char xCoordTok;
//char* yCoordTok;

int main()
{
	int i = 1;
	while (i < 55)
	{
		std::string s = std::to_string(i);
		const char *no = s.c_str();
		char textFile[12] = { '\0' };
		strcpy(textFile, "image");
		strcat(textFile, no);
		strcat(textFile, ".txt");
		ifstream file(textFile);
		int l = 1;
		while (l < 8)
		{
			getline(file, line);
			if (l == 4)
			{
				xCoord = line;
				char* xCoordTok = new char[xCoord.length() + 1];
				strcpy(xCoordTok, xCoord.c_str());
				char* tok;
				tok = strtok(xCoordTok, ":");
				while (tok != NULL)
				{
					if (tok != "X Coordinate")
					{
						xCoords = tok;
					}
					tok = strtok(NULL, ":");
				}
			}
			else if(l == 5)
			{
				yCoord = line;
				char* yCoordTok = new char[yCoord.length() + 1];
				strcpy(yCoordTok, yCoord.c_str());
				char* tok;
				tok = strtok(yCoordTok, ":");
				while (tok != NULL)
				{
					if (tok != "Y Coordinate")
					{
						yCoords = tok;
					}
					tok = strtok(NULL, ":");
				}
			}
			l++;
		}
		int xVal = atoi(xCoords);
		int yVal = atoi(yCoords);
		int quad;
		if (xVal < 683 && yVal < 384)
		{
			quad = 1;
		}
		else if (xVal < 683 && yVal > 384)
		{
			quad = 3;
		}
		else if (xVal > 683 && yVal < 384)
		{
			quad = 2;
		}
		else if (xVal > 683 && yVal > 384)
		{
			quad = 4;
		}
		else
		{
			quad = 0;
		}
		std::string sq = std::to_string(quad);
		const char *quadValChar = sq.c_str();
		FILE* imgFile = fopen(textFile, "a");
		fprintf(imgFile, "Quadrant:");
		fprintf(imgFile, quadValChar);
		i++;
	}

    //return 0;
}
