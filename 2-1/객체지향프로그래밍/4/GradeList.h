#pragma once
#include<iostream>
#include"DepartmentList.h"
#include"GradeNode.h"
class GradeList
{
public:
	GradeList();
	~GradeList();
	void link_gr(DepartmentList&DepartmentList);

	GradeNode* GradeHead=NULL;
};

