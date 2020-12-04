#include "DepartmentList.h"

DepartmentList::DepartmentList()
{
}


DepartmentList::~DepartmentList()
{
}

bool DepartmentList::check(char * name) //The function for checking there is same department or not
{
	Node* tmp = mHead;

	if (mHead == NULL || tmp->getNext() == NULL)
		return 1; //If Head is NULL, return 1

	else if (mHead != NULL)
	{
		for (;tmp; tmp = tmp->getNext())
		{
			if (!strcmp(tmp->getInfo(),name))
				return 0; //If there is same department department, return 0
		}
		return 1; //else return 1
	}
}

void DepartmentList::LinkHead()
{ //A function that makes a list of departments circular
	Node* tmp = mHead;

	while (tmp->getNext())
		tmp = tmp->getNext();

	tmp->setNext(mHead);
}

void DepartmentList::insert_de(char * name) //The funciton works for inserting Node
{
	Node* tmp = mHead;
	Node* prev = mHead;

	if (check(name)) //The function checking same department
	{
		if (mHead == NULL)
		{ //If there is no information on the list
			DepartmentNode* newNode = new DepartmentNode;
			newNode->Save_de(name);
			mHead = newNode; //new Node is Head
			mtail = newNode;
			return;
		}

		else if (mHead != NULL)
		{ //If there is information in the list
			for (; tmp; tmp = tmp->getNext()) //Algorithm for Ascending
			{
				if (strcmp(tmp->getInfo(), name) == -1)
				{ //When the incoming information is larger
					if (tmp->getNext() == NULL)
					{
						DepartmentNode* newNode = new DepartmentNode;
						newNode->Save_de(name);
						tmp->setNext(newNode);
						newNode->setNext(NULL);

						mtail = newNode;

						return;
					}
					else
						continue;
				}
				else if (strcmp(tmp->getInfo(), name) == 1)
				{ //When the incoming information is smaller
					DepartmentNode* newNode = new DepartmentNode;
					newNode->Save_de(name);

					if (tmp == mHead)
					{
						newNode->setNext(tmp);
						mHead = newNode;
						return;
					}
					else if (tmp != mHead)
					{
						while (prev->getNext() != tmp)
							prev = prev->getNext();

						newNode->setNext(tmp);
						prev->setNext(newNode);
						return;
					}
				}
			}
		}
	}
}

void DepartmentList::linktail() //Head-to-tail function
{
	mtail->setNext(mHead);
	mHead->setPrev(mtail);

	Node*tmp = mHead;

	for (int a = 1; a != 0; tmp = tmp->getNext())
	{
		if (!strcmp(tmp->getInfo(), mtail->getInfo()))
			a = 0;
	}
}

void DepartmentList::changeHead(DepartmentNode* newNode) //Functions that compare values ​​and change heads
{
	if (strcmp(newNode->getInfo(), mHead->getInfo()) == -1)
	{//If the information is smaller than the head, replace the head.
		mHead = newNode;
	}
	else
		return;
}

void DepartmentList::changetail(DepartmentNode* newNode) //Functions that compare values ​​and change tails
{
	if (strcmp(newNode->getInfo(), mtail->getInfo()) == 1)
	{//If you compare the information with the information, change the tail if it is larger than the tail.
		mtail = newNode;
	}
	else
		return;
}

