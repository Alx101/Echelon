#include "E_Custom_Algorithms.h"
#include <iostream>

miscFuncVar::miscFuncVar()
{
	for(int i = 0; i < _ROOTSIZE_; i++)
    {
    	rooted[i] = root(2, i);
    }
	for(int i = 0; i < _ROOTSIZE_; ++i)
	{
		boolVal[i] = 0;
	}
}

miscFuncVar::~miscFuncVar()
{
}

unsigned long int miscFuncVar::root(int toRoot, int timesToRoot)
{
    unsigned long int var = (unsigned long int)toRoot;
    timesToRoot = timesToRoot - 1;
    for(int i = 0; i < timesToRoot; i++)
    {
    	var = var * toRoot;   
    }
    return(var);
}

/*
unsigned long int miscFuncVar::BoolToInt(bool* V[40])
{

}
*/

//Note: Need's fixing
void miscFuncVar::intToBool(unsigned long int data)
{
	unsigned long int root;
	roots = 0;

    for(int i = 0; i < 40; i++)
    {
     	if(data < rooted[i])
        {
         	roots = i;
            i = 40;
        }
    }
    for(int i = 0; i < roots; ++i)
    {
   		int rb = i + 1;
        root = rooted[rb];
        if((data%root) < (root/2))
		{
			boolVal[i] = 0;
		}
        else if((data%root) >= (root/2))
		{
			boolVal[i] = 1;
		}
    }

}

void miscFuncVar::printBoolVal()
{
	for(int i = 0; i < roots; i++)
	{
		std::cout << boolVal[i];
	}
	std::cout << "\n";
}

binaryTree::binaryTree()
{
	unsigned long int var = 54;
	mfv.intToBool(var);
	mfv.printBoolVal();
}

binaryTree::~binaryTree()
{
}


























