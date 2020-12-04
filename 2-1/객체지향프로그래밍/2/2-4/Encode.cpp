#include "Encode.h" //Declare "Encode.h"

Encode::Encode()
{
}
Encode::~Encode()
{
}

void Encode::inputWord() //Declare void function that in class Encode
{
	int sum = 0; //Declare integer variable
	cout << "Input word : "; //Print "Input word"
	cin >> word; //Get the information from key board and Save to word

	for (int i = 0; word[i]; i++) /*Declare i and save 0 to i, If word[i] is not end repeat the function
								  and update i + 1 */
	{
		if (word[i] > 122 || word[i] < 97) //If word[i] is bigger than 122 or is smaller than 97, practice the function
		{
			cout << "We accept only lowercase letters!" << endl; //Print "We accept only lowercase letters!"
			cout << "Input word again! : "; //Print "Input word again! : "
			cin >> word; //Get the information from key board and Save to word
		}
	}

	while (1) //Repeat the function untill practice the break
	{
		for (int i = 0; word[i]; i++) /*Declare i and save 0 to i, If word[i] is not end repeat the function
								  and update i + 1 */
		{
			if (word[i] != 'z') //If word[i] is not 'z' practice th funtion
				sum += (word[i] - 96); //Save sum + word[i]-96 to sum
			else if (word[i] == 'z') //If word[i] is 'z' practice th funtion
				sum += 25; //Save sum + 25 to sum
		}

		if (sum < 255) //If sum < 255 practice the break
			break;

		if (sum >= 255) //If sum >= 255 practice the function
		{
			cout << "The bitstream range is over!" << endl; //Print "The bitstream range is over!"
			cout << "Input word again! : "; //Print "Input word again! : "
			cin >> word; //Get the information from key board and Save to word
		}
		sum = 0; //Save 0 to sum
	}
}

void Encode::printEncResult() //Declare void function that in class Encode
{
	cout << "---Encoding result---" << endl; //Print  "---Encoding result---"
	cout << buffer << endl; //Print infomation of buffer
}

char* Encode::getBuf() //Declare char* function that in class Encode
{
	strcpy_s(word, buffer); //Save string buffer to word
	return word; //return string of word
}

int Encode::encodeWord() //Declare int function that in class Encode
{
	int i = 0, j = 0, count = 0; //Declare integer variable and Save 0 

	for (; word[i] != NULL; i++) //If word[i] is not NULL repeat the function and update i+1
	{
		if (word[i] == 'z') //If word[i] is 'z', practice the function
		{
	
			for (count = 0; count != 25; count++, j++) //Save 0 to count, If count is not 25, repeat the function and update value
				buffer[j] = '0'; //Save '0' to buffer[j]
		}

		if (word[i] != 'z') //If word[i] is not 'z', practice the function
		{
			for (; word[i] - 97 >= 0; word[i] -= 1, j++) //If word[i]-97 is equal or bigger than 0, repeat the function and update value
			{

				if (word[i] - 97 == 0 && word[i] != 26) //If word[i] - 97 == 0 and word[i] is not 26, practice the function
				{
					buffer[j] = '1'; //Save '1' to buffer[j]
				}
				else //The condition is not satiesfied othger condition, practice the function
				{
					buffer[j] = '0'; //Save '0' to buffer[j]
				}
			}
		}
	}
	cout << endl; //Print "endl"
	return 0; //return 0
}
