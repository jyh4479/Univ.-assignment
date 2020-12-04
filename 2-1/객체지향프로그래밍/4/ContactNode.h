#pragma once
#include<iostream>
class ContactNode
{
protected:
	char Phone[100] = { NULL };
	ContactNode*Pright = NULL;
public:
	ContactNode();
	~ContactNode();

	void setPhone(char* inPhone) {
		strcpy(Phone, inPhone);
	}
	char *getPhoneInfo() {
		return Phone;
	}

	void setNext(ContactNode* getInfo) {
		this->Pright = getInfo;
	}

	ContactNode*getNext() {
		return Pright;
	}
};

