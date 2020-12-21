#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<chrono>
#include<cmath>
using namespace std;

void printArray(int A[], int size, int Cmp_Num, int cycle);
void Bubble(int A[],int size ,int option);
void Create_array(int A[], int size);
void Best_create_array(int A[], int size);
void Worst_create_array(int A[], int size);
void textcolor(int foreground, int background);
void Problem5();
void Problem6();
void Problem7();

#define LIGHTRED 12
#define LIGHTGREEN 10
#define YELLOW 14
#define WHITE 15
#define BLACK 0
#define NOP -100

int Info_count = 0;
int *Info;

int main()
{
	int button = 0; //For checking select menu
	cout << "***************************" << endl;
	cout << "*      Start Program      *" << endl;
	cout << "*       Algorithms        *" << endl;
	cout << "*       2015722025        *" << endl;
	cout << "*     Jeong yong hoon     *" << endl;
	cout << "***************************" << endl;

	while (1)
	{
		cout << endl;
		cout << "1.Problem 5" << endl; //menu of view
		cout << "2.Problem 6" << endl;
		cout << "3.Problem 7" << endl;
		cout << "4.Exit Program" << endl;
		cout << "Select menu: ";
		cin >> button;

		switch (button)
		{
		case 1:
			Problem5(); //Function of problem 5
			break;
		case 2:
			Problem6(); //Function of problem 6
			break;
		case 3:
			Problem7(); //function of problem 7
			break;
		case 4:
			cout << "***************************" << endl; //end of program
			cout << "*      End of Program     *" << endl;
			cout << "*       Algorithms        *" << endl;
			cout << "*       2015722025        *" << endl;
			cout << "*     Jeong yong hoon     *" << endl;
			cout << "***************************" << endl;
			return 0;
		}
	}
}

void Bubble(int A[], int size, int option)
{
	int i, j, tmp, flag, comparison = 0, cycle = 0;
	chrono::system_clock::time_point StartTime, EndTime; //value of checking excution time
	chrono::microseconds excution;

	cout << "---Input Array---" << endl;
	textcolor(LIGHTRED, BLACK);
	printArray(A, size, NOP, NOP); //View input array
	textcolor(WHITE, BLACK);
	cout << "-----------------" << endl;
	
	if (option == 3)
		StartTime = chrono::system_clock::now(); //Information of current time

	for (i = size - 1; i > 0; i--) //For decreasing time of comparing 
	{
		cycle++; //check cycle of bubble sort
		for (j = 0, flag = 0; j < i; j++, comparison++) //For comparing all items
		{
			if (option == 1)
				printArray(A, size, j, cycle); //For checking step by step

			if (A[j] > A[j + 1]) //Check integer
			{
				flag = 1;
				tmp = A[j + 1]; //swap
				A[j + 1] = A[j];
				A[j] = tmp;
			}
		}
		if (flag == 0) //For checking condition of orderig
			break;
	}

	if (option == 3) //For printing real time of excution
	{
		EndTime = chrono::system_clock::now();
		excution = chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime);
	}

	if (option == 3) //Print excution time
	{
		cout << "Excution time: " << excution.count() << endl;
		Info[Info_count] = excution.count();
	}

	else if (option == 2) //print number of comparison
		Info[Info_count] = comparison;

	cout << "---Output Array---" << endl; //For printing information of working
	textcolor(LIGHTGREEN, BLACK);
	printArray(A, size, NOP, NOP);
	textcolor(WHITE, BLACK);
	cout << "Size of array: " << size << endl;
	cout << "Number of cycle: " << cycle << endl;
	cout << "Number of comparison: " << comparison << endl;

	if (option == 3)
	{
		cout << "Excution time: " << excution.count() << endl;
		Info[Info_count] = excution.count();
	}

	else if(option ==2)
		Info[Info_count] = comparison;

	cout << "------------------" << endl;
	Info_count++;

	return;
}

