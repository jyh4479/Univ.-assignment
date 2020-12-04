#include "NameList.h"

NameList::NameList()
{
}


NameList::~NameList()
{
}

void NameList::ChangeHead(NameNode* newNode) //Functions that compare values ​​and change heads
{
	if (nameHead == NULL) //If nameHead is NULL
		return; //return
	else
	{
		if (strcmp(nameHead->getInfo(), newNode->getInfo()) == -1)
			return; //If the value is larger than the original head, return
		else
		{
			nameHead = newNode; //If else , newNode is nameHead
		}
	}
}

void NameList::insert_na(char * department, char * name, DepartmentList &DepartmentList)
{ //Name node insert function
	Node* tmp = DepartmentList.mHead;
	Node* prev = NULL;
	Node* sub_de = NULL;
	Node* sub_head = NULL;

	for (; strcmp(department, tmp->getInfo()); tmp = tmp->getNext());
	//Compare the departments and stop at the appropriate department
	prev = tmp;

	if (tmp->getDown()==NULL) //When there is no person in the department
	{
		NameNode* newNode = new NameNode;
		if (nameHead == NULL)
			nameHead = newNode;
	
		newNode->Save_name(name);
		tmp->setDown(newNode);
		newNode->setUp(tmp);
		ChangeHead(newNode);
		return;
	}

	else if (tmp->getDown()!=NULL) //If there is a person in the department
	{
		sub_de = tmp;
		sub_head = tmp->getDown();
		tmp = tmp->getDown();

		for (; tmp; tmp = tmp->getDown())
		{ //Algorithm for inserting nodes by name
			{
				if (strcmp(tmp->getInfo(), name) == -1)
					if (tmp->getDown() == NULL)
					{
						NameNode* newNode = new NameNode;
						newNode->Save_name(name);
						tmp->setDown(newNode);
						newNode->setUp(tmp);
						newNode->setDown(NULL);
						ChangeHead(newNode);
						return;
					}
					else
						continue;
				else if (strcmp(tmp->getInfo(), name) == 1)
				{//If strcmp return 1, practice the function
					NameNode* newNode = new NameNode;
					newNode->Save_name(name);
					ChangeHead(newNode);

					if (tmp == sub_head)
					{ //if tmp is sub_head, practice the function
						newNode->setUp(sub_de);
						newNode->setDown(tmp);
						tmp->setUp(newNode);
						sub_de->setDown(newNode);
						return; //return
					}
					else if (tmp != sub_head)
					{ //if tmp is not sub_head, practice the funciton
						while (prev->getDown() != tmp) //repeat the function if getDown() is not tmp
							prev = prev->getDown();

						newNode->setUp(prev); //The function of link the Node
						newNode->setDown(tmp);
						tmp->setUp(newNode);
						prev->setDown(newNode);
						return; //return
					}
				}
			}
		}
	}
}

void NameList::link_na(DepartmentList &DepartmentList)
{//A function that associates name nodes that are connected to a department with names
	Node* tmp_de = DepartmentList.mHead;
	Node* tmp_d = DepartmentList.mHead;
	Node* prev = tmp_de->getDown();
	Node* tmp = prev->getDown();
	Node* Save_node = NULL;
	int a = 0, b = 0;

	for (; tmp_de; tmp_de = tmp_de->getNext())
	{ //repeat the function tmp_de is not NULL , and update tmp_de
		prev = tmp_de->getDown();
		tmp = prev->getDown();
		if (b == 1) //if b is 1, practice the function
		{
			Save_node->setNext(prev);
			prev->setPrev(Save_node);
		}

		if (tmp == NULL)
		{ //if tmp is NULL, practice the function
			Save_node->setNext(prev);
			prev->setPrev(Save_node);
			Save_node = prev;
			a = 1;
			continue;
		}

		for (; tmp; tmp = tmp->getDown(), prev = prev->getDown())
		{ //If tmp is not NULL, repeat the function
			b = 1;
			if (a == 1) //if a is 1, practice the function
			{
				Save_node->setNext(prev);
				prev->setPrev(Save_node);
				a = 0; //Save 0 to a
			}
			prev->setNext(tmp);
			tmp->setPrev(prev);
			Save_node = tmp;
		}
	}
}

bool NameList::Check(Node*tmp,Node*tail)
{ //A function that ensures that all name nodes are perfectly aligned
	Node*Compare = tmp->getNext();

	for (; Compare!=tail->getNext(); tmp = tmp->getNext(), Compare = Compare->getNext())
	{
		if (strcmp(tmp->getInfo(), Compare->getInfo()) == 1)//if tmp's information bigger than compare,
			return 1; //return 1
	}
	return 0; //else return 0
}

