#include<iostream> //Declare iostream
using namespace std; //Declare using namespace std 

void DrawingStar(char* a, int& b) //Declare the function that contain character,integer variabel
{
	for (int line = 0; b > line-1 ; line++) /*Declare and Save 0 to line, "if b is bigger than line-1" repeat the function
											 and end the function once, increase 1 to line*/
	{
		for (int blank = 0; blank < 3 * b - line; blank++) /*Declare and Save 0 to blank, "if blank is smaller than 3*b-line" repeat the function
														   and end the function once, increase 1 to blank*/
			cout << " "; //Print " "

		for (int mark = 0; mark < line; mark++) /*Declare and Save 0 to mark, "if mark is smaller than line repeat the function
												and end the function once, increase 1 to mark*/
			cout << a << " "; //Print "a"," "

		cout << endl; //Print "\n"
	}

	for (int line2 = 0; b > line2; line2++) /*Declare and Save 0 to line2, "if b is bigger than line2" repeat the function
											and end the function once, increase 1 to line2*/
	{
		for (int blank2 = 0; blank2 < line2; blank2++) /*Declare and Save 0 to blank2, "if blank2 is smaller than line2" repeat the function
													   and end the function once, increase 1 to blank2*/
			cout << " "; //Print " "
		for (int mark2 = 0; mark2 < 3 * b - line2; mark2++) /*Declare and Save 0 to mark, "if mar is smaller than 3*b-line2" repeat the function
															and end the function once, increase 1 to mark2*/
			cout << a << " "; //Print "a"," "

		cout << endl; //Print "\n"
	}

	for (int line3 = 0; b > line3; line3++) /*Declare and Save 0 to line3, "if b is bigger than line3" repeat the function
											and end the function once, increase 1 to line3*/
	{
		for (int blank3 = 0; blank3 < b - 1; blank3++) /*Declare and Save 0 to blank3, "if blank3 is smaller than b-1" repeat the function
													   and end the function once, increase 1 to blank3*/
			cout << " "; //Print " "

		for (int mark3 = 0; mark3 < b - line3; mark3++) /*Declare and Save to mark3, "if mark3 is smaller than b-line3" repeat the function
														and end the function once, increase 1 to mark3*/
			cout << a << " "; //Print "a"," "

		for (int blank4 = 1; blank4 < 4 * line3+2; blank4++) /*Declare and Save to blank4, "if blank4 is smaller than 4*line3+2" repeat the function
															   and end the function once, increase 1 to blank4*/
			cout << " "; //Print " "

		for (int mark4 = 0; mark4 < b - line3; mark4++) /*Declare and Save to mark4, "if mark4 is smaller than b-line3" repeat the function
														and end the function once, increase 1 to mark4*/
			cout << a << " "; //Print "a"," "

		cout << endl; //Print "\n"
	}
}

int main() //Declare main function
{
	char a[2]; int b = 0; //Declare variable of character, integer

	cout << "In put your mark : "; //Print "In put your mark : "
	cin >> a; //Get an a
	cout << "Input N : "; //Print "Input N : "
	cin >> b; //Get a b

	while (b > 11 || b < 3) //"If b is bigger than 11 or is smaller than 3", repeat the function
	{
		cout << b << " is not odd integer in 3~11" << endl; //Print "b is not odd integer in 3~11 \n"
		cout << "please enter the other integer : "; //Print "please enter the other integer : "
		cin >> b; //Print "b"
	}
	while (b%2==0) //"Remain the b/2 is 0", repeat the function
	{
		cout << b << " is not odd integer in 3~11" << endl; //Print "b is not odd integer in 3~11 \n"
		cout << "please enter the other integer : "; //Print "please enter the other integer : "
		cin >> b; //Print "b"
	}

	cout << "Output : "; //Print "Output : "

	DrawingStar(a, b); //Call the function of DrawingStar

	return 0; //Return 0 and declare end of main function
}