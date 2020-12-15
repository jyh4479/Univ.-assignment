#include "BpTree.h"
using namespace std;

BpTree::BpTree(ofstream* fout, int order = 3) { //The constructure
	root = NULL; //Save NULL to root
	this->order = order;
	this->fout = fout;
}

BpTree::~BpTree() {

}

void BpTree::Insert(StockData* pSto) { //for insert Node

	double key = pSto->getEarning();   // key = Earning
	vector<pair<int, StockData*> > value;         // value = map< id, stock data* >
	value.push_back(make_pair(pSto->getStockID(), pSto)); //push data to value

	if (root == NULL) { //if root is NULL
		BpTreeNode* pDataNode = new BpTreeDataNode; //The Node for root
		dynamic_cast<BpTreeDataNode*>(pDataNode)->insertDataMap(key, value); //insert data
		root = pDataNode; //Declare root
		return;
	}
	BpTreeNode* pDataNode = searchDataNode(key); //Search Node
	map<double, vector<pair<int, StockData*> > >*pMap = dynamic_cast<BpTreeDataNode*>(pDataNode)->getDataMap(); //load data of map
	map<double, vector<pair<int, StockData*> > >::iterator iterator; //Declare iterator
	pair<int, StockData*> tmp; //Declare tmp
	iterator = pMap->begin(); //load data of map

	int flag = 0; //flag
	int i, j; //for bubble sort

	for (int a = 0; a < pMap->size(); a++)
	{ //search equal data
		if (pMap->find(key) == iterator) //If the key data is equal
		{
			flag = 1; // set flag
			iterator->second.push_back(make_pair(pSto->getStockID(), pSto)); //push data
			if (iterator->second.size() > 1)
			{ //practice bubble sort
				for (i = 0; i < iterator->second.size() - 1; i++)
				{
					for (j = 0; j < iterator->second.size() - (i + 1); j++)
					{
						if (iterator->second[j].first < iterator->second[j + 1].first)
						{
							tmp = iterator->second[j];
							iterator->second[j] = iterator->second[j + 1];
							iterator->second[j + 1] = tmp;
						}
					}
				}
			}
			return; //return
		}
		else //else
			iterator++; //Move iterator
	}

	if (flag == 0) //if flag is 0
		dynamic_cast<BpTreeDataNode*>(pDataNode)->insertDataMap(key, value); //insert data

	if (exceedDataNode(pDataNode)) //check need split or not
		splitDataNode(pDataNode); //split
	return; //return
}

