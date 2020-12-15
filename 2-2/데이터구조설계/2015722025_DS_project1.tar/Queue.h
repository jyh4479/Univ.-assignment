#pragma once
#include "CarNode.h"
#include <fstream>
class Queue
{
public: 		// public member funciton
	Queue();	
	~Queue();
	CarNode * pHead = NULL;						// member variable
	void		Push(CarNode * node);			// LOAD
	CarNode *	Pop();							
	CarNode *	Search(int num, ofstream&flog, char*codename); // SEARCH
	bool		Print(ofstream& flog);				// PRINT
	bool		Save();
};