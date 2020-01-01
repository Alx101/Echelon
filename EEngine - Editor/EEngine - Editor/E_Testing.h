#ifndef _E_TESTING_
#define _E_TESTING_
//This file is for easy testing of Class's or Function's
//Only works during debuging so the players won't know what we are testing.

//Include all file's need for testing the class's or function's
#include "E_Custom_Algorithms.h"

class tester
{
public:
	tester();
	~tester();
	void Update();
private:
	//All class's that need to be tested are defined here(Must be a pointer)
	binaryTree* tree;
	void test();
};



#endif