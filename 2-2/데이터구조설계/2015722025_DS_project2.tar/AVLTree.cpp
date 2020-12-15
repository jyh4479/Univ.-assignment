#include "AVLTree.h"

AVLTree::AVLTree(ofstream* fout){ //The constructure
	root=NULL; //root is NULL
	make_heap(vHeap.begin(), vHeap.end(), compare); //make heap
	this->fout = fout;
}

AVLTree::~AVLTree(){

}

bool AVLTree::Insert(StockData* pSto){ //The function of insert

	AVLNode* pNew = new AVLNode; //Declare Node
	pNew->setSD(pSto); //Load data
	char	*pName = pSto->getName();
	int		rotation = 0;

	if(root == NULL){ //if root is NULL, pNew is root, and return true
		root = pNew;
		return true;
	}

	AVLNode* a = root, //Declare sub AVLNode for inserting
			*pa = NULL,
			*p = root,
			*pp = NULL,
			*rootSub = NULL;

	while (p != NULL) //if p is not NULL, repeat the function
	{
		if (p->getBF() != 0) { a = p; pa = pp; } //check balance factor
		
		if (strcmp(pSto->getName(), p->getSD()->getName()) < 0) { pp = p; p = p->getLeft(); } //Move Node
		else if (strcmp(pSto->getName(), p->getSD()->getName()) > 0) { pp = p; p = p->getRight(); }
		else { p->setSD(pSto); return true; } //The condition that equals name
	}

	if (strcmp(pSto->getName(), pp->getSD()->getName()) < 0) pp->setLeft(pNew); //link Node
	else  pp->setRight(pNew);
	
	int d; //Declare d, for balance factor
	AVLNode *b, //for rotation
			*c;

	if (strcmp(pSto->getName(), a->getSD()->getName()) < 0) { b = p = a->getLeft(); d = 1; } //Load The data of Node
	else { b = p = a->getRight(); d = -1; }

	while (p != pNew) //If p is not pNew, repeat the function
	{
		if (strcmp(pSto->getName(), p->getSD()->getName()) < 0) { p->setBF(1); p = p->getLeft(); } //check condition
		else { p->setBF(-1); p = p->getRight(); } //else
	}

	if (a->getBF() == 0 || a->getBF() + d == 0) //Check balance factor
	{
		a->setBF(a->getBF() + d); return true;
	}
	/////////////////////////////////rotation
	if (d == 1)
	{//left imbalance
		if (b->getBF() == 1)
		{//LL rotation
			a->setLeft(b->getRight()); //Move Node
			b->setRight(a); a->setBF(0); b->setBF(0);
			rootSub = b;
		}
		else
		{//LR rotation
			c = b->getRight(); //Move Node
			b->setRight(c->getLeft());
			a->setLeft(c->getRight());
			c->setLeft(b);
			c->setRight(a);
			switch (c->getBF())
			{
			case 0: //Check balance factor
				b->setBF(0); a->setBF(0);
				break;
			case 1:
				a->setBF(-1); b->setBF(0);
				break;
			case -1:
				b->setBF(1); a->setBF(0);
				break;
			}
			c->setBF(0); rootSub = c; //c is new root
		} //end of LR
	} //end of left imbalance

	else
	{ //right imbalance
		if (b->getBF() == -1)
		{ //RR rotation
			a->setRight(b->getLeft());
			b->setLeft(a); a->setBF(0); b->setBF(0);
			rootSub = b;
		}
		else
		{ //RL rotation
			c = b->getLeft();
			b->setLeft(c->getRight());
			a->setRight(c->getLeft());
			c->setRight(b);
			c->setLeft(a);
			switch (c->getBF())
			{ //check balance factor
			case 0:
				b->setBF(0); a->setBF(0);
				break;
			case 1:
				b->setBF(-1); a->setBF(0);
				break;
			case -1:
				a->setBF(1); b->setBF(0);
				break;
			}
			c->setBF(0); rootSub = c; //c is the new root
		} //end of RL
	}

	//Subtree with root b has been rebalanced
	if (pa == NULL) root = rootSub;
	else if (a == pa->getRight()) pa->setRight(rootSub);
	else pa->setLeft(rootSub);
	return true;
} //end of AVL Insert