void NameList::sorting()
{ //A function that sorts connected name nodes
	Node *sHead;
	for (sHead = nameHead; sHead->getPrev(); sHead = sHead->getPrev());

	Node *Head = sHead;
	Node *tmp = Head;
	Node *tail = NULL;
	Node *Cur2 = NULL;
	Node *Cur1 = NULL;
	int a = 1;


	for (; tmp->getNext(); tmp = tmp->getNext()); //For seek tail
	tail = tmp->getPrev();
	tmp = Head->getNext();

	for (; Check(tmp, tail);)  //repeat the function, untill check return 0
	{
		Cur1 = Head->getNext();
		Cur2 = Cur1->getNext();

		while (strcmp(Cur1->getInfo(), Cur2->getInfo()) != 1) //if strcmp is not 1, repeat the function
		{ //If Cur 1 is less than Cur 2, repeat continuously.
			Cur1 = Cur1->getNext();
			Cur2 = Cur2->getNext();
		}
		Cur1->getPrev()->setNext(Cur1->getNext());
		Cur2->getNext()->setPrev(Cur2->getPrev());
		Cur1->setNext(Cur2->getNext());
		Cur2->setPrev(Cur1->getPrev());
		Cur1->setPrev(Cur2);
		Cur2->setNext(Cur1);
	}


///////The code below is a code that aligns the head and tail separately.////////
	if (tmp != nameHead)
	{
		tmp = Head;
		for (; 1; tmp = tmp->getNext()) //repeat the funciton untill break
		{
			if (strcmp(Head->getInfo(), tmp->getInfo()) == -1)
				break;
		}

		Head->getNext()->setPrev(NULL);
		sHead = Head->getNext();
		tmp->getPrev()->setNext(Head);
		Head->setPrev(tmp->getPrev());
		tmp->setPrev(Head);
		Head->setNext(tmp);
	}
	
	for (; tail->getNext(); tail = tail->getNext()); //For saving information of end Node
	tmp = tail->getPrev();

	a = 1;
	while (a) //repeat the function, If a is not 0
	{
		if (strcmp(tail->getInfo(), tmp->getInfo()) == 1)
			a = 0;
		tmp = tmp->getPrev();
	}
	tmp = tmp->getNext();

	tail->getPrev()->setNext(NULL);
	tmp->getNext()->setPrev(tail);
	tail->setNext(tmp->getNext());
	tmp->setNext(tail);
	tail->setPrev(tmp);
}

void NameList::Print(DepartmentList &DepartmentList,ofstream&LOGFILE)
{ //Functions for printing
	Node *Dtmp = DepartmentList.mHead;
	Node*tmp = DepartmentList.mHead;

	for (; tmp->getDown(); tmp = tmp->getDown()); //For Descending order
	for (; tmp != Dtmp; tmp = tmp->getUp())
	{
		cout << Dtmp->getInfo() << " / ";
		cout << tmp->getInfo() << " / ";
		cout << tmp->getGrade()->getGradeInfo() << " / ";
		cout << tmp->getID()->getIDInfo() << " / ";
		cout << tmp->getPhone()->getPhoneInfo();
		cout << endl;

		LOGFILE<< Dtmp->getInfo() << " / ";
		LOGFILE << tmp->getInfo() << " / ";
		LOGFILE << tmp->getGrade()->getGradeInfo() << " / ";
		LOGFILE << tmp->getID()->getIDInfo() << " / ";
		LOGFILE << tmp->getPhone()->getPhoneInfo();
		LOGFILE << endl;
	}
	
	for (int a = 1; a;)
	{ //Function for output
		Dtmp = Dtmp->getNext();
		tmp = Dtmp;
		for (; tmp->getDown(); tmp = tmp->getDown());
		for (; tmp != Dtmp; tmp = tmp->getUp())
		{
			cout << Dtmp->getInfo() << " / ";
			cout << tmp->getInfo() << " / ";
			cout << tmp->getGrade()->getGradeInfo() << " / ";
			cout << tmp->getID()->getIDInfo() << " / ";
			cout << tmp->getPhone()->getPhoneInfo();
			cout << endl;

			LOGFILE << Dtmp->getInfo() << " / ";
			LOGFILE << tmp->getInfo() << " / ";
			LOGFILE << tmp->getGrade()->getGradeInfo() << " / ";
			LOGFILE << tmp->getID()->getIDInfo() << " / ";
			LOGFILE << tmp->getPhone()->getPhoneInfo();
			LOGFILE << endl;
		}
		if (tmp == DepartmentList.mtail)
			a = 0; //Shut down when tmp is equal to tail
	}
}

void NameList::addGrade(char * sub_name, char* information,DepartmentList &DepartmentList,GradeList& GradeList)
{//A function that creates and saves the input information to each name node
	Node* tmp = DepartmentList.mHead->getDown();
	Node* Dtmp = DepartmentList.mHead;

	for (; Dtmp; Dtmp = Dtmp->getNext())
	{
		for (tmp = Dtmp->getDown(); tmp; tmp = tmp->getDown())
		{
			if (strcmp(sub_name, tmp->getInfo()) == 0 && tmp->getGrade() == NULL)
			{//Repeat until names match
				GradeNode* newNode = new GradeNode;
				newNode->setGrade(information);
				tmp->setGrade(newNode);
				if (!strcmp(sub_name, nameHead->getInfo()))
					GradeList.GradeHead = newNode;
				return;
			}
		}
	}
}

