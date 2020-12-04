#include<iostream> //Declare iostream
#include"Encode.h" //Declare "Encode.h"
#include"Decode.h" //Declare "Decode.h"
using namespace std; //Delcare using namespace std;

int main() //Star main function
{
	Encode encode; //Declare Encode variable

	encode.inputWord(); //practice the function of class encode.inputWord()
	encode.encodeWord(); //practice the function of class encode.encodeWord()
	encode.printEncResult(); //practice the function of class encode.printEncResult()

	cout << endl; //Print "endl"

	Decode decode; //Declare Decode variable

	decode.setBuf(encode.getBuf()); //practice the function of class decode.setBuf(char* variable)
	decode.decodebin(); //practice the function of class decode.decodebin()
	decode.printWord(); //practice the function of class decode.printWord()

	return 0; //return 0 and end of main function
}