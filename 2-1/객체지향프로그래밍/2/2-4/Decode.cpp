#include "Decode.h" //Declare "Decode.h"

Decode::Decode()
{
}
Decode::~Decode()
{
}

void Decode::printWord() //Declare void function that in class Decode
{
	cout << "---Decoding result---" << endl; //Print "---Decoding result---"
	cout << buffer << endl; //Print "buffer"
}

void Decode::setBuf(char* buf) //Declare void function that in class Decode
{
	strcpy_s(word, buf); //Save buf string to word
}

int Decode::decodebin(void) //Declare int function that in class Decode
{
	int i = 0, j = 0, k = 0, count = 1; //Declare integer variable

	for (;word[i] != NULL; i++) //If word[i] is not NULL, repeat the function and update i + 1
	{

		if (word[i] == '1') //If word[i] = '1', practice the function
		{
			buffer[j] = (97 + k); //Save 97 + k to buffer[j]
			j++, k = 0, count = 1; //Save j+1 to j , save 0 to k , save 1 to count
			continue; //Declare continue
		}

		else if (count % 25 == 0) //If count % 25 == 0, practice the function
		{
			buffer[j] = 'z'; //Save 'z' to buffer[j]
			j++, k = 0, count = 1; //Save j+1 to j , save 0 to k , save 1 to count
			continue; //Declare continue
		}
		k++, count++; //Save k+1 to k , save count + 1 to count
	}
	return 0; //return 0
}
