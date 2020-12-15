#pragma once
#include "LinkedList.h"
#include "NumberBST.h"
#include "Queue.h"
#include<utility>


class Manager
{
public:
	LinkedList * ll = NULL;
	NumberBST * bst = NULL;
	Queue * queue = NULL;

public:
	Manager();
	~Manager();

	fstream fin;

	void run(const char * command,ofstream &flog); //The function works for other function
	bool LOAD(); //Load the data from txt file
	bool MOVE(int info, ofstream & flog); //for moving data to bst from linked list
	bool ADD(); //Load the data from txt file, If there is no data
	bool SAVE(); //Save the data structure that made by command
	bool SEARCH(int carnum, ofstream & flog); //for searching correct node
	bool PRINT(ofstream&flog, char*tmp2, char*tmp3); //the function for printing data
	bool COMPLETE(int carnum, ofstream & flog); //the function send the data to queue from bst
	bool EXIT(); //for ending of program

	void printErrorCode(int n, ofstream &flog); //for check error and print code
	void printSuccessCode(const char * cmdname, ofstream &flog); //for check working of function and print code
};
