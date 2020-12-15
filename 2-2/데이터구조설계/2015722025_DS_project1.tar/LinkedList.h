#pragma once
#include "CarNode.h"
#include <fstream>

class LinkedList
{
public:
	CarNode * pHead = NULL;

	LinkedList();
	~LinkedList();

	void Insert(CarNode * node);	//LOAD, ADD
	CarNode * Search(int car, ofstream& flog);		//SEARCH
	bool Print(ofstream &flog);	//PRINT
	bool Save();	//SAVE
	bool Delete(CarNode*prev, CarNode*tmp); //For complete
};