void DepartmentList::newcreate(char*a ,char*b,Node*tmp)
{ //A function for creating new departments
	Node*prev = tmp->getNext();
	for (; prev->getNext()!=tmp; prev = prev->getNext());

	DepartmentNode* newNode = new DepartmentNode;
	newNode->Save_de(b); //Information on new subjects

	newNode->setDown(tmp->getDown()); //A command to store links to the original lesson
	tmp->getDown()->setUp(newNode); //A command to store links to the original lesson
	prev->setNext(tmp->getNext()); //A command to store links to the original lesson

	Node*tmp2 = NULL;


	prev = mHead->getNext();
	tmp2 = mHead;

	for (; prev->getNext() != tmp2; prev = prev->getNext());

	for (int a = 1; a; prev = prev->getNext(), tmp2 = tmp2->getNext())
	{ //A function that connects the names of departments
		if (strcmp(newNode->getInfo(), tmp2->getInfo()) == -1)
		{
			prev->setNext(newNode);
			newNode->setNext(tmp2);
			changeHead(newNode); //Function that determines head by comparing size
			changetail(newNode); //Function that determines tail by comparing size
			break;
		}

		if (prev == mtail&&strcmp(newNode->getInfo(), prev->getInfo()) == 1) //At the far end
		{
			prev->setNext(newNode);
			newNode->setNext(tmp2);
			changeHead(newNode); //Function that determines head by comparing size
			changetail(newNode); //Function that determines tail by comparing size
			break;
		}
	}	
	delete tmp;
}

bool DepartmentList::Check2(Node*tmp, Node*tail)
{ //Function that checks the size of information
	Node*Compare = tmp->getDown();

	for (; Compare != tail->getDown(); tmp = tmp->getDown(), Compare = Compare->getDown())
	{
		if (strcmp(tmp->getInfo(), Compare->getInfo()) == 1) //Return if the information is larger
			return 1;
	}
	return 0; //else, return 0;
}

void DepartmentList::sortingname(char*b)
{ //A function to sort the people in the department concerned
	Node*tmp = mHead;
	Node*tail = mHead;;
	Node*Cur1 = NULL;
	Node*Cur2 = NULL;
	int a = 1;

	for (; strcmp(tmp->getInfo(), b); tmp = tmp->getNext()); //For seek head of student
	for (; strcmp(tail->getInfo(), b); tail = tail->getNext()); //For seek tail of student
	for (; tail->getDown(); tail = tail->getDown());
	tail = tail->getUp();
	tmp = tmp->getDown();

	for (; Check2(tmp, tail);) //repeat the function, untill check return 0
	{
		Cur1 = tmp;
		Cur2 = Cur1->getDown();

		while (strcmp(Cur1->getInfo(), Cur2->getInfo()) != 1)
		{ //If Cur 1 is less than Cur 2, repeat continuously.
			Cur1 = Cur1->getDown();
			Cur2 = Cur2->getDown();
		}
		Cur1->getUp()->setDown(Cur1->getDown());
		Cur2->getDown()->setUp(Cur2->getUp());
		Cur1->setDown(Cur2->getDown());
		Cur2->setUp(Cur1->getUp());
		Cur1->setUp(Cur2);
		Cur2->setDown(Cur1);
	}

	Node*compare1 = tmp;
	Node*compare2 = tmp;

	for (; compare2->getDown(); compare2 = compare2->getDown());
	compare1 = compare2;

	for (; compare1 != tmp;)
	{
		compare1 = compare1->getUp();
		if (strcmp(compare2->getInfo(), compare1->getInfo()) == -1)
			break;
		if (tmp == compare1)
			return;
	}

	///////The code below is a code that aligns the end student separately.////////

	for (; tail->getDown(); tail = tail->getDown());
	tmp = tail->getUp();

	while (a) //repeat the function, If a is not 0
	{
		if (strcmp(tail->getInfo(), tmp->getInfo()) == 1)
			a = 0;
		tmp = tmp->getUp();
	}
	tmp = tmp->getDown();

	tail->getUp()->setDown(NULL);
	tmp->getDown()->setUp(tail);
	tail->setDown(tmp->getDown());
	tmp->setDown(tail);
	tail->setUp(tmp);
}

