#pragma once
#include "NumberNode.h"
#include <iostream>


class NumberBST
{
private:
	NumberNode * root=NULL;
	int nodeCnt=0;

public:
	NumberBST();
	~NumberBST();


	void		Insert(NumberNode * node);			// LOAD, MOVE
	NumberNode *	Delete(int num, ofstream& flog);				// COMPLETE
	NumberNode *	Search(int num, ofstream& flog);				// ADD, COMPLETE, SEARCH
	bool		Print(char * BST,ofstream&flog);					// PRINT
	bool		Save(); // SAVE 

	void        Inorder(char* order,ofstream&flog); //The funtion is Recursive function
	void		Inorder(char* order, NumberNode *node,ofstream&flog);

	void        Preorder(char* order,ofstream&flog);
	void		Preorder(char* order, NumberNode *node,ofstream&flog);

	void        Postorder(char* order,ofstream&flog);
	void		Postorder(char* order, NumberNode *node, ofstream&flog);

	void I_preorder(char * order, ofstream & flog); //The function is Repeat function
	void I_inorder(char * order, ofstream & flog);
	void I_postorder(char * order, ofstream & flog);

	void levelOrder(char * order, ofstream & flog); //The function print node according to leveling

	int			getCnt(int n) { return nodeCnt=nodeCnt+n; }; //for checking number of Node in BST
	void		setCnt(int cnt) { nodeCnt = cnt; };

	//////////////////////////////

	NumberNode* Checknumber(int num);
	NumberNode* Getroot() { return root; }

	void exit(NumberNode*node); //The function for exit command

	void savepreorder(ofstream & e_list); //The function that for saving eventlist.txt
	void savepreorder(NumberNode * current, ofstream & e_list);

	void visit(NumberNode* current,ofstream&flog) //For printing data
	{
		flog << current->GetNumber() << endl;
	}
};
