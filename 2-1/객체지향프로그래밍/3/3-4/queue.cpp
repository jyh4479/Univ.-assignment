#include "queue.h"
#include "Node.h"
#include<iostream>
using namespace std;

queue::queue()
{
	size = 0;
	mHead = NULL;
	tail = NULL;
}

void queue::Push(queue* q) //The function that uisng for create new card
{
	Node* newnode = new Node; //Declare newnode in heep area
	newnode->setnumber(newnode->getnumber()); //Save random number
	newnode->setshape(newnode->getshape()); //Save random shape
	newnode->setnext(NULL); //Save NULL

	if (IsEmpty(q)) //Check the Linked list is empty or not
	{
		q->mHead = newnode; //Save newnode to q=>mHead
		q->tail = newnode; //Save newnode to q->tail
	}
	else
	{
		q->tail->setnext(newnode); //Link the tail and newnode
		q->tail=newnode; //The tail point newnode
	}
	q->size++; //Save q->size + 1 to q->size
}

bool queue::IsEmpty(queue*q) //For checking size is 0 or not
{
	if (q->size == 0) //If q->size is 0 return 1
		return 1;
	else
		return 0; //or not return 0
}
bool queue::IsFull(queue*q,int size) //For checking size is Full or not
{
	if (q->size == size) //q->size is equal size 
		return 1; //return 1
	else
		return 0; //or not return 0
}

void queue::Pop(queue* q) //The option of Delete Node
{
	Node* tmp = q->mHead; //Declare tmp and Save q->mHead to tmp

	mHead = tmp->next(tmp); //Save tmp->next(tmp) to mHead

	//This function work for printing shape of card
	if (tmp->shape(tmp) == 'a') 
		cout << "¢¾";
	if (tmp->shape(tmp) == 'b')
		cout << "¢¼";
	if (tmp->shape(tmp) == 'c')
		cout << "¢À";
	if (tmp->shape(tmp) == 'd')
		cout << "¡ß";
	
	cout << tmp->number(tmp) << " is popped" << endl; //show the card is deleted

	delete tmp; //delete tmp

	q->size--; //Save q->size-1 to q->size

	if (q->size == 0) //If q->size is 0, practice the function
		cout << "Queue is Empty" << endl; //print string
}

void queue::print(queue*q) //The function show all card
{
	Node* tmp = q->mHead; //declare tmp, and save q->mHead to tmp

	if (tmp == NULL) //If tmp is NULL, practice the function
	{
		cout << "Queue is Empty" << endl; //print string
		return; //return;
	}

	while (tmp) //If tmp is not NULL, repeat the function
	{

		//This function work for printing shape of card
		if (tmp->shape(tmp) == 'a')
			cout << "¢¾";
		else if (tmp->shape(tmp) == 'b')
			cout << "¢¼";
		else if (tmp->shape(tmp) == 'c')
			cout << "¢À";
		else if (tmp->shape(tmp) == 'd')
			cout << "¡ß";

		cout << tmp->number(tmp); //print card number

		if (tmp->next(tmp) != NULL) //If tmo->next(tmp) is not NULL, print slash
			cout << " / ";

		tmp = tmp->next(tmp); //Save tmp->next(tmp) to tmp
	}
	cout << endl;
}

void queue::same(queue* q) //Checking the card To prevent duplication
{
	Node* tmp = q->mHead; //Declare tmp and Save q->mHead to tmp
	Node* tail = q->mHead; //Declare tail and Save q->mHead to tail
	int a = 0, b = 0, c = 0, d = 0;

	if (tmp->next(tmp) == NULL) //If tmp->next(tmp) is NULL, return
		return;

	else
	{
		for (; tail->next(tail) != NULL; tail = tail->next(tail));//To save end Node to tail

		while (tmp->next(tmp) != tail->next(tail))
		{//Repeat function, while tmp->next(tmp) != tail->next(tail)
			{
				if (tmp->number(tmp) == tail->number(tail) && tmp->shape(tmp) == tail->shape(tail))
				{//If newNode and the other Node's information is same, change the value of newNode
					tail->setnumber(tail->getnumber());
					tail->setshape(tail->getshape());
					tmp = q->mHead;
					a = 0, b = 0, c = 0, d = 0;
				}
				else
					tmp = tmp->next(tmp); //Save tmp->next(tmp) to tmp
			}
		}
	}
}