void DepartmentList::MoveDepartment(char*a,char*b)
{ //A shifting function
	Node*tmp = mHead;
	Node*tmp2 = mHead;
	Node*De = mHead;

	for (; strcmp(tmp->getInfo(), a); tmp = tmp->getNext());
	for (; strcmp(tmp2->getInfo(), b); tmp2 = tmp2->getNext());
	//Function that finds received parameters

	for (; De->getNext() != tmp; De = De->getNext());
	//Repeat function until information matches

	//The code below is a command to connect new departments
	De->setNext(tmp->getNext());
	De = tmp;

	tmp = tmp->getDown();

	for (; tmp2->getDown(); tmp2 = tmp2->getDown());

	tmp->setUp(tmp2);
	tmp2->setDown(tmp);

	sortingname(b); //A function to sort new incoming students

	delete De; //Delete department
}

void DepartmentList::workModify(Node*Dtmp, char*a, char*b)
{ //Function that executes the actual Modify
	Node*Department = mHead;
	Node*tmp = Dtmp;
	int check = 1;

	for (; Department != mtail;)
	{
		if (!strcmp(b, Department->getInfo()))
		{ //Find the right department
			check = 0;
			break;
		}
		Department = Department->getNext();
	}

	if (check)
	{ //Run repeat if check is not zero
		for (Department = mHead; Department != mtail;)
		{
			Department = Department->getNext();
			if (!strcmp(a, Department->getInfo()))
				break;
			//Break if the information found is the same as the information received
		}
		if (strcmp(b, Department->getInfo()))
			newcreate(a,b, Department);
		//Create a new department if there is no department to transfer
	}
	
	else
		MoveDepartment(a,b);
	//In the case above, execute a function of transferring departments if not caught.
}

void DepartmentList::Modify(char*a,char*b,ofstream&LOGFILE)
{ //Function of the step before sending information to the function to be executed by receiving the Modify command
	Node*tmp = mHead;
	Node*tmptail = mtail;

	if (!strcmp(a, mHead->getInfo()) || !strcmp(a, mtail->getInfo()))
	{ //Handle exceptions when head or tail moves
		if (!strcmp(a, mHead->getInfo()))
		{ //When the head moves
			DepartmentNode* newHead = new DepartmentNode;
			Node* cur = mHead->getNext();
			Node* tmp2 = tmp;

			//Move information to a new node
			newHead->Save_de(cur->getInfo());
			newHead->setNext(cur->getNext());
			newHead->setDown(cur->getDown());
			cur->getDown()->setUp(newHead);
			mHead->setNext(newHead);

			delete cur;
			mHead = newHead;

			cur = mHead;

			//Determine the creation or integration of new disciplines
			for (int check = 1; check; cur = cur->getNext())
			{
				if (!strcmp(b, cur->getInfo()))
				{
					MoveDepartment(a, b);
					return;
				}
				if (cur == mtail)
					check = 0;
			}
			newcreate(a, b, tmp);
			return;

		}

		else if (!strcmp(a, mtail->getInfo()))
		{ //When the tail moves
			DepartmentNode* newtail = new DepartmentNode;
			Node*cur = mtail;
			Node*prevcur = mtail;

			for (; cur->getNext() != mtail; cur = cur->getNext());
			for (; prevcur->getNext() != cur; prevcur = prevcur->getNext());


			//Move information to a new node
			newtail->Save_de(cur->getInfo());
			newtail->setDown(cur->getDown());
			cur->getDown()->setUp(newtail);
			prevcur->setNext(newtail);
			newtail->setNext(mtail);

			delete cur;
			mtail = newtail;

			cur = mtail;

			//Determine the creation or integration of new disciplines
			for (int check = 1; check; cur = cur->getNext())
			{
				if (!strcmp(b, cur->getInfo()))
				{
					MoveDepartment(a, b);
					return;
				}
				if (cur == prevcur)
					check = 0;
			}
			newcreate(a, b, tmptail);
			return;
		}
	}

	for (; tmp != mtail;)
	{ //A function that gets the right information
		tmp = tmp->getNext();
		if (!strcmp(a, tmp->getInfo()))
			break;
	}
		workModify(tmp,a,b);
	//Deliver the information you have obtained and execute the functions that will work
}

