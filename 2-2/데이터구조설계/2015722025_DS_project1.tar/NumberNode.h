#pragma once
#include "CarBST.h"

class NumberNode
{
private:
	int number;
	CarBST * bst=NULL;
	NumberNode * pLeft=NULL;			// BST Left Pointer
	NumberNode * pRight=NULL;		// BST Right Pointer

public:
	NumberNode(int data)
	{
		number = data;
	}
	~NumberNode();

	int			GetNumber() { return number; };						// Get Number
	CarBST *		GetBST() { return bst; };						// Get Car BST
	NumberNode *	GetLeft() { return pLeft; };						// Get BST Left Pointer
	NumberNode *	GetRight() { return pRight; };						// Get BST Right Pointer

	void			SetNumber(int num) { number = num; };				// Set Alphabet
	void			SetLeft(NumberNode * node) { pLeft = node; };		// Set BST Left Pointer
	void			SetRight(NumberNode * node) { pRight = node; };	// Set BST Right Pointer
	void 			SetBST(CarBST * node) { bst = node; };			// Set Car BST
};
