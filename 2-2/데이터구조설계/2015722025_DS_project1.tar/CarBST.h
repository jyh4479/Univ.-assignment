#pragma once
#include "CarNode.h"
#include <iostream>
#include <fstream>// header file declare

using namespace std;
class CarBST
{
public:
	CarNode * root = NULL;
public:
	CarBST();
	~CarBST();
	void		Insert(CarNode * node);			// LOAD, MOVE
	CarNode *	Delete(int num);				// COMPLETE
	CarNode * Search(int num, ofstream & flog, char * codename); // ADD, COMPLETE, SEARCH
	bool		Print(const char * order, ofstream&flog);		// PRINT
	bool		Save();             // SAVE



	void        Inorder(const char* order, ofstream&flog); //The funtion is Recursive function
	void		Inorder(const char* order, CarNode *node,ofstream&flog);

	void        Preorder(const char* order, ofstream&flog); 
	void		Preorder(const char* order, CarNode *node, ofstream&flog);

	void        Postorder(const char* order, ofstream&flog); 
	void		Postorder(const char* order, CarNode *node, ofstream&flog);

	void levelOrder(const char * order, ofstream & flog); //The function print node according to leveling

	void I_preorder(const char * order, ofstream & flog); //The function is Repeat function
	void I_inorder(const char * order, ofstream & flog);
	void I_postorder(const char * order, ofstream & flog);

	///////////////////////////////Self makes function
	CarNode *	Complete(int num, ofstream& flog);
	CarNode * Getroot() { return root; }
	void savepreorder(ofstream&flog);
	void exit(CarNode * node);
	void savepreorder(CarNode * current, ofstream&flog);
	void visit(CarNode* current,ofstream&flog) //For printing data
	{
		flog << current->GetcarNum() << " ";
		flog << current->GetcarOwner() << " ";
		flog << current->Getstate() << endl;
	}
};

