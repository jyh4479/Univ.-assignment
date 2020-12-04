#include<iostream> //Declare iostream
using namespace std; //Delcare using namespace std

void militaryTimeAdd(int& pHour, int& pMin, int& pSec, int addHour, int addMin, int addSec)
{ //Declare the function that contain 6 integer variable
	if (pSec + addSec >= 60) //If (pSec + addSec) equal or bigger than 60 practice the function
	{
		pMin = pMin + (pSec + addSec) / 60; //Save pMin + (pSec + addSec) / 60 to pMin
		pSec = (pSec + addSec) % 60; //Save (pSec + addSec) % 60 to pSec
	}
	else if (pSec + addSec < 60) //If (pSec + addSec) smaller than 60 practice the function
		pSec = pSec + addSec; //Save (pSec + addSec) to pSec

	if (pMin + addMin >= 60) //If (pMin + addMin) equal or bigger than 60 practice the function
	{
		pHour = pHour + (pMin + addMin) / 60; //Save pHour + (pMin + addMin) / 60 to pHour
		pMin = (pMin + addMin) % 60; //Save (pMin + addMin) % 60 to pMin
	}
	else if (pMin + addMin < 60) //If (pMin + addMin) is smaller than 60 practice the function
		pMin = pMin + addMin; //Save (pMin + addMin) to pMin

	pHour = (pHour + addHour) % 24; //Save (pHour + addHour) % 24 to Hour
}

int main() //Declare main function
{
	int pHour, pMin, pSec; //Declar integer variable
	int addHour, addMin, addSec; //Declar integer variable

	cout << "Input time" << endl; //Print "Input time"
	cout << "Hour : "; //Print "Hour : "
	cin >> pHour; //Get infomation of pHour

	while (pHour < 0 || pHour > 23) //If pHour < 0 or pHour > 29 repeat the function
	{
		cout << "Input again!" << endl; //Print "Input again!"
		cout << "Hour : "; //Print "Hour : "
		cin >> pHour; //Get information of pHour
	}

	cout << "Minute : "; //Print "Minute : "
	cin >> pMin; //Get information of pMin

	while (pMin < 0 || pMin > 59) //If pMin < 0 or pMin > 59 repeat the function
	{
		cout << "Input again!" << endl; //Print "Input again!"
		cout << "Minute : "; //Print "Minute : "
		cin >> pMin; //Get information of pMin
	}

	cout << "Seconds : "; //Print "Seconds : "
	cin >> pSec; //Get information of pSec

	while (pSec < 0 || pSec > 59) //If pSec < 0 or pSec > 59 repeat the function
	{
		cout << "Input again!" << endl; //Print "Input again!"
		cout << "Seconds : "; //Print "Seconds : "
		cin >> pSec; //Get information of pSec
	}

	cout << "Input time" << endl; //Print "Input time"
	cout << "h: " << pHour << " m: " << pMin << " s: " << pSec << endl; //Print information of time
	
	cout << "Add time" << endl; //Print "Add time"
	cout << "Hour : "; //Print "Hour : "
	cin >> addHour; //Get information of addHour

	while (addHour < 0 || addHour>1000000) //If addHour < 0 or addHour > 1000000 Repeat the function
	{
		cout << "Input again!" << endl; //Print "Input again"
		cout << "Hour : "; //Print "Hour : "
		cin >> addHour; //Get information of addHour
	}
	cout << "Minute : "; //Print "Minute : "
	cin >> addMin; //Get information of addMin

	while (addMin < 0 || addMin>1000000) //If addMin < 0 or addMin > 1000000 Repeat the function
	{
		cout << "Input again!" << endl; //Print "Input again"
		cout << "Minute : "; //Print "Minute : "
		cin >> addMin; //Get information of addMin
	}

	cout << "Seconds : "; //Print "Seconds : "
	cin >> addSec; //Get information of addSec

	while (addSec < 0 || addSec>1000000) //If addSec < 0 or addSec > 1000000 Repeat the function
	{
		cout << "Input again!" << endl; //Print "Input again"
		cout << "Seconds : "; //Print "Seconds : "
		cin >> addSec; //Get information of addSec
	}

	militaryTimeAdd(pHour, pMin, pSec, addHour, addMin, addSec); //Practice the militaryTimeAdd function

	cout << "Output time" << endl; //Print "Output time"
	cout << "h: " << pHour << " m: " << pMin << " s: " << pSec << endl; //Print information of time

	return 0; //return 0 and end of main function
}