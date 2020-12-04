#pragma once
#include "Node.h"

class queue //Declare class of queue
{
private:

public: //Declare variable and function that can be used every function
	int size;
	Node* mHead;
	Node* tail;

	queue();

	void Push(queue*q);
	bool IsEmpty(queue*q);
	bool IsFull(queue*q,int select);
	void Pop(queue*q);
	void print(queue*q);
	void same(queue* q);
};

