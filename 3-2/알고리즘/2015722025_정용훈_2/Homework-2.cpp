#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<chrono>
#include<cmath>
using namespace std;

void Create_array(int A[], int size);
void textcolor(int foreground, int background);
int Partition(int Array[], int p, int q);
void Quicksort(int Array[], int p, int r,int option);
void Problem2();
void Problem3();
void Problem4();
void FillArray(int Array[], int size);
void swap(int Array[], int i, int j);
void CreateBestcase(int Array[], int begin, int end);
void InitializeArray(int Array[], int size);
void printArray(int Array[], int p, int r, int size);
int sizeArray(int Array[]);

#define LIGHTRED 12
#define LIGHTGREEN 10
#define DARKGRAY 8
#define YELLOW 14
#define WHITE 15
#define BLACK 0
#define GREEN 12
#define NOP -100

int Info_count = 0;
int Info_count2 = 0;
int* Info_Worst;
int* Info_Best;
int* Info_Average;
int P_flag = 0;

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
		cout << "1.Problem 2" << endl; //menu of view
		cout << "2.Problem 3" << endl;
		cout << "3.Problem 4" << endl;
		cout << "4.Exit Program" << endl;
		cout << "Select menu: ";
		cin >> button;

		switch (button)
		{
		case 1:
			Problem2(); //Function of problem 2
			break;
		case 2:
			Problem3(); //Function of problem 3
			break;
		case 3:
			Problem4(); //function of problem 4
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

void textcolor(int foreground, int background) //For change text color of console
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Create_array(int A[], int size) //For creating random array
{
	int item;
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
	again: //lable
		item = rand() % size + 1;

		for (int j = 0; j < size; j++)
			if (item == A[j]) //check items
				goto again;
		A[i] = item;
	}
}

int Partition(int Array[], int p, int q) //The function of partition of qucik sort
{
	int x = Array[p]; //pivot
	int i = p;
	int tmp = 0;
	
	for (int j = p + 1; j <= q; j++)
	{
		Info_count++; //For checking comparison
		if (Array[j] <= x)
		{
			i++;
			tmp = Array[i];
			Array[i] = Array[j];
			Array[j] = tmp;
		}
	}
	tmp = Array[p]; //swap
	Array[p] = Array[i];
	Array[i] = tmp;

	return i; //return i
}

int Random_Partition(int Array[], int p, int q, int option)  //The function of partition 
//of randomized qucik sort
{
	int x = (rand() % (q - p + 1)) + p; //select random pivot

	if (option == 1)
	{
		cout << "Select    : ";
		printArray(Array, x, NOP, sizeArray(Array));
	}

	int tmp = Array[x]; //move pivot is selected
	Array[x] = Array[p];
	Array[p] = tmp;

	if (option == 1)
	{
		cout << "Swap pivot: ";
		printArray(Array, p, q, sizeArray(Array));
	}
	return Partition(Array, p, q); //practice normal partition
}

void Quicksort(int Array[], int p, int r, int option) //Function of Quick sort
{
	if (p < r) //check number of items
	{
		if(option==1)
			printArray(Array, p, r, sizeArray(Array));

		int q = Partition(Array, p, r); //practice partition
		Quicksort(Array, p,q-1,option); //recursive function
		Quicksort(Array, q + 1, r,option);
	}
}

void Random_Quicksort(int Array[], int p, int r, int option) //Randomized quick sort
{
	if (p < r) //Remaining content is equal to normal Quick sort Exclude partition function
	{
		int q = Random_Partition(Array, p, r, option);
		Random_Quicksort(Array, p, q - 1, option);
		Random_Quicksort(Array, q + 1, r, option);
	}
}

int sizeArray(int Array[]) //For returning size of Array
{
	int count = 0;
	for (int i = 0; Array[i] > 0; i++)
		count++;
	return count;
}

void Problem2() //The function is solution of task 2
{
	int A[] = { 1,2,3,4,5,6,7,8,9 };
	int B[15] = { 0 };

	//////Legend////////
	cout << endl;
	textcolor(BLACK, YELLOW);
	cout << "    ";
	textcolor(WHITE, BLACK);
	cout << " :Pivot  ";
	textcolor(LIGHTGREEN, DARKGRAY);
	cout << "    ";
	textcolor(WHITE, BLACK);
	cout << " :Sub Array"<<endl;
	/////////////////////

	///////Worst case//////////
	cout << "--------------------" << endl;
	Quicksort(A, 0, (sizeof(A) / 4)-1,1); //practice sortig
	Info_count = 0;
	cout << "-------Result-------" << endl;
	printArray(A, NOP, NOP, sizeArray(A)); //print
	cout << endl;
	///////////////////////////

	//////Best case////////////
	cout << "--------------------" << endl;
	FillArray(B,15);
	CreateBestcase(B,0,15);
	Quicksort(B, 0, (sizeof(B) / 4)-1,1); //practice sortig
	Info_count = 0;
	cout << "-------Result-------" << endl;
	printArray(B, NOP, NOP, sizeArray(B)); //print
	cout << endl;
	///////////////////////////

	///////Average case////////
	cout << "--------------------" << endl;
	InitializeArray(A, 9);
	Create_array(A, 9);
	Random_Quicksort(A, 0, (sizeof(A) / 4) - 1, 1); //practice sortig
	Info_count = 0;
	cout << "-------Result-------" << endl;
	printArray(A, NOP, NOP, sizeArray(A)); //print
	cout << endl;
	///////////////////////////
	return;
}

