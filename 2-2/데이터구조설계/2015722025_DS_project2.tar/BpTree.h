#ifndef _BPTREE_H_
#define _BPTREE_H_

#include "BpTreeIndexNode.h"
#include "BpTreeDataNode.h"

class BpTree{
private:
	BpTreeNode*	root; //The root
	int					order;	
	ofstream*		fout;

public:
	BpTree(ofstream * fout, int order);
	~BpTree();

	void	Insert(StockData* pStockData); //insert function
	bool	exceedDataNode(BpTreeNode* pDataNode); //check size
	bool	exceedIndexNode(BpTreeNode* pIndexNode);
	void	splitDataNode(BpTreeNode* pDataNode); //split
	void	splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode*	searchDataNode(double n); //search data

	bool	Print(); // PRINT_BP
	bool	Search(double a, double b); // SEARCH_BP	

	void	printStockInfo(StockData* pStockData); //print data
	void printStockInfoBS(StockData * pStockData);
};

#endif

