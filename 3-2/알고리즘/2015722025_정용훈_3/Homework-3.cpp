#include<iostream>
#include<string>
#include<stdlib.h>
#include<windows.h>
#include<cmath>
using namespace std;

void Problem1(); //Each fuction of solution
void Problem2();
void Problem3();
int LCS_top_down(string x, string y, int m, int n); //Searching LCS method of top - down
int LCS_bottom_up(string x, string y, int m, int n); // " bottm - up
void print_LCS(string x, string y); //Function of printing string
void print_array(string x, string y, int *array[], int option); //For printing table
void textcolor(int foreground, int background);

#define LIGHTRED 12
#define LIGHTGREEN 10
#define DARKGRAY 8
#define YELLOW 14
#define WHITE 15
#define BLACK 0
#define NOP -100

int top_down_array[256][256] = { 0 };

class point //Information Node
{
public:
	int x=0;
	int y=0;
	point* next=NULL;
};

point* Head = NULL; //Information node head
point* Tail = NULL; // " tail

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
		cout << "1.Problem 1" << endl; //view of menu
		cout << "2.Problem 2" << endl;
		cout << "3.Problem 3" << endl;
		cout << "4.Exit Program" << endl;
		cout << "Select menu: ";
		cin >> button;

		switch (button)
		{
		case 1:
			Problem1(); //Function of problem 1
			break;
		case 2:
			Problem2(); //Function of problem 2
			break;
		case 3:
			Problem3(); //Function of problem 3
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

void Problem1() //The function about problem1
{
	string x = "ACFEDISKFJWCA"; //example string x
	string y = "KFUWNDKAJSKJ";  //example string y

	//print size of LCS and table
	cout << endl;
	cout << "Size of LCS is " << LCS_top_down(x, y, x.size()-1, y.size()-1) << endl;

	/////   For printing table   ///// 
	cout << "  ";
	textcolor(LIGHTGREEN, BLACK);
	for (int i = 0; i < x.size(); i++)
		cout << x[i] << " ";
	textcolor(WHITE, BLACK);

	cout << endl;
	for (int i = 0; i < y.size(); i++)
	{
		textcolor(LIGHTGREEN, BLACK);
		cout << y[i] << " ";
		textcolor(WHITE, BLACK);

		for (int j = 0; j < x.size(); j++)
			cout << top_down_array[i][j] << " ";
		cout << endl;
	}
	/////////////////////////////////////
	return;
}

void Problem2()
{
	string x = "ACFEDISKFJWCA"; //example string x
	string y = "KFUWNDKAJSKJ";  //example string y

	//print size of LCS and table
	cout << endl;
	cout << "Size of LCS is " << LCS_bottom_up(x, y, x.size(), y.size()) << endl;
}

void Problem3()
{
	string x = "ACFEDISKFJWCA"; //example string x
	string y = "KFUWNDKAJSKJ";  //example string y

	print_LCS(x, y); //print string of LCS
}

int LCS_top_down(string x, string y, int i, int j)
{
	if (i == -1 || j == -1) //For end working of function
		return 0;

	if (top_down_array[j][i] == 0) //checking visiting
	{
		if (x[i] == y[j]) //if text is equal
			top_down_array[j][i] = LCS_top_down(x, y, i - 1, j - 1) + 1;

		else if (x[i] != y[j]) //if text is not equal
			top_down_array[j][i] = //choose big value
			max(LCS_top_down(x, y, i, j - 1), LCS_top_down(x, y, i - 1, j));
	}
	return top_down_array[j][i]; //return size of LCS
}

int LCS_bottom_up(string x, string y, int i, int j)
{
	///////////////  Create space  ///////////////
	int** c = new int* [y.size()+1];
	for (int i = 0; i <= y.size(); i++)
		c[i] = new int[x.size()+1];
	/////////////////////////////////////////////

	////////    Fill table with value    ////////
	for (int i = 0; i <= y.size(); i++)
		for (int j = 0; j <= x.size(); j++)
		{
			if (i == 0 || j == 0) //Initialization
				c[i][j] = 0;
			else if (x[j-1] == y[i-1]) //If text is equal
				c[i][j] = c[i - 1][j - 1] + 1;
			else if (x[j-1] != y[i-1]) //If text is not equal
				c[i][j] = max(c[i - 1][j], c[i][j - 1]); //choose max
		}
	//////////////////////////////////////////////
	print_array(x,y,c,2);
	
	int ans = c[j][i]; //return size of LCS
	delete[] c; //delete table

	return ans;
}

void print_LCS(string x, string y)
{
	///////////////  Create space  ///////////////
	int** c = new int* [y.size() + 1];
	for (int i = 0; i <= y.size(); i++)
		c[i] = new int[x.size() + 1];
	//////////////////////////////////////////////

	/////////////    Create table    /////////////
	for (int i = 0; i <= y.size(); i++)
		for (int j = 0; j <= x.size(); j++)
		{
			if (i == 0 || j == 0) //Initialization
				c[i][j] = 0;
			else if (x[j - 1] == y[i - 1]) //If text is equal
				c[i][j] = c[i - 1][j - 1] + 1;
			else if (x[j - 1] != y[i - 1]) //If text is not equal
				c[i][j] = max(c[i - 1][j], c[i][j - 1]);
		}
	//////////////////////////////////////////////

	//////////    Searching String     //////////
	string LCS = "";
	int i = x.size();
	int j = y.size();

	while (i != 0 && j != 0)
	{
		////////   For save history of point   ////////
		point* newNode = new point;
		if (Head == NULL) //check head of list
		{
			Head = newNode; //Initialization
			Tail = newNode;
		}
		
		else //push back to list
		{
			Tail->next = newNode; //link
			Tail = newNode; //move pointer of tail
		}
		//////////////////////////////////////////////

		if (y[j - 1] == x[i - 1]) //If text is equal
		{
			LCS = LCS + y[j - 1];  //Save text to space
			newNode->x = i; //Save history for printing
			newNode->y = j;
			j -= 1; //Move point
			i -= 1;
		}
		else if (y[j - 1] != x[i - 1])//If text is not equal
		{
			newNode->x = i; //Save history for printing
			newNode->y = j;
			if (c[j - 1][i] >= c[j][i - 1]) //Move point
				j -= 1;

			else if (c[j - 1][i] < c[j][i - 1])
				i -= 1;
		}
	}
	//////////////////////////////////////////////
	cout << "----View of LCS----" << endl;
	print_array(x, y, c, 3);
	cout << "-------------------" << endl;
	reverse(LCS.begin(), LCS.end());
	cout << "LCS is --> " << LCS << endl;
	//////////////////////////////////////////////

	delete[] c;
	return;
}

void print_array(string x, string y, int* array[], int option)
{
	if (option == 3) 
		goto label;
	cout << "    "; //Problem 2 printing
	textcolor(LIGHTGREEN, BLACK);
	for (int i = 0; i < x.size(); i++)
		cout << x[i] << " ";
	textcolor(WHITE, BLACK);

	cout << endl;

	for (int i = 0; i < y.size()+1; i++)
	{
		textcolor(LIGHTGREEN, BLACK);
		if (i != 0) cout << y[i - 1] << " ";
		else cout << "  ";
		textcolor(WHITE, BLACK);

		for (int j = 0; j < x.size()+1; j++)
			cout << array[i][j] << " ";
		cout << endl;
	}
	return;

label: //Problem 3 printing
	cout << "    ";
	textcolor(LIGHTGREEN, BLACK);
	for (int i = 0; i < x.size(); i++)
		cout << x[i] << " ";
	textcolor(WHITE, BLACK);

	cout << endl;

	for (int i = 0; i < y.size() + 1; i++)
	{
		textcolor(LIGHTGREEN, BLACK);
		if (i != 0) cout << y[i - 1] << " ";
		else cout << "  ";
		textcolor(WHITE, BLACK);

		for (int j = 0; j < x.size() + 1; j++)
		{
			for (point* tmp = Head; tmp; tmp = tmp->next)
			{
				if ((tmp->x == j && tmp->y == i) && (x[j-1]==y[i-1]))
					textcolor(LIGHTRED, BLACK);
				else if(tmp->x == j && tmp->y == i) 
					textcolor(YELLOW, BLACK);
				
			}
			cout << array[i][j] << " ";
			textcolor(WHITE, BLACK);
		}
		cout << endl;
	}
	return;
}

void textcolor(int foreground, int background) //For change text color of console
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}