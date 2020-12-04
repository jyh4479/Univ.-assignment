#pragma once
#include<iostream>
#include"ContactNode.h"
#include"DepartmentList.h"
class ContactList
{
public:
	ContactList();
	~ContactList();

	void link_Ph(DepartmentList & DepartmentList);

	ContactNode* PhoneHead=NULL;
};

