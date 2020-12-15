#ifndef _BPTREEINDEXNODE_H_
#define _BPTREEINDEXNODE_H_

#include "BpTreeNode.h"

class BpTreeIndexNode : public BpTreeNode{
private:
	map <double, BpTreeNode*> mapIndex;
	
public:
	BpTreeIndexNode(){}
	~BpTreeIndexNode(){}
	
	void insertIndexMap(double n, BpTreeNode* pN){ //insert data
		mapIndex.insert(make_pair(n,pN));
	}

	void deleteMap(double n){ //delete data
		mapIndex.erase(n);
	}

	map <double, BpTreeNode*>* getIndexMap()	{ return &mapIndex; }
};

#endif
