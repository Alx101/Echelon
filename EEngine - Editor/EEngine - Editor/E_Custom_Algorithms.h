#ifndef _CUSTOM_ALGORITHMS_H_
#define _CUSTOM_ALGORITHMS_H_

#define _ROOTSIZE_ 40

//These are just some Algorithms/Functions/Variables i've made in my free time that might be useful for the project -Jason

class miscFuncVar
{
	public:
		miscFuncVar();
		~miscFuncVar();
		unsigned long int root(int toRoot, int timesToRoot);
		unsigned long int BoolToInt(bool* V[40]);
		void intToBool(unsigned long int data);
		unsigned long int rooted[_ROOTSIZE_];
		void printBoolVal();
		int roots;
	private:
		bool boolVal[_ROOTSIZE_];
};


//This is the binary tree's node not the SceneNode
class node
{
	public:
		int x;
		int y;
		void* data;
		void setData(void* val)
		{
			data = val;
		}
		node* branch0;
		node* branch1;
};

class binaryTree
{
	public:
		binaryTree();
		~binaryTree();
		node tree;
		node findInt(unsigned long int data);
		node findBool(bool data[40]);
	private:
		miscFuncVar mfv;
		unsigned long int intVal;
};

























#endif