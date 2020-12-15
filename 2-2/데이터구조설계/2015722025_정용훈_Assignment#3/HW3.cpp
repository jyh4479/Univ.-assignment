#include <iostream> 
#include "MaxHeap.h"
using namespace std;

int main() 
{
	MaxHeap<int> myHeap; //Declare Heap
	srand((unsigned)time(NULL)); //Generate random numbers over time

	for (int i = 0; i < 10; i++)
	{ //Insert the data to Node
		int number = rand() % 100 + 1;
		myHeap.Push(number);
	}

	cout << "Print all data of node!" << endl; //Print data of Heap
	for (int i = 1; i < 11; i++) //repeat function
		cout << myHeap.getHeap()[i] << " "; //Print data
	cout << endl << endl;
	
	int count = 1;
	cout << "Print all data of node _ LEVEL!" << endl; //Print by Level
	for (int i = 1; true; i = 2 * i)
	{ //The Algorithm for printing Maxheap by Level
		for (; count < i; count++)
		{
			for (int space = 0; space < myHeap.getSize() - i; space++)
				cout << " "; //Print space

			if (count <= myHeap.getSize())
				cout << myHeap.getHeap()[count]<<" "; //Print data
		}
		cout << endl;

		if (i > myHeap.getSize()) //if i is bigger than heap size
			break; //break
	}
	cout << endl << endl;

	cout << "Practice three time pop function" << endl;
	myHeap.Pop(); //practice pop function
	myHeap.Pop();
	myHeap.Pop();
	cout << endl << endl;

	count = 1;
	cout << "Print all data of node _ LEVEL!" << endl; //Print data of Heap
	for (int i = 1; true; i = 2 * i)
	{ //The Algorithm for printing Maxheap by Level
		for (; count < i; count++)
		{
			for (int space = 0; space < myHeap.getSize() - i; space++)
				cout << " "; //Print space

			if (count <= myHeap.getSize())
				cout << myHeap.getHeap()[count] << " "; //Print data
		}
		cout << endl;

		if (i > myHeap.getSize()) //if i is bigger than heap size
			break; //break
	}
	cout << endl << endl;
	return 0;
}


