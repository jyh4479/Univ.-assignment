#include<iostream> //Declare iostream
using namespace std; //Declare using namespace std 

void candle(int& a, int& b, int& count) //Declare the function that contain 3 integer variable
{
	if (a == b) //"If a is b" increase 1 to count
		count++;

	else if (a > b) //"Else if a is bigger than b" practice function
	{
		count = 1; //Save 1 to count
		b = a; //Save a to b
	}
}

void agefunction(int& age) //Declare the function that contain variable of integer
{
	cout << "Messi's age: "; //Print "Messi's age: "
	cin >> age; //Enter the value to age

	while (age < 1 || age>100000) //"If age is smaller than 1 or age is bigger than 100000 repeat the function
	{
		cout << "Age is entered too many or too low" << endl; //Print "Age is entered too many or too low"
		cout << "Please enter the age again : "; //Print "Please enter the age again : "
		cin >> age; //Enter the value to age
	}
}

void candleheight(int& age, int& a, int& b, int& count) //Declare the function that contain 4 variable of integer
{
	cout << "Heights of candles : "; //Print "Heights of candles: "
	while (age > 0) //"If age is bigger than 0" practice function and the function end once decrease 1 to age
	{
		cin >> a; //Enter the value to a
		if (a < 1 || a>1000) //"If a is smaller than 1 or a is bigger than 1000" practice the function
		{
			cout << "The height of the candle is either too high or too low." << endl; //Print "The height of the candle is either too high or too low."
			cout << "Please other number of height of candle : ";
			continue; //Declare continue
		}
		age--; //Decrease 1 of age
		candle(a, b, count); //Practice the function of contain integer that a,b,count
	}
}

int main() //Declare main function
{
	int age = 0, a = 0, b = 0, count = 1; //Dclare integer variable

	agefunction(age); //Practice the agefunction

	candleheight(age, a, b, count); //Practice the candleheight

	cout << "The number of candles that Messi blows out is " << count << endl; //Print "The number of candles that Messi blows out is "

	return 0; //Return 0 and Declare end of function
}