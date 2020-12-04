#pragma once
#include<iostream>
class GradeNode
{
protected:
	char Grade[20] = { NULL };
	GradeNode*Pleft=NULL;
public:
	GradeNode();
	~GradeNode();

	void setGrade(char* inGrade) {
		strcpy(Grade, inGrade);
	}
	char *getGradeInfo() {
		return Grade;
	}

	void setNext(GradeNode* getInfo) {
		this->Pleft = getInfo;
	}

	GradeNode*getNext(){
		return Pleft;
	}
};

