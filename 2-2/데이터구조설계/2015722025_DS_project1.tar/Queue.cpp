#include "Queue.h"

Queue::Queue()//constructor
{
}


Queue::~Queue()//destructor
{
	Pop();
	/* You must fill here */
}

void Queue::Push(CarNode * node)
{ //For inserting to queue
	if (pHead == NULL)
	{ //if the head is null, make head
		char check[10]={"C"};

		CarNode * newNode = new CarNode;
		newNode->SetcarNum(node->GetcarNum());
		newNode->SetcarOwner(node->GetcarOwner());
		newNode->Setstate(check);
		pHead = newNode;
	}

	else
	{ //if the head is not null, link the new node
		CarNode * tmp = pHead;
		char check[10]={"C"};

		CarNode * newNode = new CarNode;
		newNode->SetcarNum(node->GetcarNum());
		newNode->SetcarOwner(node->GetcarOwner());
		newNode->Setstate(check);

		for (; tmp->GetNext(); tmp = tmp->GetNext()); //the function send the tmp to end of node

		tmp->SetNext(newNode); //link the new node
	}
	return;
}

CarNode * Queue::Pop()
{ //for delete the queue
	CarNode*tmp = pHead;

	while (tmp)
	{ //repeat the function if the tmp is not null
		pHead = tmp->GetNext();
		delete tmp; //delete the tmp
		tmp = pHead;
	}
	return NULL;
}

CarNode * Queue::Search(int num, ofstream & flog, char * codename)
{ //for searching the node in queue
	if (this == NULL)
		return NULL;
	CarNode*tmp = pHead;
	for (; tmp; tmp = tmp->GetNext())
	{
		if (tmp->GetcarNum() == num&&!strncmp(codename,"COMPLETE",8))
		{ //the function for COMPLETE
			flog << "======== " << codename << "========" << endl;
			flog << tmp->GetcarNum() << " / ";
			flog << tmp->GetcarOwner() << " / ";
			flog << tmp->Getstate();
			flog << endl;
			flog << "=======================" << endl << endl;
			return tmp; //return tmp that is checked
		}

		else if (tmp->GetcarNum() == num&&!strncmp(codename,"SEARCH",6))
		{ //the function for SEARCH
			flog << "======== " << codename << "========" << endl;
			flog << tmp->GetcarNum() << " / ";
			flog << tmp->GetcarOwner() << " / ";
			flog << tmp->Getstate();
			flog << endl;
			flog << "=======================" << endl << endl;
			return tmp; //return tmp that is checked
		}
		else if (tmp->GetcarNum() == num) //the function for other case
			return tmp;
	}
	return NULL;
}

bool Queue::Print(ofstream & flog)
{ //for printing data structure that is queue
	CarNode*tmp = pHead;

	flog << "======== " << "PRINT " << "========" << endl;
	for (; tmp; tmp = tmp->GetNext())
	{ //repeat the function if tmp is not null
		flog << tmp->GetcarNum() << " / ";
		flog << tmp->GetcarOwner() << " / ";
		flog << tmp->Getstate();
		flog << endl;
	}
	flog << "=======================" << endl << endl;
	return 1;
}

bool Queue::Save()
{ //for saving the data of queue
	ofstream q_list("complete_list_car.txt");
	CarNode*tmp = pHead;
	for (; tmp; tmp = tmp->GetNext())
	{ //repeat the function if tmp is not null
		q_list << tmp->GetcarNum() << " ";
		q_list << tmp->GetcarOwner() << " ";
		q_list << tmp->Getstate() << endl;
	}
	return false;
}
