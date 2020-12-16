//////////////////////////////////////////////////////////////////////
//File Name         :spls_advanced.c                                //
//Date              :2019/03/31                                     //
//Os                :Ubuntu 16.04 LTS 64bits                        //
//Author            :Jeong yong hoon                                //
//Student ID        :2015722025                                     //
//------------------------------------------------------------------//
//Title : System Programing Assignment #2-2 (Advanced ls)           //
//Description : The task is to add an option after implementing ls. //
//              The operation is implemented by adding -l and -a of //
//              ls, and has a special feature that the option       //
//              must be executed regardless of the order of options.//
//              To accomplish this task, you can use the lstat      //
//              function to read the file, then use various         //
//              functions to print the file information, and use    //
//              the getopt function to control the options.         //
//////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<sys/stat.h>
#include<time.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<unistd.h>
#include<strings.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node //The struct for linked list
{
	char filename[256]; //information
	struct Node *next; //next
	struct Node *prev; //prev
}Node;

Node *Head = NULL; //Head of linked list
Node *Tail = NULL; //Tail of linked list

void Nodeinsert(char* fname);
void printlist(int flagA, int flagL, int total);
void deletelist();
int checkstring(char* str);
void Eliminate(char *str, char ch);
char *printPerm(mode_t mode);
char printType(mode_t mode);
void printfile(int flagA, int flagL,char *name);

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
	int c = 0;
	int height = 2;
	DIR *dirp;

	struct dirent *dir;
	struct stat buf;
	struct group *gid;
	struct passwd *uid;

	struct tm *time;
	char buff[256];

	int flagA = 0;
	int flagL = 0;
	int argcount = 0;
	int total=0;
	char swap[256];
	char Subargv[256][256]={'\0'};
	int count=1;

/////////////////////////////option//////////////////////////////
	while ((c = getopt(argc, argv, "alc:")) != -1)
	{
		switch (c)
		{
		case 'a': //If option a
			flagA = 1; //on flag
			break;
		case 'l': //If option l
			flagL = 1; //on flag
			break;
		}
	}
////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
	char paname[256][256]={'\0'};
	for(int i=0;i<argc;i++)
		strcpy(paname[i],argv[i]);
	
	char tmp[256]={'\0'};
	for (int i = 1; i < argc; i++) //buble sort
	{
		for (int j = 1; j < argc -i; j++)
		{

			if (strcasecmp(paname[j], paname[j + 1]) > 0) //If Subargv[j] is bigger than Subargv[j+1] 
			{//practice swap
				strcpy(tmp, paname[j+1]);
				strcpy(paname[j+1], paname[j]);
				strcpy(paname[j], tmp);
			}
		}
	}
/////////////////////////////////////////////////////////////


/////////////////////move parameter////////////////////////////
	for(int i=1;i<argc;i++) //repeat before checking all string of argument vector
	{
		if(paname[i][0]=='-') //When parameter is option
		{
			strcpy(Subargv[count],paname[i]);
			count++;
		}
	}

	for(int i=1;i<argc;i++) //repeat before checking all string of argument vector
	{
		if(lstat(paname[i],&buf)<0&&paname[i][0]!='-') //When parameter not exist
		{
			strcpy(Subargv[count],paname[i]);
			count++;
		}
	}
	

	for(int i=1;i<argc;i++) //repeat before checking all string of argument vector
	{
		if(lstat(paname[i],&buf)==0&&!S_ISDIR(buf.st_mode)&&paname[i][0]!='-') //when parameter is file, but is not directory
		{
			strcpy(Subargv[count],paname[i]);
			count++;
		}
	}
	
	for(int i=1;i<argc;i++) //repeat before checking all string of argument vector
	{
		if(lstat(paname[i],&buf)==0&&S_ISDIR(buf.st_mode)) //when parameter is directory
		{
			strcpy(Subargv[count],paname[i]);
			count++;
		}
	}
