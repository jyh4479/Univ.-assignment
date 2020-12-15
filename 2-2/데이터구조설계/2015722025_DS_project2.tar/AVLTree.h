#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include "AVLNode.h"

class AVLTree{ //Declare AVL Tree
private:
	AVLNode*	root; //root
	vector < pair< pair<double, int>, StockData* > > vHeap; //for making tree
	ofstream*	fout;

public:
	AVLTree(ofstream* fout);
	~AVLTree();
	
	bool		Insert(StockData* pStu); //The function of insert
	bool		Print(); //print
	bool		Search(char* name); //search
	void Exit();
	void deleteNode(AVLNode * pNode);
	bool		Rank();

	void		printStockInfo(StockData* pStockData);
};

#endif

