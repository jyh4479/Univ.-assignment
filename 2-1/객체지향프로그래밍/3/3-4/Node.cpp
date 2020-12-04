#include "Node.h"
#include "queue.h"
#include<iostream>

void Node::setnumber(int number)
{
	cardnumber = number; //Save number to cardnumber
}

void Node::setshape(char shape)
{
	cardshape = shape; //Save shape to cardshape
}

void Node :: setnext(Node* next)
{
	Next = next; //Save next to Next
	return;
}

int Node::number(Node* a)
{
	return a->cardnumber; //For access private value
}

char Node::shape(Node* a)
{
	return a->cardshape; //For access private value
}
Node* Node::next(Node*a)
{
	return a->Next; //For access private value
}

int Node :: getnumber()
{
	return rand() % 13 + 1; //Get random number 1~13
}

char Node::getshape()
{
	switch (rand() % 4) //Get random alphabet for shape
	{
	case 0:
		return 'a';
	case 1:
		return 'b';
	case 2:
		return 'c';
	case 3:
		return 'd';
	}
}
