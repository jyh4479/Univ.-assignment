#include "StudentIDList.h"



StudentIDList::StudentIDList()
{
}


StudentIDList::~StudentIDList()
{
}

void StudentIDList::link_id(DepartmentList&DepartmentList)
{ //Function to link the ID
	Node* tmp = DepartmentList.mHead->getDown();
	for (; tmp->getPrev(); tmp = tmp->getPrev());
	Node* tmp2 = tmp->getNext();

	for (; tmp2; tmp2 = tmp2->getNext(), tmp = tmp->getNext())
	{//A half-wrapped sentence for repetition from beginning to end
		tmp->getID()->setNext(tmp2->getID());
	}
	tmp->getID()->setNext(NULL);
}