void Problem3() //The function is solution of task 3
{
	int size = 0;

	cout << "Input your size of Array: "; //Declare size of Array
	cin >> size;

	int* A = new int[size]; //create array

	FillArray(A, size); //Fill Array with items -> Worst case
	P_flag = 1;
	textcolor(LIGHTRED, BLACK);
	printArray(A, NOP, NOP, size); //print Array before sorting
	P_flag = 0;
	Quicksort(A, 0, size - 1, NOP); //sorting
	cout << "--------------------------------" << endl;
	printArray(A, NOP, NOP, size); //print Array after sorting
	cout << "--------------------------------" << endl;
	cout << "Number of Worst comparisons: " << Info_count << endl << endl << endl;
	Info_count = 0;

	FillArray(A, size); //Fill Array with items
	CreateBestcase(A, 0, size); //and makes Array of best case to practice quick sort
	P_flag = 1;
	textcolor(LIGHTRED, BLACK);
	printArray(A, NOP, NOP, size);
	P_flag = 0;
	Quicksort(A, 0, size - 1, NOP);
	cout << "--------------------------------" << endl;
	printArray(A, NOP, NOP, size);
	cout << "--------------------------------" << endl;
	cout << "Number of Best comparisons: " << Info_count << endl << endl << endl;
	Info_count = 0;

	Info_Average = new int[15];
	for (int i = 0; i < 15; i++)
	{
		InitializeArray(A, size);
		Create_array(A, size); //Makes Array of Average case
		P_flag = 1;
		textcolor(LIGHTRED, BLACK);
		printArray(A, NOP, NOP, size);
		P_flag = 0;
		Random_Quicksort(A, 0, size - 1, NOP);
		cout << "--------------------------------" << endl;
		printArray(A, NOP, NOP, size);
		cout << "--------------------------------" << endl;
		cout << "Number of Average comparisons: " << Info_count << endl << endl << endl;


		Info_Average[Info_count2] = Info_count;
		Info_count = 0;
		Info_count2++;
		Sleep(1000);
	}
	 /////////////////For printing Average case/////////////////////
	cout << "-----------Average Case-----------" << endl;
	for (int a = 0; a < Info_count2; a++)
	{
		cout << a + 1 << ".";
		textcolor(YELLOW, BLACK);
		cout << Info_Average[a] << "  ";
		if ((a + 1) % 5 == 0)
			cout << endl;
		textcolor(WHITE, BLACK);
	}
	cout << "----------------------------------" << endl;
	/////////////////For printing Average case/////////////////////
	Info_count2 = 0;
	delete[] Info_Average;
	delete[] A;

	return;
}

