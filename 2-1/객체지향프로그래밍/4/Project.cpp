#include<iostream>
#include<fstream>
#include"Manager.h"
#include"DepartmentList.h"
#include"NameList.h"
#include"ContactList.h"
#include"GradeList.h"
#include"StudentIDList.h"
#include<crtdbg.h>

static ofstream LOGFILE("LOG.txt");

using namespace std;

void LoadFile(DepartmentList &DepartmentList,NameList &NameList,Manager &Manager, GradeList &GradeList,ContactList &PhoneList,StudentIDList& IDList, char* Filename)
{
	ifstream Loadcommand;

	Loadcommand.open(Filename); //Opne Command File

	char command[50]; //Variables to save commands

	while (Loadcommand.getline(command, sizeof(command)))
	{ //Function that delivers commands sequentially
		Manager.Check(command, DepartmentList, NameList, GradeList, PhoneList, IDList,LOGFILE);
		//A function that oversees all actions
	}
	Loadcommand.close(); //Close Command File
}
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//Declaration to capture unused memory
	Manager Manager;
	DepartmentList DepartmentList; //Declare the list of departments to be used
	NameList NameList; //Declare name lists to be used
	ContactList PhoneList; //Declare list of numbers to be used
	GradeList GradeList; //Declare the list of school grades to be used
	StudentIDList IDList; //Declare list of students ID to use
	
	LoadFile(DepartmentList, NameList, Manager, GradeList, PhoneList, IDList, "Command.txt");
	//Function that will perform information and commands
	LOGFILE.close();
	//Close the file that is responsible for the output
	return 0;
}