//////////////////////////////////////////////////////////////////////
//File Name         :simple_ls.c                                    //
//Date              :2019/03/31                                     //
//Os                :Ubuntu 16.04 LTS 64bits                        //
//Author            :Jeong yong hoon                                //
//Student ID        :2015722025                                     //
//------------------------------------------------------------------//
//Title : System Programing Assignment #2-1 (simple_ls)             //
//Description : The tasj is to implement 'ls', which prints only    //
//		the file name. Existing ls and function are almost  //
//		the same then note that the names of files are      //
//		sorted in alphabetical order, and hidden files are  //
//		also displayed if no exception is made. It also     //
//		prints an error if you receive more than one        //
//		argument and you receive a non-directory file as    //
//		an argument.                                        //
//////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>

//////////////////////////////////////////////////////////////////////
// For comparing string                                             //
// ================================================================ //
// Input: char* -> String from main function                        //
//        char* -> String from main function                        //
//                                                                  //
// Output: int 1 String A is bigger than B                          //
//            -1 String B is bigger than A                          //
//             0 Sitrng String A is equal to B                      //
//                                                                  //
// Purpose: To compare case-insensitively                           //
//////////////////////////////////////////////////////////////////////
int mystrcmp(char* C, char* D) //The function for comapring string
{
	char* A = (char*)malloc(sizeof(int) * 300); //declare array
	char* B = (char*)malloc(sizeof(int) * 300);
	strcpy(A, C); //copy content of string
	strcpy(B, D);
	for (int i = 0; A[i] != 0; i++) //change case of letters
	{
		if (A[i]<97)
			A[i] = A[i] + 32;
	}

	for (int i = 0; B[i] != 0; i++) //change case of letters
	{
		if (B[i]<97)
			B[i] = B[i] + 32;
	}

	if (strcmp(A, B)>0) //if A is bigger than B
		return 1; //return 1
	else if (strcmp(A, B)<0) //if B is bigger than A
		return -1; //return -1
	else
		return 0; //return 0
}

//////////////////////////////////////////////////////////////////////
// For sorting vector                                               //
// ================================================================ //
// Input: char** -> The vector for sorting                          //
//        int -> Value of vector's height                           //
//                                                                  //
// Output: void                                                     //
//                                                                  //
// Purpose: To sort vector                                          //
//////////////////////////////////////////////////////////////////////
void sorting(char**A, int height) //The function for sorting vector
{
	char* tmp = (char*)malloc(sizeof(int) * 300); //declare tmp for swap

	for (int i = 1; i < height - 1; i++) //buble sort
	{
		for (int j = 1; j < height - 1 - i; j++)
		{

			if (mystrcmp(A[j], A[j + 1]) > 0) //If A[j] is bigger than A[j+1] 
			{//practice swap
				strcpy(tmp, A[j]);
				strcpy(A[j], A[j + 1]);
				strcpy(A[j + 1], tmp);
			}
		}
	}
	free(tmp);
}

//////////////////////////////////////////////////////////////////////
// For checking exception                                           //
// ================================================================ //
// Input: char** -> The name for reading file                       //
//        int -> The count of parameter                             //
//        DIR* -> For checking file is opened or not                //
//                                                                  //
// Output: int 0 End program success                                //
//             1 Occur exception                                    //
//                                                                  //
// Purpose: For checking exception from main function               //
//////////////////////////////////////////////////////////////////////
int exception(int argc, char** argv, DIR* dirp) //for checking exception
{
	struct dirent *dir;
	struct stat buf;

	if (argc>2) //If the parameter count is bigger than 2
	{
		printf("simple_ls: only one directory path can be processed\n"); //print error
		return 1; //return 1
	}

	if (argc == 2) //If the parameter count is 2
	{
		if (dirp == NULL) //If file is not opned
		{

			if (lstat(argv[1], &buf)<0) //Read file, if file is not read then print error
			{
				printf("simple_ls: cannot access '%s' : No such directory\n", argv[1]);
				return 1; //return 1
			}

			if (!S_ISDIR(buf.st_mode)) //Checking type of file, if file is not directory then print error
			{
				printf("simple_ls: cannot access '%s' : No such directory\n", argv[1]);
				return 1; //return 1
			}
		}

	}
	return 0; //return 0
}

//////////////////////////////////////////////////////////////////////
// Main function                                                    //
// ================================================================ //
// Input: int -> argument count                                     //
//        char** -> argument vector                                 //
//                                                                  //
// Output: int 0 End program success                                //
//                                                                  //
// Purpose: Control all working                                     //
//////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	DIR *dirp;
	DIR *checking;

	struct dirent *dir;
	int height = 2;

	/////////////////////////////open file////////////////////////////
	if (argc > 1)
		dirp = opendir(argv[1]);
	else
		dirp = opendir(".");

	if (exception(argc, argv, dirp)) //check exception
		return 0;
	/////////////////////////////////////////////////////////////////

	//////////////// //save word to other array/////////////////////
	rewinddir(dirp);//move pointer to starting point

	char **A = (char**)malloc(sizeof(char*)*height);
	do
	{
		dir = readdir(dirp);
		if (dir == NULL) //check NULL
			break; //stop repeat function

		A[height - 1] = (char*)malloc(sizeof(char)*strlen(dir->d_name) + 1);
		strcpy(A[height - 1], dir->d_name);

		height++;
		A = (char**)realloc(A, sizeof(char*)*height);
	} while (1);
	////////////////////////////////////////////////////////////////

	sorting(A, height); //sorting function

	////////////////////Print content of vector////////////////////
	for (int i = 1; i < height - 1; i++)
	{
		if (A[i][0] != '.') //check dot of file name
			printf("%s\n", A[i]);
	}
	////////////////////////////////////////////////////////////////
	return 0;
}
