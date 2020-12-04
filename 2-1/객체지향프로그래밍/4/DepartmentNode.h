#pragma once
#include "Node.h"
#include <string>

class DepartmentNode :public Node
{
protected:
	char de_name[32];
public:
	DepartmentNode();
	~DepartmentNode();
	void Save_de(char* name)
	{
		strcpy(de_name, name);
	}
	char* Get_de()
	{
		return de_name;
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

	char *getname() {
		return de_name;
	}

	virtual void setNext(Node *next)
	{
		Pnext = next;
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
		return de_name;
	}



	virtual GradeNode *getGrade() {
		return NULL;
	}
	virtual void setGrade(GradeNode *Grade)
	{
		return;
	}

	virtual StudentIDNode *getID() {
		return NULL;
	}
	virtual void setID(StudentIDNode *ID)
	{
		return;
	}
	virtual ContactNode *getPhone() {
		return NULL;
	}
	virtual void setPhone(ContactNode *Phone)
	{
		return;
	}
};

