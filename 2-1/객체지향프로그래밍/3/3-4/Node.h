#pragma once
#include "Node.h"

class Node //Declare class of Node
{
private: //Declae variable that is used only Node class
	int cardnumber;
	char cardshape;
	Node* Next;

public: //Declare variable and function that can be used every function
	void setnumber(int number);
	void setshape(char shape);
	int getnumber();
	char getshape();
	void setnext(Node* next);
	int number(Node* a);
	char shape(Node* a);
	Node* next(Node*a);
};

