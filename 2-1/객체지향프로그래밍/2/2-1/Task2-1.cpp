#include<iostream> //Declare iostream function
#include<fstream> //Declare fstream for File
#include<string> //Declare string function

using namespace std; //Declare using namespace std

void shiftfunction(char*str1, int& a); //Declare shiftfunction that contain 2 variable

void caesarEncryption(ifstream& inFile, ofstream& outFile, int nCaesar)
{ //Declare caesarEncryption function that contain 2 File variable 1 integer variable
	int i = 0; //Delcare integer i and save 0 to i
	char str1[1000] = { NULL }; //Declare char str1, save NULL to str1

	cout << endl << "---------------- out put ----------------" << endl;
	//cout "---------------- out put ----------------"
	while (!inFile.eof()) //Repeat the function until the file is finished.
	{
		inFile.getline(str1, sizeof(str1)); //Save information of File to str1
		shiftfunction(str1, nCaesar); //Practice a function that contain 2 variable
		outFile << str1 << endl; //Send the information of str1 to File
		cout << str1 << endl; //Print str1
	}
}

void shiftfunction(char*str1, int& a) //Declare function that contain 2 variable
{
	for (int i = 0; str1[i] != NULL; i++) /*Declare i and save 0 to i, Repeat function if str1[i] is not NULL
										  and the function end once, update i+1*/
	{
		if (97 <= str1[i] && str1[i] <= 122) //If (str1[i] equal or bigger than 97) and (strr1[i] equal or smaller than 122) practice the function
		{
			if (str1[i] + a <= 122) //If str1[i] + a equal or smaller than 122 practice the function
			{
				str1[i] = str1[i] + a; //Save str1[i] + a to str1[i]
			}
			else //Condition is not satiesfied practice this function
				str1[i] = str1[i] - 26 + a; //Save str1[i]-26+a to str1[i]
		}

		if (65 <= str1[i] && str1[i] <= 90) //If (str1[i] equal or bigger than 65) and (str1[i] equal or smaller than 90) practic the function
		{
			if (str1[i] + a <= 90) //If str1[i] + a equal or smaller than 90 practice the function
			{
				str1[i] = str1[i] + a; //Save str1[i] + a to str1[i]
			}
			else //Condition is not satiesfied practice this function
				str1[i] = str1[i] - 26 + a; //Save str1[i] - 26 + a to str1[i]
		}

		if (32 <= str1[i] && str1[i] <= 57) //If (str1[i] equal or bigger than 32) and (str1[i] equal or smaller than 57) practic the function
		{
			if (str1[i] + a <= 57) //If str1[i] + a equal or smaller than 57 practice the function
			{
				str1[i] = str1[i] + a; //Save str1[i] + a to str1[i]
			}
			else //Condition is not satiesfied practice this function
				str1[i] = str1[i] - 26 + a; //Save str1[i] -26 + a to str1[i]
		}
	}
}

int main() //Declare main function
{
	int a = 0; //Declare intger variable a and save 0 to a

	string strFileName = "Diary_15yearsOld"; //Declare string variable strFileName and Save the string"Diary_15yearsOld"
	string strFileFormat = ".txt"; //Declare string variable strFileFormat and Save the string".txt"

	ifstream inFile(strFileName + strFileFormat); //Open the File and load information of the File
	ofstream outFile(strFileName + "_encryption" + strFileFormat); //Open the File that we will use for save information

	if (!inFile.is_open() || !outFile.is_open()) //Function to check if a file is opened successfully
	{
		cout << "file is not opened" << endl; //Print "file is not opened"
	}

	cout << "Input the Shift number : "; //Print "Input the Shift number : "
	cin >> a; //Get infomation of a

	while (a < 0 || a > 26) //If (a is smaller than 0) and (a is bigger than 26) Repeat the function
	{
		cout << "Input the Shift nuber again : "; //Print "Input the Shift nuber again : "
		cin >> a; //Get infomation of a
	}
	caesarEncryption(inFile, outFile, a); //Practice caesarEncryption function that contain 3 variabel

	inFile.close(); //Close the File of inFile
	outFile.close(); //Close the File of out File

	return 0; //return 0 and end the main function
}