void Problem4() //--> Equal to Problem 3, just different measure content
{
	chrono::system_clock::time_point StartTime, EndTime; //value of checking excution time
	chrono::microseconds excution;

	excution = chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime);

	int size = 0;
	int repeat = 0;
	int Average1 = 0, Average2 = 0, Average3 = 0;

	cout << "Input your size of Array: ";
	cin >> size;

	cout << "Input your number of repeating: ";
	cin >> repeat;

	Info_Worst = new int[size];
	Info_Best = new int[size];
	Info_Average = new int[size];

	for (int i = 0; i < repeat; i++)
	{
		int* A = new int[size];

		FillArray(A, size);
		P_flag = 1;
		textcolor(LIGHTRED, BLACK);
		printArray(A, NOP, NOP, size);
		P_flag = 0;
		/////////////////////////////////////////////////////////////////////////////////////
		StartTime = chrono::system_clock::now(); //Information of current time
		Quicksort(A, 0, size - 1, NOP);
		EndTime = chrono::system_clock::now();
		excution = chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime);
		Info_Worst[Info_count2] = excution.count();
		Average1 += excution.count();
		/////////////////////////////////////////////////////////////////////////////////////
		cout << "--------------------------------" << endl;
		printArray(A, NOP, NOP, size);
		cout << "--------------------------------" << endl;
		cout << "Excution time: " << excution.count() << endl << endl << endl;
		Info_count = 0;

		FillArray(A, size);
		CreateBestcase(A, 0, size);
		P_flag = 1;
		textcolor(LIGHTRED, BLACK);
		printArray(A, NOP, NOP, size);
		P_flag = 0;
		/////////////////////////////////////////////////////////////////////////////////////
		StartTime = chrono::system_clock::now(); //Information of current time
		Quicksort(A, 0, size - 1, NOP);
		EndTime = chrono::system_clock::now();
		excution = chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime);
		Info_Best[Info_count2] = excution.count();
		Average2 += excution.count();
		/////////////////////////////////////////////////////////////////////////////////////
		cout << "--------------------------------" << endl;
		printArray(A, NOP, NOP, size);
		cout << "--------------------------------" << endl;
		cout << "Excution time: " << excution.count() << endl << endl << endl;
		Info_count = 0;

		InitializeArray(A, size);
		Create_array(A, size);
		P_flag = 1;
		textcolor(LIGHTRED, BLACK);
		printArray(A, NOP, NOP, size);
		P_flag = 0;
		/////////////////////////////////////////////////////////////////////////////////////
		StartTime = chrono::system_clock::now(); //Information of current time
		Random_Quicksort(A, 0, size - 1, NOP);
		EndTime = chrono::system_clock::now();
		excution = chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime);
		Info_Average[Info_count2] = excution.count();
		Average3 += excution.count();
		/////////////////////////////////////////////////////////////////////////////////////
		cout << "--------------------------------" << endl;
		printArray(A, NOP, NOP, size);
		cout << "--------------------------------" << endl;
		cout << "Excution time: " << excution.count() << endl << endl << endl;
		Info_count = 0;
		Info_count2++;

		delete[] A;
		Sleep(1000);
	}

	cout << "------------Worst Case------------" << endl;
	for (int a = 0; a < Info_count2; a++)
	{
		cout << a + 1 << ".";
		textcolor(YELLOW,BLACK);
		cout << Info_Worst[a] << "  ";
		if ((a + 1) % 5 == 0)
			cout << endl;
		textcolor(WHITE,BLACK);
	}
	cout << "Average: " << Average1/15<<endl;
	cout << "----------------------------------" << endl;

	cout << "------------Best Case-------------" << endl;
	for (int a = 0; a < Info_count2; a++)
	{
		cout << a + 1 << ".";
		textcolor(YELLOW, BLACK);
		cout << Info_Best[a] << "  ";
		if ((a + 1) % 5 == 0)
			cout << endl;
		textcolor(WHITE, BLACK);
	}
	cout << "Average: " << Average2/15<<endl;
	cout << "----------------------------------" << endl;

	cout << "-----------Average Case-----------" << endl;
	for (int a = 0; a < Info_count2; a++)
	{
		cout << a + 1 << ".";
		textcolor(YELLOW, BLACK);
		cout << Info_Average[a] << "  ";
		if ((a + 1) % 5 == 0)
			cout << endl;
		textcolor(WHITE, BLACK);
	}
	cout << "Average: " << Average3/15<<endl;
	cout << "----------------------------------" << endl;
	
	Info_count2 = 0;
	delete[] Info_Worst;
	delete[] Info_Best;
	delete[] Info_Average;

	return;
}

void InitializeArray(int Array[], int size)
{
	for (int i = 0; i < size; i++)
		Array[i] = 0;
}

void CreateBestcase(int Array[], int begin, int end)  //For creating Array of best case
{
	int count = end - begin;
	if (count < 3) //Check number of items
		return;

	int middle = begin + (count - 1) / 2; //select middle
	
	CreateBestcase(Array,begin,middle);
	swap(Array, begin, middle); //Swap first item and middle item
	CreateBestcase(Array,++middle,end);
}

void swap(int Array[], int i, int j)
{
	int tmp = Array[i];
	Array[i] = Array[j];
	Array[j] = tmp;
	return;
}

void FillArray(int Array[], int size)
{
	for (int i = 0; i < size; i++)
		Array[i] = i + 1;
	return;
}

void printArray(int A[], int p, int r, int size)
{
	if (p != NOP && r != NOP)
	{
		for (int i = 0; i < size; i++)
		{
			if (p == i)
				textcolor(BLACK, YELLOW);
			else if ((i > p) && (i == r || i < r))
				textcolor(LIGHTGREEN, DARKGRAY);
			else
				textcolor(WHITE, BLACK);

			cout << A[i] << " ";
		}
		textcolor(WHITE, BLACK);
	}

	else if (p != NOP && r == NOP)
	{
		for (int i = 0; i < size; i++)
		{
			if (p == i)
				textcolor(BLACK, YELLOW);
			else
				textcolor(WHITE, BLACK);

			cout << A[i] << " ";
		}
		textcolor(WHITE, BLACK);
	}

	else
	{
		for (int i = 0; i < size; i++)
		{
			if(P_flag==0)
				textcolor(LIGHTGREEN, BLACK);
			cout << A[i] << " ";
		}
		textcolor(WHITE, BLACK);
	}
	cout << endl;
}