bool AVLTree::Print(){ //Pritn function
	if (root == NULL) //if root is NULL
		return false; //return false

	stack<AVLNode*> s; //Declare stack
	AVLNode* current = root; //load root

	*fout << "==================== PRINT =====================" << endl;
	while (1) //repeat function until break
	{
		while (current != NULL) //if current is not NULL, repeat function
		{
			s.push(current); //push current
			current = current->getLeft(); //Move current
		}

		if (!s.empty()) //check empty
		{
			current = s.top(); //load data of top
			s.pop(); //delete
		}
		if (current == NULL) //if current is NULL
			break; //break
		printStockInfo(current->getSD()); //print data
		*fout << endl;
		current = current->getRight(); //Move Node
	}
	*fout << "================================================" << endl;
	return true; //return true*
}

bool AVLTree::Search(char* name){ //search Node
	AVLNode *pCur = root; //load root

	while (pCur) //searching information
	{
		if (strcmp(pCur->getSD()->getName(), name) > 0) pCur = pCur->getLeft();
		else if (strcmp(pCur->getSD()->getName(), name) < 0) pCur = pCur->getRight();
		else break;
	}

	if (pCur == NULL) //if pCur is NULL
		return false; //return false

	*fout << "======= SEARCH =======" << endl;
	printStockInfo(pCur->getSD()); //print data
	*fout << "======================" << endl;

	StockData* pSD = pCur->getSD(); //for insert heap

	if (vHeap.size() == 0) //check size
		vHeap.push_back(make_pair(make_pair(1000, 1000), pSD)); //insert big data for compare

	vHeap.push_back(make_pair(make_pair(pSD->getEarning(), pSD->getStockID()), pSD)); //push data

	pair< pair<double, int>, StockData* >temp; //Declare temp

	int currentNode = vHeap.size()-1; //Declare currentNode
	while (currentNode != 1 && vHeap[currentNode / 2].first.first < pSD->getEarning())
	{ //repeat function until make correcting Max heap
		temp = vHeap[currentNode / 2]; //swap
		vHeap[currentNode/2]= vHeap[currentNode];
		vHeap[currentNode] = temp;
	//	vHeap[currentNode / 2].swap(vHeap[currentNode]); //Don't work in Linux
		currentNode /= 2;
	}
	push_heap(vHeap.begin(), vHeap.end(), compare);
	return true; //return true;
}

void AVLTree::Exit() { //Exit function
	deleteNode(root);
}

void AVLTree::deleteNode(AVLNode*pNode) { //Delete Memory
	if (pNode != NULL)
	{ //delete using post order
		deleteNode(pNode->getLeft());
		deleteNode(pNode->getRight());
		delete pNode;
	}
}

bool AVLTree::Rank(){ //Rank function
	if (vHeap.empty()) return false; //check empty

	StockData* pSto;

	sort_heap(vHeap.begin(), vHeap.end(), compare); //sort heap
	vHeap.pop_back(); //delete big data for comparing
	reverse(vHeap.begin(), vHeap.end()); //reverse
	
	*fout << "==================== RANK =====================" << endl;
	while(!vHeap.empty()){ //delete all, print data 
		pSto = vHeap.front().second;
		pop_heap(vHeap.begin(), vHeap.end(), compare);
		vHeap.pop_back();
		printStockInfo(pSto);
		*fout << endl;
	}
	*fout << "===============================================" << endl;
	return true;
}

void AVLTree::printStockInfo(StockData* pStockData){ //The function of printing data
	fout->setf(ios::fixed);
	fout->precision(2); 
	*fout << pStockData->getStockID() << " " << pStockData->getName() << " " << pStockData->getEarning() << endl;
	*fout << "시가: " << pStockData->getOpening_Price() << endl;
	*fout << "종가: " << pStockData->getClosing_Price() << endl;
	*fout << "거래량: " << pStockData->getVolume() << endl;
	*fout << "수익률: " << pStockData->getEarning() << endl;
}

