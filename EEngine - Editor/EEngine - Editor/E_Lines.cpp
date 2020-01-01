#include <iostream>
#include "E_Lines.h"
#include "common_header.h"

using namespace EEngine;
using namespace std;

pathline::pathline(vectors vpos1, vectors vpos2)
{
  pos1 = new pathvectors;
  pos1->x = (int)(vpos1.x);
  pos1->y = (int)(vpos1.y);
  pos1->z = (int)(vpos1.z);

  pos2 = new pathvectors;
  pos2->x = (int)(vpos2.x);
  pos2->y = (int)(vpos2.y);
  pos2->z = (int)(vpos2.z);
  
  pathSlopes = new pathvectors;
  findSlope();
  
  curPoint = 0;
  
  pathBuffer = new pathvectors;
  pathBuffer->x = pos1->x;
  pathBuffer->y = pos1->y;
  pathBuffer->z = pos1->z;
  
}

pathline::~pathline()
{

}

void pathline::findSlope()
{
	pathSlopes = new pathvectors;
	pathSlopes->y = (pos2->y - pos1->y)/(pos2->x - pos1->x);
	pathSlopes->z = (pos2->z - pos1->z)/(pos2->x - pos1->x);
}


void pathline::nextPoint()
{
	if(pos1->x < pos2->x)
		pathBuffer->x = pathBuffer->x + 1;
	else
		pathBuffer->x = pathBuffer->x - 1;

	if(pos1->y < pos2->y)
		pathBuffer->y = (pathBuffer->y + pathSlopes->y);
	else if(pos1->y > pos2->y)
		pathBuffer->y = (pathBuffer->y - pathSlopes->y);

	if(pos1->z < pos2->z)
		pathBuffer->z = (pathBuffer->z + pathSlopes->z);
	else if(pos1->z > pos2->z)
		pathBuffer->z = (pathBuffer->z - pathSlopes->z);

	vectorBuffer = new vectors;
	vectorBuffer->x = pathBuffer->x + 0.5;
	vectorBuffer->y = pathBuffer->y + 0.5;
	vectorBuffer->z = pathBuffer->z + 0.5;
  
	curPoint = curPoint + 1;
	path[curPoint] = vectorBuffer;
	cout << "\n" << vectorBuffer->x << "\n" << vectorBuffer->y << "\n" << vectorBuffer->z << "\n";
	
}

void pathline::startLine()
{
	int intervals = 0;
	if(pos1->x < pos2->x)
		intervals = (pos2->x - pos1->x);
	else if(pos1->x > pos2->x)
		intervals = (pos1->x - pos2->x);

	if(curPoint < intervals)
	{
		nextPoint(); //This while loop takes up all other update functions, please revise this
	}
}

int i;