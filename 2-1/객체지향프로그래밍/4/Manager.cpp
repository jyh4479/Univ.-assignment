#include "Manager.h"

using namespace std;

static int number = 0; //The number for checking

Manager::Manager()
{
}

Manager::~Manager()
{
}

bool Manager::checksame(char*a, DepartmentList&DepartmentList)
{ //Function checking for overlapping
	Node*tmp = DepartmentList.mHead;
	Node*tail = DepartmentList.mtail;

	for (; tmp != tail;) //Repeat the function, If tmp is not tail
	{
		if (!strcmp(tmp->getInfo(), a)) //Return 0 if same information
			return 0;
		
		tmp = tmp->getNext();
	}
	
	if (!strcmp(a , tail->getInfo()))
		return 0;
	else 
		return 1; //else, return 1
}

bool Manager::checkempty(DepartmentList&DepartmentList)
{
	if (DepartmentList.mHead == NULL) //Function to check if list is empty
		return 1;
	else
		return 0;
}

bool Manager::checkempty2(NameList&NameList) 
{
	if (NameList.nameHead == NULL) //Function to check if list is empty
		return 1;
	else
		return 0;
}

/*void Manager::DeleteData(DepartmentList &DepartmentList, NameList &NameList, GradeList &GradeList, ContactList &PhoneList, StudentIDList& IDList)
{
	Node* tmp = NameList.nameHead;
	Node*Dtmp = DepartmentList.mHead;
	Node*Dtail = DepartmentList.mtail;
	Node*bye = NULL;

	for (; tmp->getNext(); tmp = tmp->getNext());

	for (; tmp;)
	{
		delete tmp->getGrade();
		delete tmp->getID();
		delete tmp->getPhone();

		bye = tmp;
		tmp = tmp->getPrev();

		delete bye;
		bye = NULL;
	}
	
	for (; Dtmp != Dtail;)
	{
		bye = Dtmp;
		Dtmp = Dtmp->getNext();

		delete bye;
		bye = NULL;
	}
	
	delete Dtail;
	return;
}*/

void Manager::DeleteHead(NameList &NameList)
{ //Function that removes all name lists
	Node*tmp = NameList.nameHead;
	Node*bye = NameList.nameHead;

	for (; tmp;) //Repeat until list ends
	{
		delete tmp->getGrade();
		delete tmp->getID();
		delete tmp->getPhone();

		bye = tmp;

		tmp = tmp->getNext();

		delete bye;
		bye = NULL;
	}
	NameList.nameHead = NULL; //Save NULL to nameHead
}

void Manager::DeleteDe(DepartmentList& DepartmentList)
{ //Function that removes all department lists
	Node *tmp = DepartmentList.mHead;
	Node *tail = DepartmentList.mtail;
	Node *bye = DepartmentList.mHead;

	for (; tmp!=tail;) //Repeat until list ends
	{
		bye = tmp;

		tmp = tmp->getNext();

		delete bye;
		bye = NULL;
	}
	delete tmp;
	tmp = NULL;
	DepartmentList.mHead=NULL; //Save NULL to Head
	DepartmentList.mtail = NULL; //Save NULL to tail
}

void Manager::DeleteIDHead(NameList& NameList)
{ //Function that clears ID list
	Node*tmp = NameList.IDHead;
	Node*bye = NameList.IDHead;

	for (; tmp;) //Repeat until list ends
	{
		delete tmp->getGrade();
		delete tmp->getID();
		delete tmp->getPhone();

		bye = tmp;

		tmp = tmp->getNext();

		delete bye;

		bye = NULL;
	}
	NameList.IDHead = NULL; //Save NULL to Head
}

void Manager::DeletePhoneHead(NameList& NameList)
{ //Function that clears Contact list
	Node*tmp = NameList.PhoneHead;
	Node*bye = NameList.PhoneHead;

	for (; tmp;) //Repeat until list ends
	{
		delete tmp->getGrade();
		delete tmp->getID();
		delete tmp->getPhone();

		bye = tmp;

		tmp = tmp->getNext();

		delete bye;

		bye = NULL; 
	}
	NameList.PhoneHead = NULL; //Save NULL to Head
}

