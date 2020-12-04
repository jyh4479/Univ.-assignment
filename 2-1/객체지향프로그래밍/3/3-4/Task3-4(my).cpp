#include<iostream>
#include<time.h> //Declare time.h, for using random function
#include"queue.h"
#include"Node.h"

using namespace std;

int main()
{
	int size, select; //Declare integer variable
	queue* q = new queue; //Declare q in heep area
	srand((unsigned int)time(NULL)); //For changing seed value

	cout << "Queue Size : "; //print string
	cin >> size; //Get vlaue from keyboard and save to size

	while (size > 52 || size < 1) //
	{
		cout << "Input Queue Size again(1~52) : ";
		cin >> size;
	}

	while (1) //Repeat the function, untill break
	{
		cout << "------------------------" << endl;
		cout << "Queue Size : " << size << endl;
		cout << "1. Generate a card" << endl;
		cout << "2. Delete a card" << endl;
		cout << "3. Show all cards" << endl;
		cout << "4. End " << endl;
		cout << "------------------------" << endl;
		cout << "Select menu : ";
     	cin >> select; //Get vlaue from keyboard and save to select

		if (select == 1) //If select is 1, practice the function
		{
			if (q->IsFull(q, size)) //The function that check queue is full or not
			{
				cout << "Queue is Full" << endl;
				continue;
			}
			q->Push(q); //This is function of insertion
			q->same(q); //This is function that check the same card
		}
		
		if (select == 2) //If select is 2, practice the function
		{
			if (q->IsEmpty(q)) //The function that check queue is empty or not
			{
				cout << "Queue is Empty" << endl;
				continue;
			}
			q->Pop(q); //This is function of deletion
		}

		if (select == 3) //If select is 3, practice the function
			q->print(q); //This is function of print all card

		if (select == 4) //If select is 4, practice the function
		{
			cout << "End the program" << endl; 
			return 0; //Declare end of main function
		}
	}
}