void NameList::addID(char*sub_name, char*information, DepartmentList &DepartmentList,StudentIDList& IDList)
{//A function that creates and saves the input information to each name node

	Node* tmp = DepartmentList.mHead->getDown();
	Node* Dtmp = DepartmentList.mHead;

	for (; Dtmp; Dtmp = Dtmp->getNext())
	{
		for (tmp = Dtmp->getDown(); tmp; tmp = tmp->getDown())
		{
			if (strcmp(sub_name, tmp->getInfo()) == 0 && tmp->getID() == NULL)
			{//Repeat until names match
				StudentIDNode* newNode = new StudentIDNode;
				newNode->setID(information);
				tmp->setID(newNode);
				if (!strcmp(sub_name, nameHead->getInfo()))
					IDList.IDHead = newNode;
				return;
			}
		}
	}
}

void NameList::addPhone(char*sub_name, char*information, DepartmentList &DepartmentList,ContactList& PhoneList)
{//A function that creates and saves the input information to each name node
	Node* tmp = DepartmentList.mHead->getDown();
	Node* Dtmp = DepartmentList.mHead;


	for (; Dtmp; Dtmp = Dtmp->getNext())
	{
		for (tmp = Dtmp->getDown(); tmp; tmp = tmp->getDown())
		{
			if (strcmp(sub_name, tmp->getInfo()) == 0 && tmp->getPhone() == NULL)
			{//Repeat until names match
				ContactNode* newNode = new ContactNode;
				newNode->setPhone(information);
				tmp->setPhone(newNode);
				if (!strcmp(sub_name, nameHead->getInfo()))
					PhoneList.PhoneHead = newNode;
				return;
			}
		}
	}
}

void NameList::updateGrade(char * sub_name, char* information, DepartmentList &DepartmentList, GradeList& GradeList)
{//Function that clears the original information and puts the updated information
	Node* tmp = DepartmentList.mHead->getDown();
	Node* Dtmp = DepartmentList.mHead;

	for (; Dtmp; Dtmp = Dtmp->getNext())
	{
		for (tmp = Dtmp->getDown(); tmp; tmp = tmp->getDown())
		{
			if (strcmp(sub_name, tmp->getInfo()) == 0)
			{//Repeat until names match
				tmp->getGrade()->setGrade(information);
				return;
			}
		}
	}
}

void NameList::updateID(char*sub_name, char*information, DepartmentList &DepartmentList, StudentIDList& IDList)
{//Function that clears the original information and puts the updated information
	Node* tmp = DepartmentList.mHead->getDown();
	Node* Dtmp = DepartmentList.mHead;

	for (; Dtmp; Dtmp = Dtmp->getNext())
	{
		for (tmp = Dtmp->getDown(); tmp; tmp = tmp->getDown())
		{
			if (strcmp(sub_name, tmp->getInfo()) == 0)
			{//Repeat until names match
				tmp->getID()->setID(information);
				return;
			}
		}
	}
}

void NameList::updatePhone(char*sub_name, char*information, DepartmentList &DepartmentList, ContactList& PhoneList)
{//Function that clears the original information and puts the updated information
	Node* tmp = DepartmentList.mHead->getDown();
	Node* Dtmp = DepartmentList.mHead;


	for (; Dtmp; Dtmp = Dtmp->getNext())
	{
		for (tmp = Dtmp->getDown(); tmp; tmp = tmp->getDown())
		{
			if (strcmp(sub_name, tmp->getInfo()) == 0)
			{//Repeat until names match
				tmp->getPhone()->setPhone(information);
				return;
			}
		}
	}
}

void NameList::Addname(DepartmentList & DepartmentList, char*Dename, char*name)
{ //Functions to add information to the original list
	Node*tmp = DepartmentList.mHead;
	Node*tail = DepartmentList.mtail;
	Node*prev = NULL;

	for (int count = 1; count; tmp = tmp->getNext())
	{ //Find the department with the name you entered
		if (!strcmp(Dename, tmp->getInfo()))
			break;

		else if (tmp == tail)
			count = 0;
	}

	for (tmp = tmp->getDown(); tmp->getDown(); tmp = tmp->getDown())
	{ //A function that inserts the information to be added in order of name
		if (strcmp(name, tmp->getInfo()) == -1)
		{
			NameNode* newNode = new NameNode;
			newNode->Save_name(name);

			newNode->setUp(tmp->getUp());
			newNode->setDown(tmp);
			tmp->getUp()->setDown(newNode);
			tmp->setUp(newNode);
			link_add(newNode);
			ChangeHead(newNode);
			return;
		}
		else if (strcmp(name, tmp->getInfo()) == 1)
			continue;
	}

	if (tmp->getDown() == NULL)
	{ //If getDonw is NULL, practice the function
		if (strcmp(name, tmp->getInfo()) == -1)
		{
			NameNode* newNode = new NameNode;
			newNode->Save_name(name);

			newNode->setUp(tmp->getUp());
			newNode->setDown(tmp);
			tmp->getUp()->setDown(newNode);
			tmp->setUp(newNode);
			link_add(newNode);
			ChangeHead(newNode);
		}
		else
		{ //else
			NameNode* newNode = new NameNode;
			newNode->Save_name(name);

			tmp->setDown(newNode);
			newNode->setUp(tmp);
			newNode->setDown(NULL);
			link_add(newNode);
			ChangeHead(newNode);
		}
	}
}