BpTreeNode* BpTree::searchDataNode(double n) { //The Search Node
	
	BpTreeNode* pCur = root; //load root
	map<double, BpTreeNode*>::iterator itIndex; //Declare iterator

	while (pCur->getMostLeftChild() != NULL) //If pCur->left is Node NULL, repeat the function
	{
		itIndex = dynamic_cast<BpTreeIndexNode*>(pCur)->getIndexMap()->begin();

		if (n < itIndex->first) //if n is smaller than data
		{
			pCur = pCur->getMostLeftChild();
		}

		else //else
		{
			while (true) //repeat the function until break
			{
				itIndex++; //move iterator
				if (itIndex == dynamic_cast<BpTreeIndexNode*>(pCur)->getIndexMap()->end() || n < itIndex->first)
				{
					itIndex--; //move iterator
					pCur = itIndex->second;
					break;
				}
			}
		}
	}
	return pCur; //return pCur
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) { //for split data Node

	int splitPosition_data = 2; //for check middle data

	BpTreeNode* p = NULL; //Declare parent
	BpTreeNode* newNode = new BpTreeDataNode(); //create new data Node
	map<double, vector<pair<int, StockData*> >>::iterator iterator, end; //iterator, end
	iterator = dynamic_cast<BpTreeDataNode*>(pDataNode)->getDataMap()->end(); //load data of iterator
	iterator--; //Move iterator

	for (int a = dynamic_cast<BpTreeDataNode*>(pDataNode)->getDataMap()->size(); a >= 2; a--)
	{ //create new data Node
		end = iterator;
		dynamic_cast<BpTreeDataNode*>(newNode)->insertDataMap(iterator->first, iterator->second); iterator--; //insert information
		dynamic_cast<BpTreeDataNode*>(pDataNode)->deleteMap(end->first); //delete existing Data
	}

	if (dynamic_cast<BpTreeDataNode*>(pDataNode)->getNext() != NULL) //If pNode->next is not NULL
	{
		dynamic_cast<BpTreeDataNode*>(dynamic_cast<BpTreeDataNode*>(pDataNode)->getNext())->setPrev(newNode); //link new Node
		dynamic_cast<BpTreeDataNode*>(newNode)->setNext(dynamic_cast<BpTreeDataNode*>(pDataNode)->getNext());
		dynamic_cast<BpTreeDataNode*>(pDataNode)->setNext(newNode);
		dynamic_cast<BpTreeDataNode*>(newNode)->setPrev(pDataNode);
	}
	else //else
	{
		dynamic_cast<BpTreeDataNode*>(pDataNode)->setNext(newNode);
		dynamic_cast<BpTreeDataNode*>(newNode)->setPrev(pDataNode);
	}

	p = pDataNode->getParent(); //for create index Node
	if (pDataNode->getParent() == NULL) //if index Node is not root
	{
		BpTreeNode* newindex = new BpTreeIndexNode(); //create index Node
		dynamic_cast<BpTreeIndexNode*>(newindex)->insertIndexMap(dynamic_cast<BpTreeDataNode*>(newNode)->getDataMap()->begin()->first, newNode);
		//insert data of middle
		newindex->setMostLeftChild(pDataNode); //link new index Node and existing Node
		newNode->setParent(newindex);
		pDataNode->setParent(newindex);
		root = newindex; //Declare root
	}
	else //if index Node is root
	{
		dynamic_cast<BpTreeIndexNode*>(p)->insertIndexMap(dynamic_cast<BpTreeDataNode*>(newNode)->getDataMap()->begin()->first, newNode);
		//insert data of middle
		newNode->setParent(p); //link
	}


	p = pDataNode->getParent(); //load data
	if (exceedIndexNode(p)) //check number of data
	{
		BpTreeNode* tmp = p;
		while (true)
		{ //repeat function
			if (!exceedIndexNode(tmp)) //Repeat until size is correct
				break;
			splitIndexNode(tmp);   //splitIndexNode
			tmp = tmp->getParent();  //Move Node
		}
	}
	p = pDataNode; 
	while (true)
	{
		if (p->getParent() == NULL)
		{ //change root
			root = p; 
			break;
		}
		p = p->getParent(); //Move Node
	}
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) { //split Index Node

	int splitPosition_index = 2; //for check middle data
	map<double, BpTreeNode*>::iterator iterator, end; //iterator, end
	iterator = dynamic_cast<BpTreeIndexNode*>(pIndexNode)->getIndexMap()->end();//load data of iterator
	iterator--; //Move iterator
	BpTreeNode* newindexNode = new BpTreeIndexNode(); //create new index Node for spliting

	for (int a = dynamic_cast<BpTreeIndexNode*>(pIndexNode)->getIndexMap()->size(); a > splitPosition_index; a--)
	{
		end = iterator;
		dynamic_cast<BpTreeIndexNode*>(newindexNode)->insertIndexMap(iterator->first, iterator->second); //insert information
		iterator->second->setParent(newindexNode); //link Node
		iterator--;
		dynamic_cast<BpTreeIndexNode*>(pIndexNode)->deleteMap(end->first); //delete existing Data                       
																					
	}
	if (pIndexNode->getParent() == NULL) //if parent is NULL
	{
		BpTreeNode* newPnode = new BpTreeIndexNode(); //vreate new index Node
		newindexNode->setMostLeftChild(iterator->second); //link Node
		iterator->second->setParent(newindexNode);
		dynamic_cast<BpTreeIndexNode*>(newPnode)->insertIndexMap(iterator->first, newindexNode); //insert data
		dynamic_cast<BpTreeIndexNode*>(pIndexNode)->deleteMap(iterator->first); //delete data                
		newPnode->setMostLeftChild(pIndexNode); //link Node
		pIndexNode->setParent(newPnode);
		newindexNode->setParent(newPnode);
	}
	else //else
	{
		newindexNode->setMostLeftChild(iterator->second); //link Node
		iterator->second->setParent(newindexNode);
		dynamic_cast<BpTreeIndexNode*>(pIndexNode->getParent())->insertIndexMap(iterator->first, newindexNode); //insert data
		dynamic_cast<BpTreeIndexNode*>(pIndexNode)->deleteMap(iterator->first); //delete data
		newindexNode->setParent(pIndexNode->getParent());
	}
}

