#include "Manager.h"
#include <stdlib.h>
using namespace std;

Manager::Manager()	//constructor
{
}

Manager::~Manager()//destructor
{
	/* You must fill here */
}

void Manager::run(const char * command, ofstream &flog)
{
	char *cmd;
	char *check;
	char checkcount[50];

	fin.open(command);// The function that opens file
	//flog.open("log.txt");
	flog.open("log.txt", ios::app);// The function that opens file

	cmd = new char[40];

	while (!fin.eof()) //repeat the function untill end for file
	{	
		fin.getline(cmd, 40); //load the command
		
		if (fin.fail()) //check loading file information
           		break; //break

		char * tmp = strtok(cmd, " "); //load the command before " "
		//char * tmp2 = strtok(cmd, " "); //load the command before " "

		if (strncmp(tmp, "LOAD",4) == 0) //If the command is LOAD, practice the function
		{
			check = strtok(NULL," ");
			if (check != NULL)
			{
				printErrorCode(100, flog);
				continue;
			}

			if(LOAD()) printSuccessCode("LOAD", flog);
			else printErrorCode(100, flog); //The error code

		}

		else if (strncmp(tmp, "ADD",3) == 0) //if the tmp is ADD, rpactice the function
		{
			check = strtok(NULL, " ");
			if (check != NULL)
			{
				printErrorCode(200, flog);
				continue;
			}

			if (ADD()) printSuccessCode("ADD", flog); //practice function if that true
			else printErrorCode(200, flog); //if not print error
		}

		else if (strncmp(tmp, "PRINT",5) == 0) //if the tmp is PRINT, rpactice the function
		{
			char * tmp2 = strtok(NULL, " ");
			char * tmp3 = strtok(NULL, " ");

			if (tmp2 == NULL)
			{ //if tmp2 is NULL
				printErrorCode(600, flog); //print error
				continue;
			}
			
			if (!strncmp(tmp2, "COMPLETE_LIST", 13) || !strncmp(tmp2, "TOTAL_LIST", 10))
			{ //The reason is different number of parameter
				if (tmp3 != NULL)
				{
					printErrorCode(600, flog); //print error
					continue;
				}
			}

			check = strtok(NULL, " ");
			if (check != NULL)
			{
				printErrorCode(600, flog);
				continue;
			}

			if (PRINT(flog, tmp2, tmp3)); //practice function if that true
			else printErrorCode(600, flog); //if not print error

		}

		else if (strncmp(tmp, "MOVE",4) == 0) //if the tmp is MOVE, rpactice the function
		{
			char * tmp2 = strtok(NULL, " ");
		
			if (tmp2 == NULL)
			{ //if tmp2 is NULL
				printErrorCode(300,flog); //print error
				continue;
			}

			check = strtok(NULL, " ");
			if (check != NULL)
			{
				printErrorCode(300, flog);
				continue;
			}

			int count = atoi(tmp2); //change character to integer

			sprintf(checkcount,"%d",count); //for checking parameter

			if(strncmp(tmp2,checkcount,sizeof(tmp2))) //for checking parameter state
				printErrorCode(300, flog); //if not print error
	
			if (MOVE(count,flog))  printSuccessCode("MOVE",flog); //practice function if that true
			else printErrorCode(300,flog); //if not print error
		}

		else if (strncmp(tmp, "SEARCH",6) == 0)
		{
			char * tmp2 = strtok(NULL," ");

			if (tmp2 == NULL) //check parameter
			{
				printErrorCode(500, flog);
				continue;
			}

			int carnum = atoi(tmp2);

			check = strtok(NULL, " ");
			if (check != NULL)
			{
				printErrorCode(500, flog);
				continue;
			}

			if (SEARCH(carnum,flog));
			else printErrorCode(500, flog);
		}

		else if (strncmp(tmp, "COMPLETE",8)==0)
		{
			char * tmp2 = strtok(NULL, " ");

			if (tmp2 == NULL) //check parameter
			{
				printErrorCode(700, flog);
				continue;
			}

			check = strtok(NULL, " ");
			if (check != NULL)
			{
				printErrorCode(700, flog);
				continue;
			}

			int carnum = atoi(tmp2);
			if (COMPLETE(carnum, flog));
			else printErrorCode(700, flog);
		}

		else if (strncmp(tmp, "SAVE",4) == 0)
		{
			check = strtok(NULL, " ");
			if (check != NULL)
			{
				printErrorCode(400, flog);
				continue;

			}
			if (SAVE()) printSuccessCode("SAVE", flog);
			else printErrorCode(400, flog);
		}
		
		else if (strncmp(tmp, "EXIT",4) == 0)
		{
			check = strtok(NULL, " ");
			if (check != NULL)
			{
				printErrorCode(0, flog);
				continue;
			}

			if (EXIT()) printSuccessCode("EXIT", flog);
			else printErrorCode(0, flog);

			delete cmd;
			return;
		}
		else	printErrorCode(0,flog);

	}
	fin.close();
	flog.close();
	delete cmd;
	return;
}