void NameList::DeleteNode(Node*tmp)
{ //The function to use when clearing a node that has no other information but a name
	if (tmp->getDown() == NULL)
	{ //If getDonw is NULL, practice the function
		tmp->getPrev()->setNext(tmp->getNext());
		tmp->getNext()->setPrev(tmp->getPrev());
		tmp->getUp()->setDown(tmp->getDown());
		tmp = NULL;
		delete tmp;
		return;
	}
	else
	{ //else
		tmp->getPrev()->setNext(tmp->getNext());
		tmp->getNext()->setPrev(tmp->getPrev());
		tmp->getUp()->setDown(tmp->getDown());
		tmp->getDown()->setUp(tmp->getUp());
		tmp = NULL;
		delete tmp;
		return;
	}
}
void NameList::Checksame(char*Savename,char*SavePhone,char*SaveID, ContactList &PhoneList, StudentIDList& IDList)
{ //Function to check whether student number and number are duplicated
	Node*tmp = nameHead;
	StudentIDNode*tmp2 = IDList.IDHead;
	ContactNode*tmp3 = PhoneList.PhoneHead;

	for (; strcmp(tmp->getInfo(), Savename); tmp = tmp->getNext());
	//Repeat until names match

	for (; tmp2; tmp2 = tmp2->getNext())
	{
		if (tmp2 == NULL) //If tmp2 is NULL
			return; //return;
		else if (!strcmp(tmp2->getIDInfo(), SaveID))
		{
			DeleteNode(tmp); //If it is duplicated, delete the node you added again
			cout << "200-1" << endl; //Pritn Error code
		}
	}

	for (;tmp3; tmp3 = tmp3->getNext())
	{
		if (tmp3 == NULL) //If tmp3 is NULL,
			return; //return;
		else if (!strcmp(tmp3->getPhoneInfo(), SavePhone))
		{
			DeleteNode(tmp); //If it is duplicated, delete the node you added again
			cout << "200-1" << endl; //Pritn Error code
		}
	}
}

void NameList::addInfo(DepartmentList&DepartmentList, NameList &NameList, GradeList &GradeList, ContactList &PhoneList, StudentIDList& IDList,int&number)
{ //A function to add additional student information to the node
	char information[100] = { NULL };
	char SaveDe[100] = { NULL };
	char Savename[100] = { NULL };

	char SaveID[100] = { NULL };
	char SavePhone[100] = { NULL };


	ifstream Addcommand("Add_information.txt"); //Load information to add

	if (!Addcommand.is_open())
	{ //If the file does not open, run it
		cout << "200" << endl; //Print error code
		number = 0;
		return;
	}

	for (int count = 1; Addcommand >> information; count++)
	{ //Enter information into a function that functions to add and receive information sequentially
		if (count == 1)
		{
			strcpy(SaveDe, information);
		}
		else if (count == 2)
		{
			Addname(DepartmentList, SaveDe, information);
			strcpy(Savename, information);
		}
		else if (count == 3)
		{
			addGrade(Savename, information, DepartmentList, GradeList);
		}
		else if (count == 4)
		{
			addID(Savename, information, DepartmentList, IDList);
			strcpy(SaveID, information);
		}
		else if (count == 5)
		{
			addPhone(Savename, information, DepartmentList, PhoneList);
			strcpy(SavePhone,information);
			Checksame(Savename,SavePhone,SaveID,PhoneList,IDList);
			count = 0;
		}
	}
	Addcommand.close(); //Close the file
}

