#include<iostream> //Declare iostream
using namespace std; //Declare using namespace std 

int main() //Declare main function
{
	int end = 0, sum = 0, b=0, i = 1; //Declare integer variable for calculation

	cout << "Max range value n : "; //Print "Max range calue n : "
	cin >> end; //Enter the variable of end
	cout << endl; //Print '\n'
	for (int a = 1; a <= end; a++) //Declare integer a and save 1, "if a is smaller than end of equal" repeat the function
	{
		while (i<a) //"If i is smaller than a" repeat the function
		{
			if (a%i == 0) //"If a/i remainder is 0" practice the function
				sum = sum + i; //Save sum+i to sum
			i++; //Increase 1 to i
		}

		if (sum == a) //"If sum is a" practice the function
		{
			cout << i <<" = "; //Print variable and " = "
			
			b = 1; //Save 1 to b
			
			while(1) //Repeat the function until break
			{
				if (i%b == 0 && b != i) //"If i/b remainder and b is not i" preactice the function
				{
					cout << b; //Print variabel b
					if (b != i/2) //"If b is not i/2 practice the function
						cout << " + "; //Print " + "
				}
				if (b == i/2) //"If b is i/2 practice the function
					break; //End the function

				b++; //Increase 1 to b
			}
			cout << endl; //Print '\n'
		}
		sum = 0, i = 1; //Save 0 to sum and 1 to i
	}
	return 0; //return 0 and declare ending function
}





			



		