bool BpTree::exceedDataNode(BpTreeNode* pDataNode) {  //for checking size of data in Node
	map <double, vector<pair<int, StockData*> > > *m = dynamic_cast<BpTreeDataNode*>(pDataNode)->getDataMap();
	if (m->size() > order - 1)      return true;
	else                        return false;
}
bool BpTree::exceedIndexNode(BpTreeNode* pIndexNode) { //for checking size of data in Node
	map <double, BpTreeNode*> *m = dynamic_cast<BpTreeIndexNode*>(pIndexNode)->getIndexMap();

	if (m->size() > order - 1)      return true;
	else                        return false;
}

bool BpTree::Print() { //For printing data of b+ tree
	if (root == NULL) return false; //if root is NULL, return false

	BpTreeNode* pNode = root; //load root
	BpTreeNode* endNode;

	for (; pNode->getMostLeftChild(); pNode = pNode->getMostLeftChild()); //Move Node to most left
	endNode = pNode;
	for (; dynamic_cast<BpTreeDataNode*>(pNode)->getNext(); pNode = dynamic_cast<BpTreeDataNode*>(pNode)->getNext()); //Move Node to most right
	map<double, vector<pair<int, StockData*> > >::iterator itrange = dynamic_cast<BpTreeDataNode*>(pNode)->getDataMap()->begin(); //Declare iterator
	for (int a = 1; a != dynamic_cast<BpTreeDataNode*>(pNode)->getDataMap()->size(); a++, itrange++);

	map<double, vector<pair<int, StockData*> > >::iterator itprint; //iterator
	map<double, vector<pair<int, StockData*> > >*check; //for checking data

	*fout << "==================== PRINT =====================" << endl; //start print
	while (dynamic_cast<BpTreeDataNode*>(pNode) != dynamic_cast<BpTreeDataNode*>(endNode)->getPrev())//repeat before print all data
	{
		itprint = dynamic_cast<BpTreeDataNode*>(pNode)->getDataMap()->begin(); //load iterator
		check = dynamic_cast<BpTreeDataNode*>(pNode)->getDataMap(); //load map

		if (check->size() == 2) //check size
		{
			itprint++; //move iterator
			while (true) //repeat the function
			{
				vector<pair<int, StockData*> >::iterator itvector = itprint->second.begin();//Declare iterator of vector
				int vector = 0;
				while (vector != itprint->second.size())
				{ //print data of Node
					printStockInfo(itvector->second);
					itvector++;
					vector++;
				}
				if (check->begin() == itprint) break; //if data is end, escape loop
				itprint--;
			}
		}

		else //else
		{
			vector<pair<int, StockData*> >::iterator itvector = itprint->second.begin(); //load data

			int vector = 0;
			while (vector != itprint->second.size())
			{ //pritn all data of Node
				printStockInfo(itvector->second);
				itvector++;
				vector++;
			}
		}
		pNode = dynamic_cast<BpTreeDataNode*>(pNode)->getPrev();
	}
	*fout << "================================================" << endl << endl;
	return true;
}

