#pragma once
#include<iostream>
#include"DepartmentList.h"
#include"StudentIDNode.h"
class StudentIDList
{
public:
	StudentIDList();
	~StudentIDList();

	void link_id(DepartmentList & DepartmentList);

	StudentIDNode* IDHead = NULL;
};

