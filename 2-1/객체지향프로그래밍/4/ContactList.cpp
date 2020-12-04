#include "ContactList.h"

ContactList::ContactList()
{
}


ContactList::~ContactList()
{
}

void ContactList::link_Ph(DepartmentList&DepartmentList) //The function for linking contact Node
{
	Node* tmp = DepartmentList.mHead->getDown();
	for (; tmp->getPrev(); tmp = tmp->getPrev());
	Node* tmp2 = tmp->getNext();

	for (; tmp2; tmp2 = tmp2->getNext(), tmp = tmp->getNext())
	{ //A half-wrapped sentence for repetition from beginning to end
		tmp->getPhone()->setNext(tmp2->getPhone());
	}
	tmp->getPhone()->setNext(NULL);
}