void NameList::link_add(NameNode*newNode)
{ //A function that connects the newly added node with the existing nodes through add function
	Node*tmp = nameHead;

	for (; tmp; tmp = tmp->getNext())
	{
		if (strcmp(tmp->getInfo(), newNode->getInfo()) == 1)
		{ //if tmp's information is bigger than newNode's information
			if (tmp == nameHead)
			{
				newNode->setNext(tmp);
				tmp->setPrev(newNode);
				newNode->setPrev(NULL);
				return;
			}
			else
			{
				newNode->setNext(tmp);
				newNode->setPrev(tmp->getPrev());
				tmp->getPrev()->setNext(newNode);
				tmp->setPrev(newNode);
				return;
			}
		}

		if (strcmp(tmp->getInfo(), newNode->getInfo()) == -1)
		{ //if tmp's information is smaller than newNode's information
			if (tmp->getNext() == NULL)
			{
				newNode->setNext(NULL);
				tmp->setNext(newNode);
				newNode->setPrev(tmp);
			}
			continue;
		}
	}
}

void NameList::Checkde(DepartmentList & DepartmentList)
{ //The function to check the students of the department and erase the department without students
	Node*tmp = DepartmentList.mHead;
	Node*Prev = tmp;

	for (int a = 1; a; tmp = tmp->getNext())
	{
		if (tmp->getDown() == NULL) //If List does not have a student
		{
			if (tmp == DepartmentList.mHead || tmp == DepartmentList.mtail)
			{
				if (tmp == DepartmentList.mHead)
				{
					Node*tmp2 = DepartmentList.mHead->getNext();
					DepartmentNode*newNode = new DepartmentNode;

					//Head moving algorithm
					newNode->Save_de(tmp2->getInfo());
					newNode->setNext(tmp2->getNext());
					newNode->setDown(tmp2->getDown());
					tmp2->getDown()->setUp(newNode);
					DepartmentList.mHead->setNext(newNode);
					DepartmentList.mHead = newNode;
					delete tmp2;
				}

				else
				{ //When the tail of the department disappears
					Node*tmp2 = tmp->getNext();
					Node*tmp3 = tmp->getNext();
					for (; tmp2->getNext() != DepartmentList.mtail; tmp2 = tmp2->getNext());
					for (; tmp3->getNext() != tmp2; tmp3 = tmp3->getNext());
					DepartmentNode*newNode = new DepartmentNode;

					//Algorithm to move tail
					newNode->Save_de(tmp2->getInfo());
					newNode->setNext(tmp2->getNext());
					newNode->setDown(tmp2->getDown());
					tmp2->getDown()->setUp(newNode);
					tmp3->setNext(newNode);
					DepartmentList.mtail = newNode;
					delete tmp2;
				}
			}
			for (; Prev->getNext() != tmp; Prev = Prev->getNext());
			Prev->setNext(tmp->getNext());
			delete tmp; //delete department
			return;
		}

		if (tmp == DepartmentList.mtail)
			a = 0;
	}
}

void NameList::UpdateInfo(DepartmentList & DepartmentList, char*Dename, char*name)
{ //A function that finds the student to update and replaces the existing information
	Node*tmp = DepartmentList.mHead;
	Node*Check = NULL;
	Node*ncompare = NULL;
	Node*ntmp = nameHead;

	while (strcmp(ntmp->getInfo(), name)) //Functions to Find Names
		ntmp = ntmp->getNext();

	while (strcmp(tmp->getInfo(), Dename)) //Function to find department
		tmp = tmp->getNext();

	Check = ntmp;
	while (Check->getUp()) //repeat the function, If getup() is not NULL
		Check = Check->getUp();

	if (!strcmp(Dename,Check->getInfo()))
		return;

	ntmp->getUp()->setDown(ntmp->getDown());

	if (ntmp->getDown() == NULL)
	{}//A safety statement
	else if(ntmp->getDown() != NULL)
		ntmp->getDown()->setUp(ntmp->getUp());

	ncompare = tmp->getDown();

	for (; ncompare; ncompare = ncompare->getDown())
	{ //repeat the function, If ncompare is not NULL
		if (strcmp(ntmp->getInfo(), ncompare->getInfo()) == -1)
		{
			ntmp->setUp(ncompare->getUp());
			ntmp->setDown(ncompare);
			ncompare->getUp()->setDown(ntmp);
			ncompare->setUp(ntmp);
			break;
		}
		else if (strcmp(ntmp->getInfo(), ncompare->getInfo()) != -1)
			continue;
	}

	if (ncompare == NULL) //If ncompare is NULL, practice the function
	{
		for (; tmp->getDown(); tmp = tmp->getDown()); //repeat the function, If getDown() is not NULL

		ntmp->setUp(tmp);
		ntmp->setDown(NULL);
		tmp->setDown(ntmp);
	}
	Checkde(DepartmentList); //Delete any overlapping subjects
}

