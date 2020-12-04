#pragma once
#include<iostream>
#include"GradeNode.h"
#include"StudentIDNode.h"
#include"ContactNode.h"

class Node
{
protected:
	Node *Pnext=NULL;
	Node *Pprev=NULL;
	Node *Pup=NULL;
	Node *Pdown=NULL;
public:
	virtual Node *getNext() = 0; //The function for getting other Node
	virtual Node *getPrev() = 0; 
	virtual Node *getUp() = 0; 
	virtual Node *getDown() = 0; 
	
	virtual void setNext(Node *Pnext) = 0; //The function for saving other Node
	virtual void setPrev(Node *Pprev) = 0;
	virtual void setUp(Node *Pup) = 0;
	virtual void setDown(Node *pdown) = 0;

	virtual GradeNode *getGrade() = 0; //get Grade  Node
	virtual void setGrade(GradeNode *Grade) = 0;

	virtual StudentIDNode *getID() = 0; //get ID Node
	virtual void setID(StudentIDNode *ID) = 0;

	virtual ContactNode *getPhone() = 0; //get Contact Nde
	virtual void setPhone(ContactNode *Phone) = 0;

	virtual char *getInfo() = 0; //for get information of Node
};

