#pragma once

#include"NameNode.h"
#include"DepartmentList.h"
#include"ContactList.h"
#include"GradeList.h"
#include"StudentIDList.h"
#include<fstream>
#include<iostream>

using namespace std;

class NameList
{
public:
	NameList();
	~NameList();

	void ChangeHead(NameNode * newNode);

	void insert_na(char * department, char * name, DepartmentList & DepartmentList);

	void link_na(DepartmentList & DepartmentList);

	bool Check(Node * tmp, Node * tail);

	void sorting();

	void Print(DepartmentList & DepartmentList, ofstream & LOGFILE);

	void addGrade(char * sub_name, char * information, DepartmentList & DepartmentList, GradeList & GradeList);

	void addID(char * sub_name, char * information, DepartmentList & DepartmentList, StudentIDList & IDList);

	void addPhone(char * sub_name, char * information, DepartmentList & DepartmentList, ContactList & PhoneList);

	void updateGrade(char * sub_name, char * information, DepartmentList & DepartmentList, GradeList & GradeList);

	void updateID(char * sub_name, char * information, DepartmentList & DepartmentList, StudentIDList & IDList);

	void updatePhone(char * sub_name, char * information, DepartmentList & DepartmentList, ContactList & PhoneList);

	void Addname(DepartmentList & DepartmentList, char*Dename, char*name);

	void DeleteNode(Node * tmp);

	void Checksame(char * Savename, char * SavePhone, char * SaveID, ContactList & PhoneList, StudentIDList & IDList);

	void addInfo(DepartmentList & DepartmentList, NameList & NameList, GradeList & GradeList, ContactList & PhoneList, StudentIDList & IDList, int & number);

	void link_add(NameNode * newNode);

	void Checkde(DepartmentList & DepartmentList);

	void UpdateInfo(DepartmentList & DepartmentList, char * Dename, char * name);

	bool checkUp(char * Savename, char * SaveID, char * SavePhone, StudentIDList & IDList, ContactList & PhoneList);

	void Update(DepartmentList & DepartmentList, NameList & NameList, GradeList & GradeList, ContactList & PhoneList, StudentIDList & IDList, ofstream & LOGFILE);

	void Find(char * a, int count, ofstream & LOGFILE);

	void Print_De(char * information, DepartmentList & DepartmentList, ofstream & LOGFIEL);

	void Insertionsorting(char * information,Node*tmp);

	void DeleteList(Node * tmp);

	void PrintID(ofstream & LOGFIEL);

	void PrintDe(Node * tmp, ofstream & LOGFIEL);

	void Printname(ofstream & LOGFILE);

	void linknewNode(NameNode * newNode);

	void addnewNode(NameNode * newNode, Node * tmp);

	void createPhoneList(Node * tmp);

	void PrintPhone(ofstream & LOGFILE);

	NameNode* nameHead = NULL;
	NameNode* IDHead = NULL;
	NameNode* PhoneHead = NULL;
};