bool NameList::checkUp(char*Savename, char*SaveID, char*SavePhone, StudentIDList&IDList, ContactList&PhoneList)
{
	Node*tmp = nameHead;
	ContactNode*tmp3 = PhoneList.PhoneHead;
	StudentIDNode*tmp2 = IDList.IDHead;

	for (; tmp; tmp = tmp->getNext()) //repeat the function, if tmp is not NULL
		if (!strcmp(tmp->getInfo(), Savename)) //Run if same information
			break;

	for (; tmp3; tmp3 = tmp3->getNext()) //repeat the function, if tmp3 is not NULL
	{
		if (!strcmp(tmp->getPhone()->getPhoneInfo(), tmp3->getPhoneInfo())) //Run if same information
			continue;

		if (!strcmp(tmp3->getPhoneInfo(), SavePhone)) //Run if same information
		{
			return 0; //return 0
		}
	}

	for (; tmp2; tmp2 = tmp2->getNext()) //repeat the function, if tmp2 is not NULL
	{
		if (!strcmp(tmp->getID()->getIDInfo(), tmp2->getIDInfo())) //Run if same information
			continue;

		if (!strcmp(tmp2->getIDInfo(), SaveID)) //Run if same information
		{
			return 0;
		}
	}
	return 1; //else , return 1
}

void NameList::Update(DepartmentList&DepartmentList, NameList &NameList, GradeList &GradeList, ContactList &PhoneList, StudentIDList& IDList,ofstream&LOGFILE)
{ //A function that finds the student to update and replaces the existing information
	char information[100] = { NULL };
	char SaveDe[100] = { NULL };
	char Savename[100] = { NULL };

	char SavePhone[100] = { NULL };
	char SaveID[100] = { NULL };

	int checking1 = 0;
	int checking2 = 0;

	int ex = 0;

	ifstream Updatecommand("Update_information.txt"); //Get information to update

	if (!Updatecommand.is_open()) //If the file does not open, run it
	{
		cout << "300" << endl; //Print error code
		LOGFILE << "300" << endl;
		return;
	}

	for (int count = 1; Updatecommand >> information; count++) //Run until all files are read
	{
		if (count == 1)
		{
			strcpy(SaveDe, information);
		}
		else if (count == 2)
		{
			Node*tmp = DepartmentList.mHead;
			Node*ntmp = nameHead;

			for (; ntmp; ntmp = ntmp->getNext()) //Repeat the function, if ntmp is not NULL
			{
				if (!strcmp(ntmp->getInfo(), information)) //Run if same information
					break;
			}
			strcpy(Savename, information);

			if (ntmp == NULL) //If ntmp is NULL
			{
				cout << "300-2" << endl; //Print error code
				LOGFILE << "300-2" << endl;
				ex = 1;
			}
			else
			{
				UpdateInfo(DepartmentList, SaveDe, Savename);
			}
		}
		else if (count == 3)
		{
			if (ex == 1)
			{ //Function to do nothing
			}
			else
			{
				updateGrade(Savename, information, DepartmentList, GradeList);
			}
		}
		else if (count == 4)
		{
			if (ex == 1)
			{ //Function to do nothing
			}
			else
			{
				strcpy(SaveID, information); //Save information to SaveID
				if (checkUp(Savename, SaveID, SavePhone, IDList, PhoneList))
				{
					updateID(Savename, information, DepartmentList, IDList);
				}
				else
					checking2 = 1;
			}
		}
		else if (count == 5)
		{
			if (ex == 1)
			{
				ex = 0;
			}
			else
			{
				strcpy(SavePhone, information); //Save information to SavePhone
				if (checkUp(Savename, SaveID, SavePhone, IDList, PhoneList))
				{
					updatePhone(Savename, information, DepartmentList, PhoneList);
				}
				else
					checking1 = 1;
			}
			if (checking1 == 1 && checking2 == 1)
			{
				cout << "300-1" << endl;
				LOGFILE << "300-1" << endl;
				checking1 = 0;
				checking2 = 0;
			}
			count = 0;
		}
	}
	Updatecommand.close(); //Functions to close open files
}

void NameList::Find(char*a,int count,ofstream&LOGFILE)
{ //A function that allows you to find a matching first name or last name
	Node*tmp = nameHead;
	char name[100] = { NULL };
	int check = 1;

	for (; tmp; tmp = tmp->getNext()) //Repeat the function, If tmp is not NULL
	{
		strncpy(name, tmp->getInfo(), count);
		if (!strncmp(a, name, count))
		{
			PrintDe(tmp,LOGFILE);
			cout << tmp->getInfo() << " / ";
			cout << tmp->getGrade()->getGradeInfo() << " / ";
			cout << tmp->getID()->getIDInfo() << " / ";
			cout << tmp->getPhone()->getPhoneInfo();
			cout << endl;

			LOGFILE<< tmp->getInfo() << " / ";
			LOGFILE << tmp->getGrade()->getGradeInfo() << " / ";
			LOGFILE << tmp->getID()->getIDInfo() << " / ";
			LOGFILE << tmp->getPhone()->getPhoneInfo();
			LOGFILE << endl;
			check = 0;
		}
	}
	if (tmp == NULL&&check == 1)
	{ //If there is no name, print error code
		cout << endl << "900" << endl;
		LOGFILE << "900" << endl;
	}
}