bool Manager::LOAD()
{ //The function that load the three data structure
	ifstream llF;
	ifstream bstF;
	ifstream queueF;
	int carinfoN = 0;
	char carinfoO[50];
	char carinfoS[50];
	NumberNode*search = NULL;

	if (ll == NULL && bst == NULL && queue == NULL)
	{ //If all data structure have data, practice the function
		llF.open("total_list_car.txt"); //The function that open file
		if (!llF) //Checking file dosen't open
			return 0;
		bstF.open("event_list_car.txt");
		if (!bstF)
			return 0;
		queueF.open("complete_list_car.txt");
		if (!queueF)
			return 0;

		LinkedList * newll = new LinkedList;
		ll = newll; //make linked list

		while (!llF.eof())
		{ //Load the information of linked list
			llF >> carinfoN;
			llF >> carinfoO;
			llF >> carinfoS;
			if (strlen(carinfoO)<3) //Prevent spaces from being stored on nodes
				break;
			CarNode *newNode = new CarNode;

			newNode->SetcarNum(carinfoN);
			newNode->SetcarOwner(carinfoO);
			newNode->Setstate(carinfoS);
			ll->Insert(newNode);
		}
		//////////////////////////////////////////
		NumberBST * newbst = new NumberBST;
		bst = newbst; //make BST

		while (!bstF.eof()&&bst->getCnt(0)!=100)
		{ //Load the information of BST
			bstF >> carinfoN;
			bstF >> carinfoO;
			bstF >> carinfoS;

			if(bstF.fail()) //check file
				break;
			
			if (strlen(carinfoO)<3) //Prevent spaces from being stored on nodes
				break;
			CarNode *newNode = new CarNode;
			bst->getCnt(1);

			newNode->SetcarNum(carinfoN);
			newNode->SetcarOwner(carinfoO);
			newNode->Setstate(carinfoS);
	
			search = bst->Checknumber(newNode->GetcarNum());//return the number Node that is searched

			if (search->GetBST() == NULL)
			{
				CarBST * BST = new CarBST;
				search->SetBST(BST); //link the number node and BST	
			}
			search->GetBST()->Insert(newNode); //Insert
		}
		////////////////////////////////////////////////
		Queue * newQ = new Queue;
		queue = newQ; //make queue

		while (!queueF.eof())
		{ //Load the information of queue
			queueF >> carinfoN;
			queueF >> carinfoO;
			queueF >> carinfoS;
			if (strlen(carinfoO)<3) //Prevent spaces from being stored on nodes
				break;
			CarNode *newNode = new CarNode;

			newNode->SetcarNum(carinfoN);
			newNode->SetcarOwner(carinfoO);
			newNode->Setstate(carinfoS);
			queue->Push(newNode);
			delete newNode;
		}
		llF.close(); //close file of information
		bstF.close();
		queueF.close();
		return true; //return true
	}
	else
		return false; //return false
}

bool Manager::SAVE()
{ //The command of SAVE
	if (ll == NULL || bst == NULL || queue == NULL)
		return false; //If any information is missing, return false

	ll->Save();
	bst->Save();
	queue->Save();
	return 1;
}

bool Manager::COMPLETE(int carnum, ofstream & flog)
{ //The function for practicing complete that
	if (bst == NULL) //for checking there is data or no data
		return false;
	char command[50]={"COMPLETE"};
	if (bst->Delete(carnum, flog) != NULL)
	{
		if (queue == NULL)
		{
			Queue * newQ = new Queue;
			queue = newQ;
		}

		queue->Push(bst->Delete(carnum, flog)->GetBST()->Complete(carnum, flog)); //Input the information
		queue->Search(carnum, flog, command);
		bst->Delete(carnum, flog)->GetBST()->Delete(carnum); //Delete from event list
		bst->getCnt(-1);
		return 1;
	}
	else
		return 0;
}

bool Manager::EXIT()
{
	delete ll; //delete all linked list data
	delete bst; //delete all binary search tree data
	delete queue; //delete all queue data

	return 1;
}

