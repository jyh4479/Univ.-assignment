#include<iostream> //Declare iostream
using namespace std; //Declare using namespace std 

int main() //Declare main function
{
	int a = 0, b = 0, count = 0, max = 0, min = 0, sum = 0, average = 0; //Declare the intger variable that need for calculation
	cout << "Input : "; //Print "Input : "
	cin >> a; //Enter the variable a from keyboard
	sum = a; //Save a to sum
	max = a; //Save a to max
	min = a; //Save a to min
	cout << "Collatz conjecture : "; //Print "Collatz conjecture : "

	cout << a; //Print varialbe a

	while (a != 1) //"if a not 1" repeat the function
	{
		cout << " -> "; //Print " -> "
		if (a % 2 == 0) //"if a/2 remainder is 0" practice the function
		{
			a = a / 2; //Save a/2 to a
			cout << a; //Print variable a 
			sum += a; //Save sum+a to sum

			if (a < min) //"if a is smaller than min" practice the function
				min = a; //Save a to min
		}

		else //Any condition satisfied, practice the function
		{
			a = 3 * a + 1; //Save 3*a+1 to a
			cout << a; //Print variable a
			sum += a; //Save sum+a to sum

			if (a > max) //"if a is larger than max" practice the function
				max = a; //Save a to max
		}
		count++; //Increase 1 to A

	
	} //End the function of repeat

	cout << endl; //Print '\n'
	cout << "count : " << count; //Print "count : " and variable count
	average = sum / (count+1); //Save the variable of sum/count+1 to average
	cout << endl; //Print '\n'
	cout << "max : " << max; //Print "max : "
	cout << endl; //Print '\n'
	cout << "min : " << min; //Print "min : "
	cout << endl; //Print '\n'
	cout << "sum : " << sum; //Print "sum : "
	cout << endl; //Print '\n'
	cout << "average : " << average; //Print "average : "
	cout << endl; //Print '\n'
	
	return 0; //Return 0 and Declare the function
} //End the main function