void NameList::Print_De(char*information,DepartmentList&DepartmentList,ofstream&LOGFIEL)
{ //Function that outputs connected department according to condition
	Node*tmp = DepartmentList.mHead;

	for (; (strcmp(tmp->getInfo(), information)); tmp = tmp->getNext());
	//Repeat until information is matched
	for (; tmp->getDown(); tmp = tmp->getDown());

	for (; tmp->getUp() != NULL; tmp = tmp->getUp())
	{
		PrintDe(tmp,LOGFIEL);
		cout << tmp->getInfo() << " / ";
		cout << tmp->getGrade()->getGradeInfo() << " / ";
		cout << tmp->getID()->getIDInfo() << " / ";
		cout << tmp->getPhone()->getPhoneInfo();
		cout << endl;

		LOGFIEL<< tmp->getInfo() << " / ";
		LOGFIEL << tmp->getGrade()->getGradeInfo() << " / ";
		LOGFIEL << tmp->getID()->getIDInfo() << " / ";
		LOGFIEL << tmp->getPhone()->getPhoneInfo();
		LOGFIEL << endl;
	}
}

void NameList::Insertionsorting(char* information, Node*tmp)
{//Functions that perform insert sorting
	if (IDHead == NULL)
	{ //Function to create a new node when there is nothing in the list
		NameNode* newNode = new NameNode;

		linknewNode(newNode);

		addnewNode(newNode, tmp);

		newNode->setNext(NULL);
		newNode->setPrev(NULL);

		IDHead = newNode;
		return;
	}

	else
	{ //If there is any information in the list
		Node *tmp2 = IDHead;
		Node *prev = IDHead;

		for (; tmp2; tmp2 = tmp2->getNext())
		{
			if (strcmp(tmp2->getID()->getIDInfo(), information) == 1)
			{ //Compare sizes and make them fit in the correct position
				if (tmp2 == IDHead)
				{
					NameNode* newNode = new NameNode;

					linknewNode(newNode);

					addnewNode(newNode, tmp);

					newNode->getID()->setID(information);
					newNode->setNext(tmp2);
					IDHead = newNode;
					return;
				}
				else
				{
					for (; prev->getNext() != tmp2; prev = prev->getNext());

					NameNode* newNode = new NameNode;

					linknewNode(newNode);

					addnewNode(newNode, tmp);
					newNode->getID()->setID(information);
					prev->setNext(newNode);
					newNode->setNext(tmp2);
					return;
				}
			}
			else
				continue;
		}
		if (tmp2 == NULL)
		{ //Node is created on the tail
			for (; prev->getNext() != tmp2; prev = prev->getNext());

			NameNode* newNode = new NameNode;

			linknewNode(newNode);

			addnewNode(newNode, tmp);

			prev->setNext(newNode);
			newNode->setNext(NULL);
			return;
		}
	}
}

void NameList::DeleteList(Node*tmp)
{ //A function that deletes the list if any lease is assigned
	Node*bye = tmp;

	for (;tmp;)
	{ //Repeat to remove all nodes
		delete tmp->getGrade();
		delete tmp->getID();
		delete tmp->getPhone();

		bye = tmp;
		tmp = tmp->getNext();
		bye = NULL;
		delete bye;
	}
	return;
}


void NameList::PrintID(ofstream&LOGFILE)
{ //Function to print the linked list in order of the IDs matching the condition
	Node*tmp = nameHead;

	for (; tmp; tmp = tmp->getNext()) //A function that provides sequential communication of the list of subjects
		Insertionsorting(tmp->getID()->getIDInfo(),tmp);

	tmp = IDHead;

	int a = 1;

	for (; tmp; tmp = tmp->getNext(), a++)
	{
		PrintDe(tmp,LOGFILE);
		cout << tmp->getInfo() << " / ";
		cout << tmp->getGrade()->getGradeInfo() << " / ";
		cout << tmp->getID()->getIDInfo() << " / ";
		cout << tmp->getPhone()->getPhoneInfo();
		cout << a;
		cout << endl;

		LOGFILE << tmp->getInfo() << " / ";
		LOGFILE << tmp->getGrade()->getGradeInfo() << " / ";
		LOGFILE << tmp->getID()->getIDInfo() << " / ";
		LOGFILE << tmp->getPhone()->getPhoneInfo();
		LOGFILE << endl;
	}
}

void NameList::PrintDe(Node*tmp,ofstream&LOGFIEL)
{ //Function that prints department
	for (; tmp->getUp(); tmp = tmp->getUp());
	cout << tmp->getInfo() << " / ";
	LOGFIEL << tmp->getInfo() << " / ";
}