void Manager::Check(char *Command,DepartmentList &DepartmentList,NameList &NameList, GradeList &GradeList, ContactList &PhoneList, StudentIDList& IDList,ofstream& LOGFILE)
{ //A function that manages all actions
	if (!strcmp(Command, "LOAD"))
	{
		cout << "[LOAD]" << endl;
		LOGFILE << "[LOAD]" << endl << endl;
		Load(DepartmentList,NameList,GradeList,PhoneList,IDList,LOGFILE);
		//A function that connects departments and receives name information to create a node.
		NameList.link_na(DepartmentList);//Function that connects created name nodes
		NameList.sorting();//A function to arrange associated name nodes alphabetically.
		GradeList.link_gr(DepartmentList); //Function that connects school year nodes
		IDList.link_id(DepartmentList); //Function that connects the number of class node
		PhoneList.link_Ph(DepartmentList); //Function that connects telephone number nodes
		DepartmentList.linktail();//A function that connects the list of departments in a circular form.

		cout << "Success" << endl;
		LOGFILE << "Success" << endl;
	}
	else if (!strcmp(Command, "ADD")) //A function for reading commands
	{
		int number = 1;
		cout << "[ADD]" << endl;
		LOGFILE <<endl<< "[ADD]" <<endl <<endl;

		if (NameList.nameHead == NULL)
		{ //If there is no list
			cout << "Make a basic list" << endl;
			LOGFILE << "Make a basic list" << endl;
			return;
		}

		NameList.addInfo(DepartmentList, NameList, GradeList, PhoneList, IDList, number); //Function that adds new incoming information
		GradeList.link_gr(DepartmentList); //Function that connects school year nodes
		IDList.link_id(DepartmentList); //Function that connects the number of class node
		PhoneList.link_Ph(DepartmentList); //Function that connects telephone number nodes

		if (number)
		{
			cout << "Success" << endl;
			LOGFILE << "Success" << endl;
			number = 1;
		}
	}

	else if (!strncmp(Command, "PRINT",5)) //A function for reading commands
	{
		char a[100] = { NULL };
		char b[100] = { NULL };
		if (Command[5]==NULL)
		{
			cout << "[PRINT]" << endl;
			LOGFILE << endl << "[PRINT]" << endl << endl;
			if (checkempty(DepartmentList))
			{ //Execute if list is empty
				cout << "600-1" << endl;
				LOGFILE << "600-1" << endl;
				return;
			}
			NameList.Print(DepartmentList,LOGFILE);
		}
		else if (Command[5] !=NULL&&Command[5] != '_') //A function for reading commands
		{ //A function to check parameters
			for (int count = 6; Command[count]; count++)
			{
				a[count - 6] = Command[count];
			}
			cout << "[PRINT" << " " << a <<"]"<< endl;
			LOGFILE << endl<<"[PRINT" << " " << a << "]" << endl <<endl;
			if (checksame(a, DepartmentList))
			{ //Function that identifies duplicate studies
				cout << "600-2" << endl;
				LOGFILE << "600-2" << endl;
				return;
			}
			NameList.Print_De(a,DepartmentList,LOGFILE); //Function to print list
		}
		else if (!strcmp(Command, "PRINT_STUDENT_ID")) //A function for reading commands
		{
			cout << "PRINT_SUTDENT_ID" << endl;
			LOGFILE <<endl <<"PRINT_SUTDENT_ID" << endl << endl;
			if (checkempty2(NameList))
			{ //Execute if list is empty
				cout << "700" << endl;
				LOGFILE << "700" << endl;
				return;
			}
			NameList.PrintID(LOGFILE); //Function to print list
			DeleteIDHead(NameList); //Function that deletes list after output
		}
		else if (!strcmp(Command, "PRINT_CONTACT")) //A function for reading commands
		{
			cout << "PRINT_CONTACT" << endl;
			LOGFILE << endl << "PRINT_CONTACT" << endl << endl;
			if (checkempty2(NameList))
			{ //Execute if list is empty
				cout << "800" << endl;
				LOGFILE << "800" << endl;
				return;
			}
			NameList.PrintPhone(LOGFILE); //Function to print list
			DeletePhoneHead(NameList); //Function that deletes list after output
		}
	}
	else if(!strncmp(Command, "MODIFY_DEPARTMENT",17)) //A function for reading commands
	{
		char a[100] = { NULL }; //Variables to store parameters before
		char b[100] = { NULL }; //Variables to store parameters after
		int count = 18;
		for (; Command[count]!=' '; count++)
			a[count - 18] = Command[count]; //The first department to be entered

		int count2 = count;

		for (; Command[count2]; count2++)
			b[count2-count] = Command[count2+1]; //The second department to be entered

		cout << "MODIFY_DEPARTMENT" << " " << a << " " << b << endl << endl;
		LOGFILE << endl << "MODIFY_DEPARTMENT" << " " << a << " " << b << endl << endl;

		if (checksame(a, DepartmentList))
		{ //Execute if list is empty
			cout << "400" << endl;
			LOGFILE << "400" << endl;
			return;
		}

		cout << "Success" << endl;
		LOGFILE << "Success" << endl;
		DepartmentList.Modify(a, b,LOGFILE); //A function that renames a department
	}
	else if (!strcmp(Command, "UPDATE")) //A function for reading commands
	{
		cout << "[UPDATE]" << endl;
		LOGFILE << endl << "[UPDATE]" << endl << endl;

		if (NameList.nameHead == NULL)
		{ //If there is no list
			cout << "Make a basic list" << endl;
			LOGFILE << "Make a basic list" << endl;
			return;
		}

		NameList.Update(DepartmentList, NameList, GradeList, PhoneList, IDList,LOGFILE); //Functions that enable updates to the list
		GradeList.link_gr(DepartmentList);//Function that connects school year nodes
		IDList.link_id(DepartmentList); //Function that connects the number of class node
		PhoneList.link_Ph(DepartmentList); //Function that connects telephone number nodes
	}

	else if (!strncmp(Command,"DELETE_DEPARTMENT",17)) //A function for reading commands
	{
		char a[100] = { NULL };
		int count = 18;
		for (; Command[count]; count++)
			a[count - 18] = Command[count]; //A course entered by parameters

		cout << "DELETE_DEPARTMENT" << " " << a << endl;
		LOGFILE << endl << "DELETE_DEPARTMENT" << " " << a << endl << endl;

		if (checksame(a, DepartmentList))
		{ //Function to check if list is empty
			cout << "500" << endl;
			LOGFILE << "500" << endl;
			return;
		}
		cout << "Success" << endl;
		LOGFILE << "Success" << endl;
		DepartmentList.Delete(a); //A function for deleting a subject
	}
	else if (!strncmp(Command, "FIND_NAME", 9)) //A function for reading commands
	{
		char a[100] = { NULL };
		int count = 10;
		for (; Command[count]; count++)
			a[count - 10] = Command[count];

		cout << "FIND_NAME" << " " << a << endl;
		LOGFILE << endl << "FIND_NAME" << " " << a << endl << endl;
		NameList.Find(a,count-10,LOGFILE);
	}
	else if (!strncmp(Command, "SAVE", 4)) //A function for reading commands
	{
		char a[100] = { NULL }; //Variables that save parameters
		char b[100] = { NULL };

		int count = 0;
		int number = 0;

		cout << endl << "[Save]" << endl << endl;
		LOGFILE << endl << "[Save]" << endl << endl;

		if (Command[4] == NULL||(Command[4]==' '&&Command[5]==NULL))
		{ //Output if no parameter is found in the txt command
			cout << "1000" << endl;
			LOGFILE << "1000" << endl;
			return;
		}

		if (DepartmentList.mHead == NULL)
		{ //If the list is empty
			cout << "There is no list" << endl;
			LOGFILE << "There is no list" << endl;
			return;
		}

		for (; Command[count]; count++)
		{ //Save Parameters
			a[count] = Command[count + 5];
		}

		DepartmentList.Savetxt(a); //Function that enables Save

		cout << a << " " << "Success" << endl;
		LOGFILE << a << " " << "Success" << endl;
	}
	else if (!strcmp(Command, "EXIT")) //A function for reading commands
	{
		DeleteDe(DepartmentList); //A function to erase a list of departments
		DeleteHead(NameList); //Function that clears name list
		_CrtDumpMemoryLeaks(); //A function that checks the memory that is not erased.

		cout << endl << "[Exit]" << endl;
		LOGFILE << endl << "[Exit]" << endl;
		exit(0); //Program end function
	}
	else
	{ //Output if command from txt is not applicable
		LOGFILE << endl << "000" << endl;
		cout << endl <<  "000" << endl;
	}
}

