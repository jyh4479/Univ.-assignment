#include<iostream> //Declare iostream
using namespace std; //Declare using namespace std;

class Encode //Declare class, name is Encode
{
private: //That's mean is "The variable is only used in class!"
	char word[255] = { NULL }; //Declare char variable
	char buffer[255] = { NULL }; //Declare char variable

public: //That's mean is "The variable is used every where"
	Encode();
	~Encode();

	void inputWord(); //Declare void function in class
	char* getBuf(); //Declare char* function in class
	void printEncResult(void); //Declare void function in class
	int encodeWord(void); //Declare int function in class

};


