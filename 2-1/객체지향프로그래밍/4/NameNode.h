#pragma once
#include "Node.h"
#include"GradeNode.h"
#include"StudentIDNode.h"
#include"ContactNode.h"
#include<iostream>
#include<string>

class NameNode :public Node
{
public:
	char name[32];
	GradeNode *Pleft = NULL;
	StudentIDNode *Pfornt = NULL;
	ContactNode *Pright = NULL;
public:
	void Save_name(char* Pname)
	{
		strcpy(name, Pname);
	}
	char* Get_name()
	{
		return name;
	}

	virtual GradeNode *getGrade() {
		return Pleft;
	}
	virtual void setGrade(GradeNode *Grade)
    {
		this->Pleft = Grade;
	}

	virtual StudentIDNode *getID() {
		return Pfornt;
	}
	virtual void setID(StudentIDNode *ID)
	{
		this->Pfornt = ID;
	}
	virtual ContactNode *getPhone() {
		return Pright;
	}
	virtual void setPhone(ContactNode *Phone)
	{
		this->Pright = Phone;
	}
	virtual Node *getNext() {
		return Pnext;
	}
	virtual Node *getPrev() {
		return Pprev;
	}
	virtual Node *getUp() {
		return Pup;
	}
	virtual Node *getDown() {
		return Pdown;
	}

	virtual void setNext(Node *next)
	{
		this->Pnext = next;
	}
	virtual void setPrev(Node *prev)
	{
		this->Pprev = prev;
	}
	virtual void setUp(Node *up)
	{
		this->Pup = up;
	}
	virtual void setDown(Node *down)
	{
		this->Pdown = down;
	}

	virtual char *getInfo()
	{
		return name;
	}
};