void textcolor(int foreground, int background) //For change text color of console
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printArray(int A[], int size, int Cmp_Num, int cycle) //The function for printing array
{
	int flag = 0;
	for (int count = 0; count < size; count++) //The condition for change color of console
	{
		if ((Cmp_Num != NOP && Cmp_Num == count) || (Cmp_Num != NOP && Cmp_Num + 1 == count))
		{
			textcolor(LIGHTRED, BLACK); 
			flag = 1;
		}

		else if (Cmp_Num != NOP && size-cycle < count)
		{
			textcolor(LIGHTGREEN, BLACK);
			flag = 1;
		}

		cout << A[count] << " ";
		
		if(flag==1)
			textcolor(WHITE, BLACK);
	}
	cout << endl;
}

void Problem5()
{
	int Best[] = { 1,2,3,4,5,6,7 }; //For showing Best case
	int Worst[] = { 7,6,5,4,3,2,1 }; //For showing Worst case
	int* Average = new int[7];
	Create_array(Average,7); //For showing average case(Create random array)

	cout << endl << "(a)Best case" << endl;
	Bubble(Best, sizeof(Best) / 4, 1); //sorting

	cout << endl << "(b)Worst case" << endl;
	Bubble(Worst, sizeof(Worst) / 4, 1); //sorting

	cout << endl << "(c)Average case" << endl;
	Bubble(Average, 7, 1); //sorting

	delete[] Average;
}

void Problem6()	
{
	int size, repeat, Case;
	cout << "Input size of array: "; //Get size of array
	cin >> size;
	cout << "Input number of repetitions: "; //Get number of repetitions
	cin >> repeat;
	cout << "(1) Best case" << endl; //Get case of array
	cout << "(2) Worst case" << endl;
	cout << "(3) Average case" << endl;
	cout << "Select yout case: ";
	cin >> Case;

	int* A = new int[size];
	Info = new int[size];

	for (int count = 0; count < repeat; count++)
	{
		if (Case == 1) //Get array
			Best_create_array(A, size);
		else if (Case == 2)
			Worst_create_array(A, size);
		else if(Case == 3)
			Create_array(A, size);

		Bubble(A, size, 2); //practice sorting

		for (int init = 0; init < size; init++)
			A[init] = 0;

		Sleep(1000); //sleep function to prevent duplication of seed
	}

	cout << endl;
	cout << "Comparison of all case" << endl; //Output to clean up repeated results
	for (int i = 0; i < Info_count; i++)
	{
		cout << i + 1 << ".";
		textcolor(YELLOW, BLACK);
		cout << Info[i] << "  ";
		textcolor(WHITE, BLACK);
		if ((i + 1) % 5 == 0)
			cout << endl;
	}
	cout << endl;

	delete[] A;
	Info_count = 0;
	delete[] Info;
	return;
}

void Problem7() //Same as Problem 6() --- Just different Bubble option
{
	int size, repeat, Case;
	cout << "Input size of array: ";
	cin >> size;
	cout << "Input number of repetitions: ";
	cin >> repeat;
	cout << "(1) Best case" << endl;
	cout << "(2) Worst case" << endl;
	cout << "(3) Average case" << endl;
	cout << "Select yout case: ";
	cin >> Case;

	int* A = new int[size];
	Info = new int[size];

	for (int count = 0; count < repeat; count++)
	{
		if (Case == 1)
			Best_create_array(A, size);
		else if (Case == 2)
			Worst_create_array(A, size);
		else if (Case == 3)
			Create_array(A, size);

		Bubble(A, size, 3);

		for (int init = 0; init < size; init++)
			A[init] = 0;

		Sleep(1000);
	}

	cout << endl;
	cout << "Excution time of all case" << endl;
	for (int i = 0; i < Info_count; i++)
	{
		cout << i + 1 << ".";
		textcolor(YELLOW,BLACK);
		cout<<Info[i] << "  ";
		textcolor(WHITE, BLACK);
		if ((i + 1) % 5 == 0)
			cout << endl;
	}
	cout << endl;

	delete[] A;
	Info_count = 0;
	delete[] Info;
	return;
}

void Create_array(int A[], int size) //For creating random array
{
	int item;
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
	again:
		item = rand() % size + 1;

		for (int j = 0; j < size; j++)
			if (item == A[j])
				goto again;
		A[i] = item;
	}
}

void Best_create_array(int A[], int size) //Best case array
{
	for (int i = 0; i < size; i++)
		A[i] = i + 1;
}

void Worst_create_array(int A[], int size) //Worst case array
{
	for (int i = size; i > 0; i--)
		A[size-i] = i;
}