#ifndef _Lines
#define _Lines

#include <iostream>
#include "common_header.h"

using namespace std;

namespace EEngine
{

class pathvectors
{
public:
	int x;
	double y;
	double z;
};

class pathline
{
public:
	pathline(vectors vpos1, vectors vpos2);
	~pathline();
	pathvectors *pos1;
	pathvectors *pos2;
	pathvectors *pathSlopes;
	void findSlope();
	void nextPoint();
	void startLine();
	map<int, vectors*> path;
	pathvectors *pathBuffer;
	int curPoint;
	vectors *vectorBuffer;
};
}


#endif