void DepartmentList::Delete(char*a)
{ //A function that deletes the subject.
	Node*tmp = mHead;
	Node*bye = NULL;
	Node*tmp2 = tmp->getNext();
	Node*tmp3 = tmp->getNext();

	if (!strcmp(a, mHead->getInfo()) || !strcmp(a, mtail->getInfo()))
	{ //If the head of the department is erased
		if (!strcmp(a, mHead->getInfo()))
		{
			DepartmentNode*newNode = new DepartmentNode;

			//Head moving algorithm
			newNode->Save_de(tmp2->getInfo());
			newNode->setNext(tmp2->getNext());
			newNode->setDown(tmp2->getDown());
			tmp2->getDown()->setUp(newNode);
			mHead->setNext(newNode);
			mHead = newNode;
			delete tmp2;
		}

		else
		{ //When the tail of the department disappears
			for (; tmp2->getNext() != mtail; tmp2 = tmp2->getNext());
			for (; tmp3->getNext() != tmp2; tmp3 = tmp3->getNext());
			DepartmentNode*newNode = new DepartmentNode;

			//Algorithm to move tail
			newNode->Save_de(tmp2->getInfo());
			newNode->setNext(tmp2->getNext());
			newNode->setDown(tmp2->getDown());
			tmp2->getDown()->setUp(newNode);
			tmp3->setNext(newNode);
			mtail = newNode;
			delete tmp2;
		}
	}

	for (; strcmp(tmp->getInfo(), a); tmp = tmp->getNext());
	for (; tmp->getDown(); tmp = tmp->getDown());

	for (; tmp->getUp();)
	{
		bye = tmp;
		tmp->getPrev()->setNext(tmp->getNext());
		tmp->getNext()->setPrev(tmp->getPrev());
		delete tmp->getGrade(); //An order to erase information from the departme
		delete tmp->getID();
		delete tmp->getPhone();
		tmp = tmp->getUp();
		delete bye;
	}

	bye = tmp;
	for (; bye->getNext() != tmp; bye = bye->getNext());
	bye->setNext(tmp->getNext());

	delete tmp; //An order to delete the subject's memory.
	return;
}

void DepartmentList::Print()
{ //Function that performs Print command
	Node* tmp = mHead;
	Node* tmp2 = mHead->getDown();
	int a = 1;
	int count = 1;

	for (; a; tmp = tmp->getNext())
	{
		cout << tmp->getInfo() << " : ";
		for (tmp2=tmp->getDown(); tmp2; tmp2 = tmp2->getDown(),count++)
		{
			cout << tmp2->getInfo() << " "<<count;
		}
		if (tmp == mtail)
			a = 0;
		cout << endl;
	}
	return ;
}

void DepartmentList::Savetxt(char*a)
{ //Function that performs Save command
	ofstream Save(a);
	Node*tmp = mHead;
	Node*tmp2 = mHead->getDown();

	for (; tmp != mtail;)
	{
		for (tmp2=tmp->getDown();tmp2;tmp2=tmp2->getDown())
		{ //Print Node
			Save << tmp->getInfo() << " / ";
			Save << tmp2->getInfo() << " / ";
			Save << tmp2->getGrade()->getGradeInfo() << " / ";
			Save << tmp2->getID()->getIDInfo() << " / ";
			Save << tmp2->getPhone()->getPhoneInfo();
			Save << endl;
		}
		tmp = tmp->getNext();
	}
	for (tmp2 = tmp->getDown(); tmp2; tmp2 = tmp2->getDown())
	{ //Print end of Node
		Save << tmp->getInfo() << " / ";
		Save << tmp2->getInfo() << " / ";
		Save << tmp2->getGrade()->getGradeInfo() << " / ";
		Save << tmp2->getID()->getIDInfo() << " / ";
		Save << tmp2->getPhone()->getPhoneInfo();
		Save << endl;
	}
}

