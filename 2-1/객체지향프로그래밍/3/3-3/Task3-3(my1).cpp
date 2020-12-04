#include <fstream> //For use File I/O function
#include "AlphaList.h"

void load(AlphaList &aList, const char* fname)
{
	char word[255] = { NULL }; //Declare char that Save word
	char alpha[2] = { NULL }; //Declare char that Save alphabet
	ifstream fin(fname); //Declare fin and open file

	for (alpha[0] = 97; alpha[0]<123; alpha[0]++) //This function links the alphabet a to z
		aList.alphainsert(alpha); //insert function

	while (fin.getline(word, sizeof(word))) //This function links the word that load from txt file
		aList.insert(word); //insert function

	fin.close(); //close the file
}

int main()
{
	AlphaList aList; //Declare aList for working

	load(aList, "input.txt"); //practice the load function that have two variable

	aList.show(); //Show all List

	return 0;
}
