#include "LinkedList.h"


LinkedList::LinkedList()//constructor
{

}

LinkedList::~LinkedList()//destructor
{
	CarNode*tmp = pHead;
	while (tmp) //if tmp is not NULL
	{
		pHead = tmp->GetNext(); //save tmp->next Node to pHead
		delete tmp; //delete tmp
		tmp = pHead; //save pHead to tmp
	}
	/* You must fill here */
}

void LinkedList::Insert(CarNode * node)
{ //Insert Node
	if (pHead == NULL) //if pHead is NULL
	{
		pHead = node; //save node to pHead
		return; //return
	}
	else
	{
		CarNode* tmp = pHead; //Save information of pHead
		for (; tmp->GetNext(); tmp = tmp->GetNext()); //Move pointer to end
		tmp->SetNext(node); //set Node to next
	}
}

CarNode * LinkedList::Search(int car, ofstream& flog)
{ //The function for Searching Node
	if (this == NULL) //if this NULL
		return NULL; //return NULL

	CarNode * tmp = pHead; //save pHead
	
	if (tmp == NULL) //if tmp is null
		return NULL; //return NULL

	for (; tmp; tmp = tmp->GetNext())
	{ //repeat the function if tmp is not NULL
		if (tmp->GetcarNum() == car)
		{ //if equals the number
			flog << "======== " << "SEARCH" << " ========" << endl; //print data
			flog << tmp->GetcarNum() << " / ";
			flog << tmp->GetcarOwner() << " / ";
			flog << tmp->Getstate() << endl;
			flog << "=======================" << endl << endl;
			return tmp; //return tmp
		}
	}
	return NULL; //return NULL
}

bool LinkedList::Print(ofstream &flog)
{ //Print Total list
	CarNode* tmp = pHead;

	flog << "======== " << "PRINT "<<  "========" << endl;
	for (; tmp->GetNext(); tmp = tmp->GetNext())
	{ //repeat the function if tmp->next is not NULL
		flog << tmp->GetcarNum() << " / ";
		flog << tmp->GetcarOwner() << " / ";
		flog << tmp->Getstate();
		flog << endl;
	}
	flog << "=======================" << endl << endl;
	return 1; //return true
}

bool LinkedList::Save()
{ //for Saveing data
	ofstream t_list("total_list_car.txt"); //open file
	CarNode*tmp = pHead;
	for (; tmp; tmp = tmp->GetNext())
	{ //repeat the function if tmp->next is not NULL
		t_list << tmp->GetcarNum() << " ";
		t_list << tmp->GetcarOwner() << " ";
		t_list << tmp->Getstate() << endl;
	}
	return false;
}

bool LinkedList::Delete(CarNode * prev, CarNode * tmp)
{ //for Deleting data
	if (tmp == pHead)
	{ //if tmp == pHead
		pHead = tmp->GetNext(); //pHead = tmp->next
		tmp->SetNext(NULL); //set NULL
		return 1;
	}

	else
	{
		prev->SetNext(tmp->GetNext()); //set next
		tmp->SetNext(NULL); //set NULL
		return 0;
	}
}