bool BpTree::Search(double a, double b) 
{
	if (root == NULL) //If root is NULL return false
		return false;

	else //else
	{
		a = roundf(a * 100) / 100; //set unit
		b = roundf(b * 100) / 100;

		if (a > b) //check number
			return false;

		BpTreeNode* range = root; //check for range
		for (; range->getMostLeftChild(); range = range->getMostLeftChild());
		if (dynamic_cast<BpTreeDataNode*>(range)->getDataMap()->begin()->first > b) return false; //over the range

		for (; dynamic_cast<BpTreeDataNode*>(range)->getNext(); range = dynamic_cast<BpTreeDataNode*>(range)->getNext());
		map<double, vector<pair<int, StockData*> > >::iterator itrange = dynamic_cast<BpTreeDataNode*>(range)->getDataMap()->begin();
		for (int a = 1; a != dynamic_cast<BpTreeDataNode*>(range)->getDataMap()->size(); a++, itrange++);
		if (itrange->first < a) return false;



		BpTreeNode* Big, *Small;
		map<double, vector<pair<int, StockData*> > >::iterator BigNode, SmallNode, check;

		Big = dynamic_cast<BpTreeDataNode*>(searchDataNode(b));
		Small = dynamic_cast<BpTreeDataNode*>(searchDataNode(a));

		check = dynamic_cast<BpTreeDataNode*>(Big)->getDataMap()->begin();
		int flag = 0;
/////////////////////////////////////////////////////////////////////////////////check NULL range

		if (Big == Small) //check the range of empty
		{
			for (int i = 0; dynamic_cast<BpTreeDataNode*>(Big)->getDataMap()->size() > i; i++, check++)
			{
				if (check->first >= a&&check->first <= b)
				{
					flag = 1;
					break;
				}
			}
			if (flag == 0)
				return false;
		}
/////////////////////////////////////////////////////////////////////////////////////
		*fout << "======== SEARCH ========" << endl; //start SEARCH
		while (dynamic_cast<BpTreeDataNode*>(Big) != dynamic_cast<BpTreeDataNode*>(Small)->getPrev()) //repeat function until end
		{
			map<double, vector<pair<int, StockData*> > >*check = dynamic_cast<BpTreeDataNode*>(Big)->getDataMap(); //load data of map
			BigNode = dynamic_cast<BpTreeDataNode*>(Big)->getDataMap()->begin(); //Delcare Big Node
			SmallNode = dynamic_cast<BpTreeDataNode*>(Small)->getDataMap()->begin(); //Delcare Small Node

			int flag = check->size(); //Save data of size

			if (flag == 2) //if flag is 2
			{
				if (BigNode->first < b)
					BigNode++;
				if (BigNode->first < a) break; //check range

				while (true) //repeat function
				{
					vector<pair<int, StockData*> >::iterator itvector = BigNode->second.begin(); //load data of vector
					if (BigNode->first < a) break; //check range
					int vector = 0;
					while (vector != BigNode->second.size()) //for printing data of vector
					{
						if (BigNode->first > b) break; //check range
						printStockInfo(itvector->second);
						itvector++; //move iterator
						vector++; //move vector
					}
					if (check->begin() == BigNode) break; //if equal Node, escape loop
					BigNode--; //move iterator
				}
			}

			else //else
			{
				if (BigNode->first < a) break; //check range
				vector<pair<int, StockData*> >::iterator itvector = BigNode->second.begin(); //load data of vector

				int vector = 0;
				while (vector != BigNode->second.size()) //for printing data of vector
				{
					if (BigNode->first > b) break; //check range
					printStockInfo(itvector->second);
					itvector++; //move iterator
					vector++; //move vector
				}
			}
			Big = dynamic_cast<BpTreeDataNode*>(Big)->getPrev(); //Move Node to prev
		}
		*fout << "========================" << endl; //end searching
		return true; //return true
	}
}
void BpTree::printStockInfo(StockData* pStockData) { //The function of printing
	fout->setf(ios::fixed);   
	fout->precision(2);      
	*fout << pStockData->getStockID() << " ";
	*fout << pStockData->getName() << " ";
	*fout << pStockData->getEarning() << " " << endl;
	*fout << "시가: " << pStockData->getOpening_Price() << endl;
	*fout << "종가: " << pStockData->getClosing_Price() << endl;
	*fout << "거래량: " << pStockData->getVolume() << endl;
	*fout << "수익률: " << pStockData->getEarning() << endl<<endl;
}

void BpTree::printStockInfoBS(StockData* pStockData) { //The function of printing
	fout->setf(ios::fixed);
	fout->precision(2);
	*fout << pStockData->getStockID() << " ";
	*fout << pStockData->getName() << " ";
	*fout << pStockData->getEarning() << " " << endl;
}