bool Manager::ADD()
{ //The function that load car data, if there are no data
	fstream info("car.txt"); //load the file
	int carinfoN=0;
	char carinfoO[50];
	char carinfoS[50];

	int count = 0;

	if (ll == NULL)
	{ //if the linked list dosen't exist, create linked list
		LinkedList *newll = new LinkedList; //create linked list
		ll = newll; //save ll
	}

	if (ll->pHead != NULL) //if already exist the data, return false
		return 0;

	else if (ll->pHead == NULL)
	{ //Dosen't exist the data
		while (!info.eof())
		{ //repeat the function before end of file
			info >> carinfoN;
			if (carinfoN == 0) //check the data
				return false;
			info >> carinfoO;
			info >> carinfoS;
			if (strlen(carinfoO)<3) //Prevent spaces from being stored on nodes
				break;

			
			CarNode *newNode = new CarNode;

			newNode->SetcarNum(carinfoN);
			newNode->SetcarOwner(carinfoO);
			newNode->Setstate(carinfoS);
			ll->Insert(newNode); //insert node
		}
	}
	return 1;
}

bool Manager::MOVE(int info, ofstream &flog)
{ //The function for sending data to BST from linked list
	int count = 0;

	if (this->ll == NULL)
		return false;

	CarNode*tmp = ll->pHead;
	CarNode*prev = ll->pHead;
	NumberNode*search = NULL;

	if (ll == NULL || ll->pHead == NULL)
		return false; //check there is data of no data

	if (bst == NULL)
	{ //if the BST is null, create new bst
		NumberBST * newbst = new NumberBST; //creat bst
		bst = newbst; //save bst
	}

	if (bst->getCnt(0) == 100) //check number of node
		return false;

	while (count != info && tmp != NULL)
	{

		if (strncmp(tmp->Getstate(), "Y", 1) == 0)
		{ //In case someone have an accident history
			search = bst->Checknumber(tmp->GetcarNum());//return the Number Node that is searched
			if (search->GetBST() == NULL)
			{
				CarBST * BST = new CarBST;
				search->SetBST(BST); //link the number node to BST
			}

			search->GetBST()->Insert(tmp); //Insert

			if (ll->Delete(prev, tmp))
			{
				prev = ll->pHead;
				tmp = ll->pHead;
			}

			else
				tmp = prev->GetNext();

			bst->getCnt(1); //Checking number of BST node
			count++;

			if (bst->getCnt(0) == 100)
			break;
		}

		else if (strcmp(tmp->Getstate(), "Y") != 0)
		{ //No accident history
			prev = tmp;
			tmp = tmp->GetNext();
		}
	}
	if (count != info)//If the integer from command is smaller than number of information, return false
		return false;

	return true;
}

bool Manager::PRINT(ofstream & flog,char*tmp2,char*tmp3)
{ //for checking type of print

	if (strncmp(tmp2, "TOTAL_LIST",10)==0)
	{ //for printing linked list
		if (ll == NULL || ll->pHead == NULL) //|| ll == nullptr || ll->pHead == nullptr)
			return 0;
		else
		{
			ll->Print(flog);
			return 1;
		}
	}
	else if (strncmp(tmp2, "COMPLETE_LIST",13) == 0)
	{ //for printing queue
		if (queue == NULL || queue->pHead == NULL) //|| queue == nullptr || queue->pHead == nullptr)
			return 0;
		else
		{
			queue->Print(flog);
			return 1;
		}
	}
	else if (strncmp(tmp2, "EVENT_LIST",10)==0)
	{ //for printing bst
		if (tmp3 == NULL)
			return 0;

		if (bst == NULL || bst->Getroot() == NULL) //|| bst == nullptr || bst->Getroot() == nullptr)
			return 0;

		else if (bst->Print(tmp3, flog))
			return 1;
		else
			return 0;
	}
	return 0;
}

bool Manager::SEARCH(int carnum, ofstream& flog)
{ //for searching data according to carnumber
	char command[50]={"SEARCH"};

	if (ll->Search(carnum, flog) != NULL)
		return 1;

	else if (bst->Search(carnum, flog) != NULL)
		return 1;

	else if (queue->Search(carnum, flog,command) != NULL)
		return 1;
	

	return 0;
}

void Manager::printErrorCode(int n, ofstream &flog) {				//ERROR CODE PRINT 
	flog << "======== ERROR ========" << endl;
	flog << n << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode(const char * cmdname, ofstream &flog) {//SUCCESS CODE PRINT 
	flog << "======== "<<cmdname<<" ========" << endl;
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}
