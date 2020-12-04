#pragma once
#include<iostream>
class StudentIDNode
{
protected:
	char ID[100] = { NULL };
	StudentIDNode*Pfornt = NULL;
public:
	StudentIDNode();
	~StudentIDNode();

	void setID(char* inID) {
		strcpy(ID, inID);
	}
	char *getIDInfo() {
		return ID;
	}

	void setNext(StudentIDNode* getInfo) {
		this->Pfornt = getInfo;
	}

	StudentIDNode*getNext() {
		return Pfornt;
	}
};

