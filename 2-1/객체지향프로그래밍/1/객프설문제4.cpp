#include<iostream> //Dclare iostream

using namespace std; //Declare using namespace std 

int CalcLength(const char* str); //Declare integer function contain const char* str

bool InsertString(char* str1, char* str2, int n) /*The function of return bool variable
												 has 2 char* variable 1 integer variable*/
{
	char substr[512] = { NULL }; //Declare variable of character and save NULL to substr
	int a = 0, b = 0, c = 0; //Declare variable of integer and save 0 to variable
	int sub_n = n; //Declare variable and save n to sub_n

	if (CalcLength(str1) < n) //"If variable of CalcLength function is smaller than n" practice the function
		return 0; //Declare end of function

	for (; str1[n] != NULL;) //"If str1[n] is not NULL" repeat the function
	{
		substr[a++] = str1[n++]; //Save the string of str1 to substr
	}

	n = sub_n; //Save sub_n to n

	for (; str2[b] != NULL;) //"If str2[b] is not NULL" repeat the function
	{
		str1[n++] = str2[b++]; //Save the string of str2 to str1
	}

	for (; substr[c] != NULL;) //"If substr[c] is not NULL" repeat the function
	{
		str1[n++] = substr[c++]; //Save th string of substr to str1
	}
	cout <<"str1 : "<< str1 << endl; //Print str1 and '\n'
	return 1; //Return 1 and declare end of function
}

int CalcLength(const char* str) //Declare integer function contain const char* str
{
	int len = 0; //Declare integer len, save 0 to len
	for (; str[len] != NULL; len++); //"If str[len] is not NULL" repeat the function, Increase 1 to len
	return len; //Return variable of len
}

int main() //Declare main function
{
	char str1[512] = { NULL }, str2[512] = { NULL }; /*Declare variable of character str1,str2
													 and save NULL to str1,str2*/
	int n = 0; //Declare intger n, save 0 to n
		
	cout << "str1 : "; //Print "str1 : "
	cin.getline(str1, sizeof(str1)); //Enter the string of str1
	cout << "str2 : "; //Print "str2 : "
	cin.getline(str2, sizeof(str2)); //Enter the string of str2
	cout << "n : "; //Print "n : "
	cin >> n; //Enter the n of integer

	while (InsertString(str1, str2, n) != 1) //"If variable of function is not 1" repeat the function
	{
		cout << "n is too big! please the other number!" << endl; //Print "n is too big! please the other number!" and '\n'
		cout << "n : "; //Print "n : "
		cin >> n; //Enter the n
	}
} //End of main function