void Manager::Load(DepartmentList &DepartmentList,NameList &NameList, GradeList &GradeList, ContactList &PhoneList, StudentIDList& IDList,ofstream& LOGFILE)
{ //A function that creates a default list to receive the initial information and perform the command.
	char information[100]; //Variables to receive information
	char sub_information[100]; //Variables to store information for comparison
	char sub_name[100]; //Variables to store information for comparison
	ifstream Loadinformation("Information.txt"); //Open information file to import

	if (!Loadinformation.is_open())
	{ //Output if file does not exist or open
		cout << "100" << endl;
		LOGFILE << "100" << endl;
		exit(0); //Exit Program
	}

	for (int count = 1; Loadinformation>>information; count++)
	{ //Function that is executed by comparing with information sequentially
		if (count == 1)
		{
			DepartmentList.insert_de(information); //Department Node Generation Functions
			strcpy(sub_information, information);
		}
		else if (count == 2)
		{
			NameList.insert_na(sub_information, information, DepartmentList); //Name node creation function
			strcpy(sub_name, information);
		}
		else if (count == 3)
		{
			NameList.addGrade(sub_name, information,DepartmentList,GradeList);
			//Function that adds an information node to the name
		}
		else if (count == 4)
		{
			NameList.addID(sub_name, information, DepartmentList,IDList);
			//Function that adds an information node to the name
		}
		else if (count == 5)
		{
			NameList.addPhone(sub_name, information, DepartmentList,PhoneList);
			//Function that adds an information node to the name
			count = 0;
		}
	}
	Loadinformation.close(); //Function that closes information file
}