void NameList::Printname(ofstream&LOGFILE)
{ //Simple print function
	Node* tmp = nameHead;

	int a = 1;
	for (; tmp; tmp = tmp->getNext(),a++)
	{
		PrintDe(tmp,LOGFILE);
		cout << tmp->getInfo() <<" / ";
		cout << tmp->getGrade()->getGradeInfo()<<" / ";
		cout << tmp->getID()->getIDInfo() << " / ";
		cout << tmp->getPhone()->getPhoneInfo();
		cout << a;
		cout << endl;

		LOGFILE<< tmp->getInfo() << " / ";
		LOGFILE << tmp->getGrade()->getGradeInfo() << " / ";
		LOGFILE << tmp->getID()->getIDInfo() << " / ";
		LOGFILE << tmp->getPhone()->getPhoneInfo();
		LOGFILE << endl;
	}
	return;
}

void NameList::linknewNode(NameNode*newNode)
{ //Function to connect new node
	GradeNode * GnewNode = new GradeNode;
	StudentIDNode*IDnewNode = new StudentIDNode;
	ContactNode* CnewNode = new ContactNode;

	newNode->setGrade(GnewNode);
	newNode->setID(IDnewNode);
	newNode->setPhone(CnewNode);
}

void NameList::addnewNode(NameNode*newNode,Node*tmp)
{ //Functions for storing information in new nodes
	newNode->Save_name(tmp->getInfo());
	newNode->getGrade()->setGrade(tmp->getGrade()->getGradeInfo());
	newNode->getID()->setID(tmp->getID()->getIDInfo());
	newNode->getPhone()->setPhone(tmp->getPhone()->getPhoneInfo());
	newNode->setUp(tmp->getUp());
	newNode->setDown(tmp->getDown());
}

void NameList::createPhoneList(Node*tmp)
{ //A function that creates a new sorted list using sorting that matches the task conditions
	if (PhoneHead == NULL)
	{ //When a node is first created
		NameNode*newNode = new NameNode;
		linknewNode(newNode);
		addnewNode(newNode, tmp);
		PhoneHead = newNode;
		return;
	}
	else
	{
		Node*end = PhoneHead;
		for (; end->getNext(); end = end->getNext());

		NameNode*newNode = new NameNode;
		linknewNode(newNode);
		addnewNode(newNode, tmp);

		end->setNext(newNode);
		return;
	}
}

void NameList::PrintPhone(ofstream&LOGFILE)
{ //Functions that sort by condition and sort by number
	Node*tmp = nameHead;
	Node*tmp2 = NULL;
	Node*most = nameHead;
	Node*smallest = nameHead;

	for (; tmp; tmp = tmp->getNext()) 
	{
		if (strcmp(tmp->getPhone()->getPhoneInfo(), most->getPhone()->getPhoneInfo()) == 1)
			most = tmp; //Find the largest value
		if (strcmp(tmp->getPhone()->getPhoneInfo(), smallest->getPhone()->getPhoneInfo()) == -1)
			smallest = tmp; //Find the smallest value
	}
	createPhoneList(most); //A command to create a new sorted list

	Node*nextmax = nameHead; //Declaration to store the node with the next larger value

	for (int a=1; most != smallest;a++)
	{ //A loop that finds the next big value and makes a list
		for (tmp2 = nameHead; tmp2; tmp2 = tmp2->getNext())
		{
			if (strcmp(nextmax->getPhone()->getPhoneInfo(), most->getPhone()->getPhoneInfo()) == 0 ||
				strcmp(nextmax->getPhone()->getPhoneInfo(), most->getPhone()->getPhoneInfo()) == 1)
				nextmax = nextmax->getNext();

			if (strcmp(tmp2->getPhone()->getPhoneInfo(), most->getPhone()->getPhoneInfo()) == 1 ||
				strcmp(tmp2->getPhone()->getPhoneInfo(), most->getPhone()->getPhoneInfo()) == 0)
				continue;

			if (strcmp(tmp2->getPhone()->getPhoneInfo(), most->getPhone()->getPhoneInfo()) == -1 &&
				strcmp(nextmax->getPhone()->getPhoneInfo(), tmp2->getPhone()->getPhoneInfo()) == -1)
				nextmax = tmp2;
		}
		most = nextmax;
		nextmax = nameHead;
		createPhoneList(most);
	}

	tmp = PhoneHead; //Initialize for printing

	int a = 1;
	for (; tmp; tmp = tmp->getNext(), a++)
	{
		PrintDe(tmp,LOGFILE);
		cout << tmp->getInfo() << " / ";
		cout << tmp->getGrade()->getGradeInfo() << " / ";
		cout << tmp->getID()->getIDInfo() << " / ";
		cout << tmp->getPhone()->getPhoneInfo();
		cout << a;
		cout << endl;


		LOGFILE<< tmp->getInfo() << " / ";
		LOGFILE << tmp->getGrade()->getGradeInfo() << " / ";
		LOGFILE << tmp->getID()->getIDInfo() << " / ";
		LOGFILE << tmp->getPhone()->getPhoneInfo();
		LOGFILE << endl;
	}
	return;
}