//////////////////////////////////////////////////////////////
				
	for (int i = 0; argv[i]; i++) //checking count
		if (argv[i][0] != '-')
			argcount++;

	if (argcount == 1) //If parameter is not exist
	{
		dirp = opendir("."); //open current directory
		chdir(".");
		do
		{
			dir = readdir(dirp); //read file

			if (dir == NULL) //check NULL
				break; //stop repeat functsion

			else
			{
				lstat(dir->d_name,&buf);
				if(flagA!=0||dir->d_name[0]!='.') //check hidden file
					total+=buf.st_blocks/2;
				Nodeinsert(dir->d_name); //insert node
			}

		} while (1);

		printlist(flagA, flagL,total); //print linked list
		deletelist(); //delete list
		chdir((char *)getenv("PWD"));
		total=0;
		return 0;
	}

/////////////////////////If argument count is not 1////////////////////////////////
	for (int i = 1; i<argc; i++) //For checking all parameter
	{
		if (Subargv[i][0] == '-') //If the parameter is option
			continue;
	
		

		if (lstat(Subargv[i], &buf)<0) //If the parameter is not file
		{
			printf("cannot access %s: No such file or directory\n",Subargv[i]); //print error
			continue;
		}

		else
		{
			if (S_ISDIR(buf.st_mode)) //If the parameter is directory
			{
				dirp = opendir(Subargv[i]); //open directory
				chdir(Subargv[i]);

				do
				{
					dir = readdir(dirp);

					if (dir == NULL) //check NULL
						break; //stop repeat functsion

					else
					{
						lstat(dir->d_name,&buf);
						if(flagA!=0||dir->d_name[0]!='.') //check hidden file
							total+=buf.st_blocks/2;
						Nodeinsert(dir->d_name); //insert node
					}

				} while (1);

				printlist(flagA, flagL,total); //print linked list
				deletelist(); //delete linked list
				closedir(dirp);
				chdir((char *)getenv("PWD"));
				total=0;
			}
			else //If the parameter just file
				printfile(flagA,flagL,Subargv[i]); //print information of file
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////
// Print function                                                   //
// ================================================================ //
// Input: int -> Information of option flag                         //
//	  int -> Information of option flag                         //
//        int -> For calculating tootal                             //
//                                                                  //
// Output: void                                                     //
//                                                                  //
// Purpose: Print list of directory's files                         //
//////////////////////////////////////////////////////////////////////
void printlist(int flagA, int flagL,int total)
{
	struct group *gid;
	struct passwd *uid;
	struct tm *time;
	char buff[256];
	char cwd[256];
	struct stat buf;
	struct dirent *dir;

	if (flagL==1) //check option if '-l'
	{
		getcwd(cwd, sizeof(cwd));
		printf("Directory path: %s\n", cwd);
		printf("total: %d\n",total);
	}

	for (Node *tmp = Head; tmp; tmp = tmp->next) //Repeat function for printing all list
	{

		if ((flagL == 1 && flagA == 0 && tmp->filename[0] != '.') || (flagL == 1 && flagA == 1))
		{ //check option of '-l'

			lstat(tmp->filename, &buf);

			uid = getpwuid(buf.st_uid);
			gid = getgrgid(buf.st_gid);

			time = localtime(&buf.st_mtime);//save time of fixed file
			printf("%c%s ", printType(buf.st_mode), printPerm(buf.st_mode));
			
			if(printType(buf.st_mode)=='l') //for printing link file
			{
			char link[256];
			char realp[256];
			int i=0;
			int j=0;

			realpath(tmp->filename, link); //real path of link file
			for(;link[i]!='\0';i++);
			for(;link[i]!='/';i--);
			for(;link[i]!='\0';i++,j++)
				realp[j]=link[i+1];
			realp[j+1]='\0';
			strcat(tmp->filename,"->");
			strcat(tmp->filename,realp);
			}
			

			printf("%ld\t", buf.st_nlink); //number of link
			printf("%s\t", uid->pw_name);  //usser ID
			printf("%s\t", gid->gr_name);  //group ID
			printf("%ld\t", buf.st_size); //size of file

			strftime(buff, 255, "%b %d %H:%M", time);
			printf("%s\t", buff);
		}

		if ((flagA == 0 && tmp->filename[0] != '.') || flagA == 1)
			printf("%s\n", tmp->filename); //file name
	}
	return;
}

//////////////////////////////////////////////////////////////////////
// Print function                                                   //
// ================================================================ //
// Input: int -> Information of option flag                         //
//	  int -> Information of option flag                         //
//        int -> For calculating tootal                             //
//                                                                  //
// Output: void                                                     //
//                                                                  //
// Purpose: Print just file information                             //
//////////////////////////////////////////////////////////////////////
void printfile(int flagA, int flagL, char *name) //The function is equal function of printlist
{ //It just print each file from parameter
	struct group *gid;
	struct passwd *uid;
	struct tm *time;
	char buff[256];
	char cwd[256];
	struct stat buf;
	struct dirent *dir;

	if ((flagL == 1 && flagA == 0 && name[0] != '.') || (flagL == 1 && flagA == 1))
		{ //check option if '-l'

			lstat(name, &buf);

			uid = getpwuid(buf.st_uid);
			gid = getgrgid(buf.st_gid);

			time = localtime(&buf.st_mtime);//save time of fixed file
			printf("%c%s ", printType(buf.st_mode), printPerm(buf.st_mode));
			
			if(printType(buf.st_mode)=='l') //for printing link file
			{
			char link[256];
			char realp[256];
			int i=0;
			int j=0;

			realpath(name, link); //real path of link file
			for(;link[i]!='\0';i++);
			for(;link[i]!='/';i--);
			for(;link[i]!='\0';i++,j++)
				realp[j]=link[i+1];
			realp[j+1]='\0';
			strcat(name,"->");
			strcat(name,realp);
			}
			

			printf("%ld\t", buf.st_nlink); //link
			printf("%s\t", uid->pw_name);  //usser ID
			printf("%s\t", gid->gr_name);  //group ID
			printf("%ld\t", buf.st_size); //size of file

			strftime(buff, 255, "%b %d %H:%M", time);
			printf("%s\t", buff);
		}

		if ((flagA == 0 && name[0] != '.') || flagA == 1)
			printf("%s\n", name); //file name
}

//////////////////////////////////////////////////////////////////////
// Insert function                                                  //
// ================================================================ //
// Input: char* -> Name of file                                     //
//                                                                  //
// Output: void                                                     //
//                                                                  //
// Purpose: For creating linked list                                //
//////////////////////////////////////////////////////////////////////
void Nodeinsert(char* name) //The function of inserting node to linked list
{
	char Ename[256];
	char Etmpname[256];
	Node* tmp = Head;
	Node* prevnode;
	

	if (Head == NULL) //If not exist linked list
	{
		Node* newnode = (Node*)malloc(sizeof(Node));
		strcpy(newnode->filename, name);
		newnode->next = NULL;
		newnode->prev = NULL;

		Head = newnode; //Creating head of list
		return;
	}

	else //when exist linked list
	{
		for (; tmp; tmp = tmp->next) //For checking all node
		{
                 //////////For checking symbol in string//////////
			strcpy(Ename, name);
			strcpy(Etmpname, tmp->filename);

			if (checkstring(Ename))
				Eliminate(Ename, '.');
			if (checkstring(Etmpname))
				Eliminate(Etmpname, '.');
		 /////////////////////////////////////////////////

			if (strcasecmp(Etmpname, Ename)>0) //compare string
			{
				if (tmp == Head) //when the new node insert before head node
				{
					Node* newnode = (Node*)malloc(sizeof(Node));
					strcpy(newnode->filename, name);
					newnode->prev = NULL;

					newnode->next = Head;
					Head->prev = newnode;
					Head = newnode;
					return;
				}

				else //when the new node insert before tmp node
				{
					Node* newnode = (Node*)malloc(sizeof(Node));
					strcpy(newnode->filename, name);
					newnode->next = tmp;
					newnode->prev = tmp->prev;
					tmp->prev->next = newnode;
					tmp->prev = newnode;
					return;
				}
			}
			else continue;
		}
		//when the new node insert next Tail node
		for (prevnode = Head; prevnode->next; prevnode = prevnode->next);
		Node* newnode = (Node*)malloc(sizeof(Node));

		strcpy(newnode->filename, name);
		newnode->next = NULL;
		prevnode->next = newnode;
		newnode->prev = prevnode;
		Tail = newnode;
		return;

	}
}

//////////////////////////////////////////////////////////////////////
// Check function                                                   //
// ================================================================ //
// Input: int -> Information of option flag                         //
//	  int -> Information of option flag                         //
//        int -> For calculating tootal                             //
//                                                                  //
// Output: int 1 -> Not exist symbol                                //
//             0 -> Exist symbol                                    //
//                                                                  //
// Purpose: For checking symbol in string                           //
//////////////////////////////////////////////////////////////////////
int checkstring(char* str)
{
	for (int i = 0; str[i] != '\0'; i++) //checking all character in string
	{
		if (str[i] >= 65 && str[i] <= 132) //check letters
			return 1;
		else if (str[i] >= 97 && str[i] <= 122) //check letters
			return 1;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////
// Delete function                                                  //
// ================================================================ //
// Input: char* -> The string is checked                            //
//	  char -> The character is wanted to eliminating            //
//                                                                  //
// Output: void                                                     //
//                                                                  //
// Purpose: For eliminating '.' symbol                              //
//////////////////////////////////////////////////////////////////////
void Eliminate(char *str, char ch) //for eliminating symbol of '.'
{
	for (; *str != '\0'; str++) //checking all character in string
	{
		if (*str == ch) //If character is '.'
		{
			strcpy(str, str + 1); //Eliminating
			str--;
			return;
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Delete function                                                  //
// ================================================================ //
// Input:  void                                                     //
//                                                                  //
// Output: void                                                     //
//                                                                  //
// Purpose: Delete linked list                                      //
//////////////////////////////////////////////////////////////////////
void deletelist() //for deleteing all linked list
{
	Node* tmp = Head;
	for (; tmp->next != NULL;) //Hit all node
	{
		Head = tmp->next;
		free(tmp); //free
		tmp = Head;
	}
	free(tmp);
	Head = NULL;
}

//////////////////////////////////////////////////////////////////////
// Print function                                                   //
// ================================================================ //
// Input: mode_t -> Information of file                             //
//                                                                  //
// Output: char -> The symbol of type                               //
//                                                                  //
// Purpose: Print symbol of file's type                             //
//////////////////////////////////////////////////////////////////////
char printType(mode_t mode) //for checking type of file
{
	switch (mode & S_IFMT)
	{
	case S_IFREG:
		return('-');
	case S_IFDIR:
		return('d');
	case S_IFCHR:
		return('c');
	case S_IFBLK:
		return('b');
	case S_IFLNK:
		return('l');
	case S_IFIFO:
		return('p');
	case S_IFSOCK:
		return('s');
	}

	return('?');
}

//////////////////////////////////////////////////////////////////////
// Print function                                                   //
// ================================================================ //
// Input: mode_t -> Information of file                             //
//                                                                  //
// Output: char* -> The symbol of permission                        //
//                                                                  //
// Purpose: Print symbol of file's permission                       //
//////////////////////////////////////////////////////////////////////
char *printPerm(mode_t mode) //for checking information of permission from file
{
	int i;
	char *p;
	static char perms[10];

	p = perms;
	strcpy(perms, "---------");

	for (i = 0; i < 3; i++)
	{
		if (mode & (S_IREAD >> i * 3)) //read
			*p = 'r';
		p++;

		if (mode & (S_IWRITE >> i * 3)) //write
			*p = 'w';
		p++;

		if (mode & (S_IEXEC >> i * 3)) //execute
			*p = 'x';
		p++;
	}
	if ((mode & S_ISUID) != 0)
		perms[2] = 's';

	if ((mode & S_ISGID) != 0)
		perms[5] = 's';

	if ((mode & S_ISVTX) != 0)
		perms[8] = 't';

	return(perms);
}
