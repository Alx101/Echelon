#include "E_Testing.h"


tester::tester()
{
	#ifdef _DEBUG
	//All class's or function's that need to be tested are initialized here.
	tree = new binaryTree();




	//No initialization's or function call's beyond this point
	test();
	#endif
}

tester::~tester()
{
	#ifdef _DEBUG
	delete tree;
	//Delete all the class's created here

	#endif
}

void tester::test()
{
	//All needed operations should be performed here
}

void tester::Update()
{
	#ifdef _DEBUG
	//All Update functions and functions that need to be iterated are called here

	#endif
}
