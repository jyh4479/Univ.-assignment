#include<iostream> //Declare iostream
using namespace std; //Declare using namespace std;

class Decode //Declare class, name is Decode
{
private: //That's mean is "The variable is only used in class!"
	char word[255] = { NULL }; //Declare char variable
	char buffer[255] = { NULL }; //Declare char variable

public: //That's mean is "The variable is used every where"
	Decode();
	~Decode();

	void setBuf(char * buf); //Declare void function in class
	void printWord();  //Declare void function in class
	int decodebin(void);  //Declare int function in class
};

