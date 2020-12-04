#pragma once
#include<fstream>
#include"DepartmentList.h"
#include"NameList.h"
#include"ContactList.h"
#include"StudentIDList.h"
#include"GradeList.h"
#include<iostream>
#include<string.h>

class Manager
{
public:
	Manager();
	~Manager();

	bool checksame(char * a, DepartmentList & DepartmentList);

	bool checkempty(DepartmentList & DepartmentList);

	bool checkempty2(NameList & NameList);

	void DeleteHead(NameList & NameList);
	void DeleteDe(DepartmentList & DepartmentList);
	void DeleteIDHead(NameList & NameList);
	void DeletePhoneHead(NameList & NameList);

	void Check(char * Command, DepartmentList & DepartmentList, NameList & NameList, GradeList & GradeList, ContactList & PhoneList, StudentIDList & IDList, ofstream & LOGFILE);
	void Load(DepartmentList & DepartmentList, NameList & NameList, GradeList & GradeList, ContactList & PhoneList, StudentIDList & IDList, ofstream & LOGFIEL);
	void Print(DepartmentList & DepartmentList, NameList & NameList);
};



