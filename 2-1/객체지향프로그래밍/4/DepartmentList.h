#pragma once
#include "Node.h"
#include"DepartmentNode.h"
#include<iostream>
#include<fstream>
using namespace std;

class DepartmentList
{
public:
	DepartmentList();
	~DepartmentList();

	DepartmentNode* mHead = NULL;
	DepartmentNode* mtail = NULL;
	void insert_de(char* name);
	void linktail();
	void changeHead(DepartmentNode * newNode);
	void changetail(DepartmentNode * newNode);
	void newcreate(char * a, char * b, Node * tmp);
	bool Check2(Node * tmp, Node * tail);
	void sortingname(char * b);
	void MoveDepartment(char * a, char * b);
	void workModify(Node * Dtmp, char * a, char * b);
	void Modify(char * a, char * b, ofstream & LOGFILE);
	void Delete(char * a);
	bool check(char* name);
	void LinkHead();
	void Print();
	void Savetxt(char * a);
};
