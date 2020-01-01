#include "common_header.h"
/*#include <exception>
#include <cstdlib>
#include <SFML/System.hpp>
#include <typeinfo>
#include <iostream>

using namespace EEngine;

memory::memory()
{
	for(int i = 0; i < _MEMORY_TO_ALLOCATE_; i++)
	{
		memoryHeap[i] = malloc(sizeof(void*));
	}
	for(int i = 0; i < _MEMORY_TO_ALLOCATE_; i++)
	{
		if(memoryHeap[i] == 0)
		{
			memoryHeap[i] = malloc(sizeof(void*));
			if(memoryHeap[i] == 0)
			{
				cout << "Unable to allocate enouph memory to run the program";
			}
		}
	}
	lastAvailableMemoryBlock;
}

memory::~memory()
{
	for(int i = 0; i < _MEMORY_TO_ALLOCATE_; i++)
	{
		free(memoryHeap[i]);
	}
}

void memory::release(void* p)
{
	free(p);
	memoryDeleted = true;
}

void* memory::allocate(size_t size)
{
	memoryHeap[lastAvailableMemoryBlock]= realloc(memoryHeap[lastAvailableMemoryBlock], size);
	void* p = memoryHeap[lastAvailableMemoryBlock];
	lastAvailableMemoryBlock += 1;
	//cout << "\nSize of current memoryHeap point: " << sizeof(memoryHeap[lastAvailableMemoryBlock]);
	return p;
}

memory mem;

void* operator new(size_t size)
{
	//cout << "\nUsed my new";
	void* p = mem.allocate(size);
	if (p==0)
		throw std::bad_alloc(); // ANSI/ISO compliant behavior
	return p;
}

void operator delete(void* p)
{
		mem.release(p);
}*/

string intToString(int i)
{
	stringstream tmp;
	tmp << i;
	return tmp.str();
}