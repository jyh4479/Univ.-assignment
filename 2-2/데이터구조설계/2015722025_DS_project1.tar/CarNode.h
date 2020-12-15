#pragma once
#include <iostream>
#include <cstring>
using namespace std;

class CarNode
{
private:
	int carNumber;
	char  name[50];
	char state[50];

	CarNode * pLeft=NULL;	// BST Left Pointer
	CarNode * pRight=NULL;	// BST Right Pointer
	CarNode * pNext=NULL;	// Queue Next Pointer, LinkedList Next Pointer


public:
	CarNode();
	
	~CarNode();

	int GetcarNum() { return carNumber; };	// Get car number
	char * GetcarOwner() { return name; };	// Get car owner
	char *Getstate() { return state; };		// Get state

	CarNode * GetLeft() { return pLeft; };	// Get BST Left Pointer
	CarNode * GetRight() { return pRight; };	// Get BST Right Pointer
	CarNode * GetNext() { return pNext; };	// Get Queue Next Pointer


	void SetcarNum(int num) { carNumber = num; };// Set car number
	void SetcarOwner(char* owner) { strcpy(name, owner); };// Set car owner
	void Setstate(char* State) { strcpy(state, State); };// Set car state
	//void SetcarNum(int carNum);			// Set car number
	//void SetcarOwner(char * carOwner);	// Set car owner
	//void Setstate(char state);			// Set car state
	void SetLeft(CarNode * node) { pLeft = node; };		// Set BST Left Pointer
	void SetRight(CarNode * node) { pRight = node; };		// Set BST Right Pointer
	void SetNext(CarNode * node) { this->pNext = node; };		// Set Queue Next Pointer
};

