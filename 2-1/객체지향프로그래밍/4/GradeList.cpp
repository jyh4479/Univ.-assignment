#include "GradeList.h"

GradeList::GradeList()
{
}


GradeList::~GradeList()
{
}

void GradeList::link_gr(DepartmentList&DepartmentList)
{ //A function that connects a school year
	Node* tmp = DepartmentList.mHead->getDown();
	for (;tmp->getPrev(); tmp = tmp->getPrev());
	Node* tmp2 = tmp->getNext();

	for (; tmp2; tmp2 = tmp2->getNext(), tmp = tmp->getNext())
	{ //A half-wrapped sentence for repetition from beginning to end

		tmp->getGrade()->setNext(tmp2->getGrade());
	}
	tmp->getGrade()->setNext(NULL);
}