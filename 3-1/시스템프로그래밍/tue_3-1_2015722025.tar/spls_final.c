//////////////////////////////////////////////////////////////////////
//File Name         :spls_final.c                                   //
//Date              :2019/05/03                                     //
//Os                :Ubuntu 16.04 LTS 64bits                        //
//Author            :Jeong yong hoon                                //
//Student ID        :2015722025                                     //
//------------------------------------------------------------------//
//Title : System Programing Assignment #3-1 (HTML ls)               //
//Description : The 3-1 task is to learn simple html output.        //
//              If you open the file through the open function and  //
//              create an html file according to the html output    //
//              format, you can execute the file, and the output    //
//              format is displayed like the pdf provided rather    //
//              than the results normally checked by the console.   //
//              Algorithms or functions for output are the          //
//              same as the previous task.                          //
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
#include<fnmatch.h>

typedef struct Node //The struct for linked list
{
	char filename[256]; //information
	struct Node *next; //next
	struct Node *prev; //prev
}Node;

Node *Head = NULL; //Head of linked list
Node *Tail = NULL; //Tail of linked list

int flagA = 0, flagL =0, flagh=0, flagS=0, flagr=0; //value of option
int Nofilecount = 0, Filecount = 0, Optioncount = 0, Directorycount = 0;
int excount = 1; //excution count

int HTMLflag=0;
int Noparameter=0;

void Nodeinsert(char* fname);

void deletelist();
int checkstring(char* str);
void Eliminate(char *str, char ch);
char *printPerm(mode_t mode);
char printType(mode_t mode);
void NodeinsertS(char* name);
int matchfunction(char(*paname)[256], int argc);
void sortingfile(char(*paname)[256],int argc);
int checkexist(char* str);


void printOph(long int sizem,FILE *file);
void printfileHTML(FILE *file,int flagA, int flagL,char *name); ////////nedd modify
void printHTML(FILE *file,int flagA, int flagL, int total, int argc,char *dirpath);
void printHTMLr(FILE *file,int flagA, int flagL, int total, int argc,char *dirpath);




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

	int argcount = 0;
	int total=0;
	char swap[256];
	char Subargv[256][256]={'\0'};
	char match[256];
	int count=1;
	char NULLpath[256]={0};

	int NofilePcount=0;
	int filePcount=0;
	char title[256]={0};

	getcwd(title, sizeof(title)); //load current working directory

	FILE *file=fopen("html_ls.html","w"); //file open for HTML
	if(file==0)
	{
		printf("error\n");
		return -1;
	}
	fprintf(file,"<html>");
	fprintf(file,"<title>%s</title>",title);
	fprintf(file,"<h1>"); //for printing command
	for(int i=0;i<argc;i++)
		fprintf(file,"%s ",argv[i]); //print all parameter
	fprintf(file,"</h1><br><br>\n"); //end head
		


/////////////////////////Set option//////////////////////////////
	while ((c = getopt(argc, argv, "alhSrc:")) != -1)
	{
		switch (c)
		{
		case 'a': //If option a
			flagA = 1; //on flag
			break;
		case 'l': //If option l
			flagL = 1; //on flag
			break;
		case'h': //If option h
			flagh=1; //on flag
			break;
		case'S': //If option S
			flagS=1; //on flag
			break; 
		case'r': //If option r
			flagr=1; //on flag
			break;
		}
	}
////////////////////////////////////////////////////////////////


/////////////move parameter for other working///////////////////
	char paname[256][256]={'\0'};
	char sortname[256][256]={'\0'};
	for(int i=0;i<argc;i++) //move content of parameter
		strcpy(paname[i],argv[i]);
////////////////////////////////////////////////////////////////

	argc=matchfunction(paname,argc); //find match

//////////////////Sorting argument vector///////////////////////	
	for(int i=0;i<argc;i++) //move content of parameter
		strcpy(sortname[i],paname[i]); //copy string

	for(int i=0;i<argc;i++) //check all parameter
	{
		if(sortname[i][0]=='/') //check exist of '/'
			Eliminate(sortname[i], '/'); //remove '/'
	}

	char tmp[256]={'\0'};
	for (int i = 1; i < argc; i++) //buble sort
	{
		for (int j = 1; j < argc -i; j++)
		{
			if(flagr==1&&(strcasecmp(sortname[j], sortname[j + 1]) < 0)) //condition of reverse
			{//practice swap
				strcpy(tmp, paname[j+1]); //copy
				strcpy(paname[j+1], paname[j]); //copy
				strcpy(paname[j], tmp); //copy

				strcpy(tmp, sortname[j+1]); //copy
				strcpy(sortname[j+1], sortname[j]); //copy
				strcpy(sortname[j], tmp); //copy
			}

			else if (flagr==0&&(strcasecmp(sortname[j], sortname[j + 1]) > 0)) //If Subargv[j] is bigger than Subargv[j+1] 
			{//practice swap
				strcpy(tmp, paname[j+1]); //copy
				strcpy(paname[j+1], paname[j]); //copy
				strcpy(paname[j], tmp); //copy

				strcpy(tmp, sortname[j+1]); //copy
				strcpy(sortname[j+1], sortname[j]); //copy
				strcpy(sortname[j], tmp); //copy
			}
		}
	}
/////////////////////////////////////////////////////////////

			

/////////////////////move parameter for sorting////////////////////////////
	for(int i=1;i<argc;i++) //repeat before checking all string of argument vector
	{
		if(paname[i][0]=='-') //When parameter is option
		{
			strcpy(Subargv[count],paname[i]); //copy
			count++;
			Optioncount++;
		}
	}

	for(int i=1;i<argc;i++) //repeat before checking all string of argument vector
	{
		char link[256];

		if(flagL!=1) //check option of L
			realpath(paname[i], link); //load real path
		else
			strcpy(link,paname[i]); //copy
		if(lstat(link,&buf)<0&&paname[i][0]!='-') //When parameter not exist
		{
			strcpy(Subargv[count],paname[i]); //copy
			count++;
			Nofilecount++;
		}
	}
	

	for(int i=1;i<argc;i++) //repeat before checking all string of argument vector
	{
		char link[256];
		if(flagL!=1) //check option of L
			realpath(paname[i], link); //load real path
		else
			strcpy(link,paname[i]); //copy
		if(lstat(link,&buf)==0&&!S_ISDIR(buf.st_mode)&&paname[i][0]!='-') //when parameter is file, but is not directory
		{
			strcpy(Subargv[count],paname[i]); //copy
			count++;
			Filecount++;
		}
	}
	
	for(int i=1;i<argc;i++) //repeat before checking all string of argument vector
	{
		char link[256];
		if(flagL!=1) //check option of L
			realpath(paname[i], link); //load real path
		else
			strcpy(link,paname[i]); //copy
		if(lstat(link,&buf)==0&&S_ISDIR(buf.st_mode)) //when parameter is directory
		{
			strcpy(Subargv[count],paname[i]); //copy
			count++;
			Directorycount++;
		}
	}

//////////////////////////////////////////////////////////////////
	if(flagS==1) //check option of S(size)
		sortingfile(Subargv,argc); //practice sorting
			
	for (int i = 0; argv[i]; i++) //checking count
		if (argv[i][0] != '-')
			argcount++;

	if (argcount == 1) //If parameter is not exist
	{
		Noparameter=1;
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
				
				if(flagS==1)
					NodeinsertS(dir->d_name); //sorting of size

				else
					Nodeinsert(dir->d_name); //insert node
			}

		} while (1);

		
		if(flagr==1)
		{
			printHTMLr(file,flagA, flagL,total, argc,NULLpath); //print reverse
		}
		else
		{
			printHTML(file,flagA, flagL,total, argc,NULLpath);
		}
		deletelist(); //delete list
		chdir((char *)getenv("PWD"));
		total=0;
		return 0;
	}

			

/////////////////////////If argument count is not 1////////////////////////////////
	for (int i = 1; i<argc; i++) //For checking all parameter
	{
			/*for(int i=0;i<argc;i++)
		printf("%s\n",Subargv[i]);
		exit(0);*/
		char dirpath[256]={0};
		strcpy(dirpath,Subargv[i]);

		if(checkexist(Subargv[i])) //check exist character of '/'
		{
			int num=0;
			for(;Subargv[i][num]!='\0';num++); //move pointer to end of string
			for(;Subargv[i][num]!='/';num--); //search '/'
			for(int check=0;check<num;check++)
				dirpath[check]=Subargv[i][check]; //copy string before '/'
		}
		

		excount++;
		if (Subargv[i][0] == '-') //If the parameter is option
			continue;
	
		if (lstat(Subargv[i], &buf)<0) //If the parameter is not file
		{
			if(NofilePcount==0) //check count of file
			{
				fprintf(file,"<body>\n"); //print format of html
				fprintf(file,"<table border=1>\n"); //print format of html
				fprintf(file,"<tr style=background-color:black><th style=color:yellow>List of non-existent files or directories</th></tr>\n"); //print format of html
			}

			if(Subargv[i][0]=='/'&& (Subargv[i][strlen(Subargv[i])-1]=='*' || Subargv[i][strlen(Subargv[i])-1]=='?' || Subargv[i][strlen(Subargv[i])-1]==']'))
				fprintf(file,"<tr><td><B>ls: cannot access</B><B style=color:red> %s</B><B>: No such file or directory</B></td></tr>\n",Subargv[i]); //print error

			
			else			
				fprintf(file,"<tr><td><B>cannot access</B><B style=color:red> %s</B><B>: No such file or directory</B></td></tr>\n",Subargv[i]); //print error
			NofilePcount++;
			
			if(NofilePcount==Nofilecount) //check count
				fprintf(file,"</table>\n</body><br>\n"); //print format of html
			
			continue;
		}

		else
		{
			if(flagL!=1) //check flag L
			{
				char link[256];
				struct stat buf2;
				realpath(Subargv[i], link); //real path of link file
				lstat(link, &buf2); //read file
				if(S_ISDIR(buf2.st_mode)) //check directory
					buf.st_mode=buf2.st_mode;
			}

			if (S_ISDIR(buf.st_mode)) //If the parameter is directory
			{
				if(Subargv[i][0]=='.')
					Noparameter=1;
				dirp = opendir(Subargv[i]); //open directory
				chdir(Subargv[i]); //change directory

				do
				{
					dir = readdir(dirp); //read

					if (dir == NULL) //check NULL
						break; //stop repeat functsion

					else
					{
						lstat(dir->d_name,&buf); //read file
						if(flagA!=0||dir->d_name[0]!='.') //check hidden file
							total+=buf.st_blocks/2;
						
						if(flagS==1)
							NodeinsertS(dir->d_name); //inser if option S is on

						else
							Nodeinsert(dir->d_name); //insert node
					}

				} while (1);
				
				if(flagr==1)
				{
					printHTMLr(file,flagA, flagL,total, argc,dirpath); //print linked list (reverse)
				}
				else
				{
					printHTML(file,flagA, flagL,total, argc,dirpath);
				}
				deletelist(); //delete linked list
				closedir(dirp); //close dirp
				chdir((char *)getenv("PWD")); //change directory
				total=0;
			}

			else //If the parameter just file
			{

			if(filePcount==0) //check count of file
				{
					fprintf(file,"<body>\n"); //print format of html
					fprintf(file,"<table border=1>\n"); //print format of html
					if(flagL==1) //If on flag L
					{
						fprintf(file,"<tr style=background-color:black><th colspan=7; style=color:yellow>List of file</th></tr>\n"); //print format of html
						fprintf(file,"<tr><th>Name</th><th>Permission</th><th>Link</th><th>Owner</th><th>Group</th><th>Size</th><th>Last Modified</th></tr>\n"); //print format of html
					}
					else
					{	fprintf(file,"<tr style=background-color:black><th style=color:yellow>List of file</th></tr>\n"); //print format of html
						fprintf(file,"<tr><th>Name</th></tr>\n"); //print format of html
					}
				}
				printfileHTML(file,flagA,flagL,Subargv[i]); //print information of file
				filePcount++;
	
			if(filePcount==Filecount) //check count
					fprintf(file,"</table>\n</body><br>\n"); //print format of html
				

			}
		}
	}
	fprintf(file,"</html>"); //end of html format
	fclose(file); //close file
	return 0;
}

//////////////////////////////////////////////////////////////////////
// Print function                                                   //
// ================================================================ //
// Input: int -> Information of option flag                         //
//	  int -> Information of option flag                         //
//        int -> For calculating total                              //
//        int -> For get information of argument count              //
//        char* -> For get information of directory path            //
//        FILE* -> For write information of html format             //
//                                                                  //
// Output: void                                                     //
//                                                                  //
// Purpose: Print information of directory                          //
//////////////////////////////////////////////////////////////////////
void printHTML(FILE* file,int flagA, int flagL, int total, int argc,char *dirpath)
{
	struct group *gid;
	struct passwd *uid;
	struct tm *time;
	char buff[256];
	char cwd[256];
	struct stat buf;
	struct dirent *dir;

	int k=0, m=0;
	char subpath[256]={0};
	char subdirpath[256]={0};
	char checkpath[256]={0};
	char color[256]={0};

	int createflag=0;
	

	getcwd(cwd, sizeof(cwd)); //load current working directory
	
	if (flagL==1||argc>2) //check option if '-l'
	{
		//getcwd(cwd, sizeof(cwd)); //load current working directory
		for(;cwd[k]!='\0';k++);
		for(;cwd[k]!='/';k--);
		for(;m<k;m++)
			subpath[m]=cwd[m];

		for(k=0;dirpath[k]!='\0';k++); //move pointer to end
		for(;dirpath[k]!='/'&&k!=0;k--); //search '/'
		if(dirpath[k]=='/') k++; //check character
		for(m=0;dirpath[k]!='\0';m++,k++)
			subdirpath[m]=dirpath[k];

		strcat(checkpath,subpath); //letter aggregation
		strcat(checkpath,"/"); //letter aggregation
		strcat(checkpath,subdirpath); //letter aggregation
		//printf("%s\n",dirpath);

		lstat(checkpath,&buf); //read type of file
		if(S_ISLNK(buf.st_mode))
			strcpy(cwd,checkpath);
		//printf("%s\n",cwd);

		if(flagL==0&&(Directorycount+Nofilecount+Filecount>1)) //check option
			fprintf(file,"<h3>Directory path : %s</h3>\n",cwd); //print format of html
		else if(flagL==1&&(Directorycount+Nofilecount+Filecount>1))
		{
			fprintf(file,"<h3>Directory path : %s</h3>\n",cwd);
			fprintf(file,"<h3>total %d</h3>\n",total); //print format of html
		}
		else if(flagL==1)
			fprintf(file,"<h3>total %d</h3>\n",total); //print format of html
		

	}
		

	for (Node *tmp = Head; tmp; tmp = tmp->next) //Repeat function for printing all list
	{
		int m=0,n=0;
		char checkname[256]={0};
		for(;tmp->filename[m]!='\0';m++);
		for(;tmp->filename[m]!='/' &&m!=0;m--);
		for(;tmp->filename[m]!='\0';n++,m++)
			checkname[n]=tmp->filename[m];

		if(!strcmp(checkname,"html_ls.html"))
			continue;
		char hyperlink[256]={0};
		strcpy(hyperlink,cwd);
		strcat(hyperlink,"/");

		if ((flagL == 1 && flagA == 0 && tmp->filename[0] != '.') || (flagL == 1 && flagA == 1))
		{ //check option of '-l'
			if(createflag==0)
			{
				fprintf(file,"<body>\n"); //print format of html
				fprintf(file,"<table border=1>\n"); //print format of html
				if(flagL==1)
					fprintf(file,"<tr><th>Name</th><th>Permission</th><th>Link</th><th>Owner</th><th>Group</th><th>Size</th><th>Last Modified</th></tr>\n"); //print format of html
				else
					fprintf(file,"<tr><th>Name</th></tr>\n");//print format of html
			createflag=1;
			}
		

			lstat(tmp->filename, &buf); //read file
			
			strcpy(color,"style=color:red>"); //check type of file or directory
			if(S_ISDIR(buf.st_mode))
				strcpy(color,"style=color:blue>");
			else if(S_ISLNK(buf.st_mode))
				strcpy(color,"style=color:green>");

			strcat(hyperlink,tmp->filename);
			if(tmp->filename[0]=='/')
				strcpy(hyperlink,tmp->filename);

			uid = getpwuid(buf.st_uid); //get user id
			gid = getgrgid(buf.st_gid); //get group id

			time = localtime(&buf.st_mtime);//save time of fixed file
			
			if(printType(buf.st_mode)=='l') //for printing link file
			{
			char link[256];
			char realp[256];
			int i=0;
			int j=0;

			realpath(tmp->filename, link); //real path of link file
			for(;link[i]!='\0';i++); //move pointer to end
			for(;link[i]!='/';i--); //search '/'
			for(;link[i]!='\0';i++,j++)
				realp[j]=link[i+1];
			realp[j+1]='\0';
			strcat(tmp->filename,"->"); //letter aggregation
			strcat(tmp->filename,realp); //letter aggregation
			}
			
			strftime(buff, 255, "%b %d %H:%M", time);
			
			fprintf(file,"<tr %s<td><a href=%s>%s</a></td>",color,hyperlink,tmp->filename); //print format of html
			fprintf(file,"<td>%c%s</td>",printType(buf.st_mode), printPerm(buf.st_mode)); //print format of html
			fprintf(file,"<td>%ld</td>",buf.st_nlink); //print format of html
			fprintf(file,"<td>%s</td>",uid->pw_name); //print format of html
			fprintf(file,"<td>%s</td>",gid->gr_name); //print format of html
			if(flagh==1) //check flag h
				printOph(buf.st_size,file); //change format of size
				
			else	
				fprintf(file,"<td>%ld\t</td>", buf.st_size); //print format of html
			fprintf(file,"<td>%s</td></tr>",buff); //print format of html
			
		}

		else if ((flagL == 0 && flagA == 0 && tmp->filename[0] != '.') || (flagL == 0 && flagA == 1))
		{
			if(createflag==0)
			{
				fprintf(file,"<body>\n"); //print format of html
				fprintf(file,"<table border=1>\n"); //print format of html
				if(flagL==1)
					fprintf(file,"<tr><th>Name</th><th>Permission</th><th>Link</th><th>Owner</th><th>Group</th><th>Size</th><th>Last Modified</th></tr>\n"); //print format of html
				else
					fprintf(file,"<tr><th>Name</th></tr>\n"); //print format of html
			createflag=1;
			}
			strcat(hyperlink,tmp->filename); //make hyperlink
			if(tmp->filename[0]=='/') //check absolute path
				strcpy(hyperlink,tmp->filename);
			fprintf(file,"<tr><td><a href=%s>%s</a></td></tr>",hyperlink,tmp->filename); //print format of html
		}
		
	}
	fprintf(file,"</table>\n</body>"); //end of html format
	return;
}

//////////////////////////////////////////////////////////////////////
// Print function                                                   //
// ================================================================ //
// Input: int -> Information of option flag                         //
//	  int -> Information of option flag                         //
//        int -> For calculating total                              //
//        int -> For get information of argument count              //
//        char* -> For get information of directory path            //
//        FILE* -> For write information of html format             //
//                                                                  //
// Output: void                                                     //
//                                                                  //
// Purpose: Print information of directory (reverse)                //
//////////////////////////////////////////////////////////////////////
void printHTMLr(FILE* file,int flagA, int flagL, int total, int argc,char *dirpath)
{
	struct group *gid;
	struct passwd *uid;
	struct tm *time;
	char buff[256];
	char cwd[256];
	struct stat buf;
	struct dirent *dir;

	int k=0, m=0;
	char subpath[256]={0};
	char subdirpath[256]={0};
	char checkpath[256]={0};
	char color[256]={0};

	int createflag=0;
	

	getcwd(cwd, sizeof(cwd)); //load current working directory
	
	if (flagL==1||argc>2) //check option if '-l'
	{
		//getcwd(cwd, sizeof(cwd)); //load current working directory
		for(;cwd[k]!='\0';k++);
		for(;cwd[k]!='/';k--);
		for(;m<k;m++)
			subpath[m]=cwd[m];

		for(k=0;dirpath[k]!='\0';k++); //move pointer to end
		for(;dirpath[k]!='/'&&k!=0;k--); //search '/'
		if(dirpath[k]=='/') k++; //check character
		for(m=0;dirpath[k]!='\0';m++,k++)
			subdirpath[m]=dirpath[k];

		strcat(checkpath,subpath); //letter aggregation
		strcat(checkpath,"/"); //letter aggregation
		strcat(checkpath,subdirpath); //letter aggregation
		//printf("%s\n",checkpath);

		lstat(checkpath,&buf); //read file
		if(S_ISLNK(buf.st_mode)) //check type of file
			strcpy(cwd,checkpath); //make path

		if(flagL==0&&(Directorycount+Nofilecount+Filecount>1)) //check option
			fprintf(file,"<h3>Directory path : %s</h3>\n",cwd); //print format of html
		else if(flagL==1&&(Directorycount+Nofilecount+Filecount>1))
		{
			fprintf(file,"<h3>Directory path : %s</h3>\n",cwd); //print format of html
			fprintf(file,"<h3>total %d</h3>\n",total); //print format of html
		}
		else if(flagL==1)
			fprintf(file,"<h3>total %d</h3>\n",total); //print format of html

	}
		
	Node *tmp = Head;
	for(;tmp->next;tmp=tmp->next);
	for (; tmp; tmp = tmp->prev) //Repeat function for printing all list
	{
		
		int m=0,n=0;
		char checkname[256]={0};
		for(;tmp->filename[m]!='\0';m++);
		for(;tmp->filename[m]!='/' &&m!=0;m--);
		for(;tmp->filename[m]!='\0';n++,m++)
			checkname[n]=tmp->filename[m];

		if(!strcmp(checkname,"html_ls.html"))
			continue;

		char hyperlink[256]={0};
		strcpy(hyperlink,cwd);
		strcat(hyperlink,"/");

		if ((flagL == 1 && flagA == 0 && tmp->filename[0] != '.') || (flagL == 1 && flagA == 1))
		{ //check option of '-l'
			if(createflag==0)
			{
				fprintf(file,"<body>\n"); //print format of html
				fprintf(file,"<table border=1>\n"); //print format of html
				if(flagL==1)
					fprintf(file,"<tr><th>Name</th><th>Permission</th><th>Link</th><th>Owner</th><th>Group</th><th>Size</th><th>Last Modified</th></tr>\n"); //print format of html
				else
					fprintf(file,"<tr><th>Name</th></tr>\n");//print format of html
			createflag=1;
			}
		

			lstat(tmp->filename, &buf); //read file
			
			strcpy(color,"style=color:red>"); //check type of file or directory
			if(S_ISDIR(buf.st_mode))
				strcpy(color,"style=color:blue>");
			else if(S_ISLNK(buf.st_mode))
				strcpy(color,"style=color:green>");

			strcat(hyperlink,tmp->filename);
			if(tmp->filename[0]=='/')
				strcpy(hyperlink,tmp->filename);

			uid = getpwuid(buf.st_uid); //get user id
			gid = getgrgid(buf.st_gid); //get group id

			time = localtime(&buf.st_mtime);//save time of fixed file
			
			if(printType(buf.st_mode)=='l') //for printing link file
			{
			char link[256];
			char realp[256];
			int i=0;
			int j=0;

			realpath(tmp->filename, link); //real path of link file
			for(;link[i]!='\0';i++); //move pointer to end
			for(;link[i]!='/';i--); //search '/'
			for(;link[i]!='\0';i++,j++)
				realp[j]=link[i+1];
			realp[j+1]='\0';
			strcat(tmp->filename,"->"); //letter aggregation
			strcat(tmp->filename,realp); //letter aggregation
			}
			
			strftime(buff, 255, "%b %d %H:%M", time);
			
			fprintf(file,"<tr %s<td><a href=%s>%s</a></td>",color,hyperlink,tmp->filename); //print format of html
			fprintf(file,"<td>%c%s</td>",printType(buf.st_mode), printPerm(buf.st_mode)); //print format of html
			fprintf(file,"<td>%ld</td>",buf.st_nlink); //print format of html
			fprintf(file,"<td>%s</td>",uid->pw_name); //print format of html
			fprintf(file,"<td>%s</td>",gid->gr_name); //print format of html
			if(flagh==1) //check flag h
				printOph(buf.st_size,file); //change format of size
				
			else	
				fprintf(file,"<td>%ld\t</td>", buf.st_size); //print format of html
			fprintf(file,"<td>%s</td></tr>",buff); //print format of html
			
		}

		else if ((flagL == 0 && flagA == 0 && tmp->filename[0] != '.') || (flagL == 0 && flagA == 1))
		{
			if(createflag==0)
			{
				fprintf(file,"<body>\n"); //print format of html
				fprintf(file,"<table border=1>\n"); //print format of html
				if(flagL==1)
					fprintf(file,"<tr><th>Name</th><th>Permission</th><th>Link</th><th>Owner</th><th>Group</th><th>Size</th><th>Last Modified</th></tr>\n"); //print format of html
				else
					fprintf(file,"<tr><th>Name</th></tr>\n"); //print format of html
			createflag=1;
			}
			strcat(hyperlink,tmp->filename); //make hyperlink
			if(tmp->filename[0]=='/') //check absolute path
				strcpy(hyperlink,tmp->filename);
			fprintf(file,"<tr><td><a href=%s>%s</a></td></tr>",hyperlink,tmp->filename); //print format of html
		}
		
	}
	fprintf(file,"</table>\n</body>"); //end of html format
	return;
}

//////////////////////////////////////////////////////////////////////
// Print function                                                   //
// ================================================================ //
// Input: int -> Information of option flag                         //
//	  int -> Information of option flag                         //
//        int -> For calculating tootal                             //
//        FILE* -> For write information of html format             //
//                                                                  //
// Output: void                                                     //
//                                                                  //
// Purpose: Print just file information                             //
//////////////////////////////////////////////////////////////////////
void printfileHTML(FILE *file,int flagA, int flagL, char *name) //The function is equal function of printlist
{
	struct group *gid;
	struct passwd *uid;
	struct tm *time;
	char buff[256];
	char cwd[256];
	struct stat buf;
	struct dirent *dir;

	int k=0, m=0;
	char subpath[256]={0};
	char subdirpath[256]={0};
	char checkpath[256]={0};

	int v=0,n=0;
	char checkname[256]={0};
	for(;name[v]!='\0';v++);
	for(;name[v]!='/' &&v!=0;v--);
	for(;name[v]!='\0';n++,v++)
	{
		if(name[v]=='/')
			v++;
		checkname[n]=name[v];
	}

	if(!strcmp(checkname,"html_ls.html"))
		return;

	char hyperlink[256]={0};
	getcwd(cwd, sizeof(cwd)); //load current working directory
	strcpy(hyperlink,cwd);
	strcat(hyperlink,"/");
	
	
		if ((flagL == 1 && flagA == 0 && name[0] != '.') || (flagL == 1 && flagA == 1)) //check flag and others
		{ //check option of '-l'

			lstat(name, &buf); //read file
			char color[256]={0};
			strcpy(color,"red");
			if(S_ISLNK(buf.st_mode))
				strcpy(color,"green");

			uid = getpwuid(buf.st_uid); //get user id
			gid = getgrgid(buf.st_gid); //get group id

			time = localtime(&buf.st_mtime);//save time of fixed file
			
			char link[256];
			if(printType(buf.st_mode)=='l') //for printing link file
			{
			char realp[256];
			int i=0;
			int j=0;

			realpath(name, link); //real path of link file
			for(;link[i]!='\0';i++); //move pointer to end
			for(;link[i]!='/';i--); //search '/'
			for(;link[i]!='\0';i++,j++)
				realp[j]=link[i+1];
			realp[j+1]='\0';
			strcat(name,"->"); //letter aggregation
			strcat(name,realp); //letter aggsregation
			}
			strftime(buff, 255, "%b %d %H:%M", time);
			
			strcat(hyperlink,name); //make path of hyperlink
			if(name[0]=='/') //check path of absolute
				strcpy(hyperlink,name); //change hyperlink
			if(S_ISLNK(buf.st_mode))
				strcpy(hyperlink,link);
			fprintf(file,"<tr style=color:%s><td><a href=%s>%s</a></td>",color,hyperlink,name); //print format of html
			fprintf(file,"<td>%c%s</td>",printType(buf.st_mode), printPerm(buf.st_mode)); //print format of html
			fprintf(file,"<td>%ld</td>",buf.st_nlink); //print format of html
			fprintf(file,"<td>%s</td>",uid->pw_name); //print format of html
			fprintf(file,"<td>%s</td>",gid->gr_name); //print format of html
			if(flagh==1) //check option of h
				printOph(buf.st_size,file); //change format of size
				
			else	
				fprintf(file,"<td>%ld\t</td>", buf.st_size); //print format of html
			fprintf(file,"<td>%s</td></tr>",buff); //print format of html
			
		}

		if ((flagL == 0 && flagA == 0 && name[0] != '.') || (flagL == 0 && flagA == 1)) //check flag and others
		{
			strcat(hyperlink,name); //make path of hyperlink
			if(name[0]=='/') //check path of absolute
				strcpy(hyperlink,name); //change hyperlink
			fprintf(file,"<tr><td><a href=%s>%s</a></td></tr>",hyperlink,name); //print format of html
		}
	
	return;
}

//////////////////////////////////////////////////////////////////////
// Print function                                                   //
// ================================================================ //
// Input: long int -> Information of option size                    //
//                                                                  //
// Output: void                                                     //
//                                                                  //
// Purpose: For printing option of h                                //
//////////////////////////////////////////////////////////////////////
void printOph(long int size,FILE *file)
{
	int k=0,flag=0;
	double sub_size;
	
	sub_size=(double)size;	
	
	for(k=0;1;k++) //for check size of k(unit)
	{
		if(sub_size>(double)1024) 
			sub_size/=1024;
	
		else 
			break;
	}
	size=(int)sub_size; //change of type
	sub_size=(int)(sub_size*10); //Remove from decimal second
	sub_size=sub_size/10;
	if(size*10==(int)(sub_size*10)) //check first decimal point
		flag=1;
	
	int size_int=0;
	
	if(k==0) //below kilobytes
	{
		
		size_int=(int)sub_size;
		fprintf(file,"<td>%d</td>",size_int);
		
	}

	else if(k==1) //kilobytes
	{
		if(flag==1) //flag of intger
		{
			size_int=(int)sub_size;
			fprintf(file,"<td>%d%s</td>",size_int,"K");
		}
		else //exist decimal point
			fprintf(file,"<td>%.1lf%s</td>",sub_size,"K");
	}

	else if(k==2) //megabytes unit
	{
		if(flag==1) //flag of intger
		{
			size_int=(int)sub_size;
			fprintf(file,"<td>%d%s</td>",size_int,"M");
		}
		else //exist decimal point
			fprintf(file,"<td>%.1lf%s</td>",sub_size,"M");
	}
	
	else if(k==3) //gigabytes unit
	{
		if(flag==1) //flag of intger
		{
			size_int=(int)sub_size;
			fprintf(file,"<td>%d%s</td>",size_int,"G");
		}
		else //exist decimal point
			fprintf(file,"<td>%.1lf%s</td>",sub_size,"G");
	}

	else if(k==4) //terabytes unit
	{
		if(flag==1) //flag of intger
		{
			size_int=(int)sub_size;
			fprintf(file,"<td>%d%s</td>",size_int,"T");
		}
		else //exist decimal point
			fprintf(file,"<td>%.1lf%s</td>",sub_size,"T");
	}
	return;
}

void sortingfile(char(*paname)[256], int argc)
{
	//Nofilecount = 0, Filecount = 0, Optioncount = 0;
	struct stat buf;
	struct stat buf2;
	char subarray[256][256]={0};
	char tmp[256]={0};
	int count=0;


	for(int i=(Optioncount+Nofilecount+1),j=0;i<(Optioncount+Nofilecount+Filecount+1);i++,j++,count++) //for move content to subarray
		strcpy(subarray[j],paname[i]); //copy
		
	for (int loop = 0; loop < count - 1; loop++) 
	{
		for (int i = 0; i < count - 1 - loop; i++) 
		{
			lstat(subarray[i],&buf);
			lstat(subarray[i+1],&buf2);
        		if(flagr==1&&buf.st_size>buf2.st_size) //If flagr is on
			{//practice swap
				strcpy(tmp,subarray[i+1]); //copy
				strcpy(subarray[i+1], subarray[i]); //copy
				strcpy(subarray[i], tmp); //copy
			}

			else if (flagr==0&&buf.st_size<buf2.st_size) //If Subargv[j] is bigger than Subargv[j+1] 
			{//practice swap
				strcpy(tmp, subarray[i+1]); //copy
				strcpy(subarray[i+1], subarray[i]); //copy
				strcpy(subarray[i], tmp); //copy
			}
    		}
	}

		for(int i=(Optioncount+Nofilecount+1),j=0;i<(Optioncount+Nofilecount+Filecount+1);i++,j++) //for move content to paname
			strcpy(paname[i],subarray[j]); //copy

	
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

			if (checkstring(Ename)) //check string
				Eliminate(Ename, '.'); //delete '.'
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

					newnode->next = Head; //link node
					Head->prev = newnode; //link node
					Head = newnode; //Declare Head
					return;
				}

				else //when the new node insert before tmp node
				{
					Node* newnode = (Node*)malloc(sizeof(Node));
					strcpy(newnode->filename, name);
					newnode->next = tmp; //link node
					newnode->prev = tmp->prev; //link node
					tmp->prev->next = newnode; //link node
					tmp->prev = newnode; //link node
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
		prevnode->next = newnode; //link node
		newnode->prev = prevnode; //link node
		Tail = newnode; //Declare Tail
		return;

	}
}

//////////////////////////////////////////////////////////////////////
// Insert function                                                  //
// ================================================================ //
// Input: char* -> Name of file                                     //
//                                                                  //
// Output: void                                                     //
//                                                                  //
// Purpose: For creating linked list sorting by size                //
//////////////////////////////////////////////////////////////////////
void NodeinsertS(char* name) //The function of inserting node to linked list
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
			struct stat buf;
			struct stat buf2;
			lstat(name,&buf); //read file
			lstat(tmp->filename,&buf2); //read file
                 //////////For checking symbol in string//////////
			strcpy(Ename, name);
			strcpy(Etmpname, tmp->filename);

			if (checkstring(Ename)) //check string
				Eliminate(Ename, '.'); //delete
			if (checkstring(Etmpname))
				Eliminate(Etmpname, '.');
		 /////////////////////////////////////////////////
			if((buf.st_size - buf2.st_size)>0)
			{
				if (tmp == Head) //when the new node insert before head node
				{
					Node* newnode = (Node*)malloc(sizeof(Node));
					strcpy(newnode->filename, name);
					newnode->prev = NULL;

					newnode->next = Head; //link node
					Head->prev = newnode; //link node
					Head = newnode; //declare Head
					return;
				}

				else //when the new node insert before tmp node
				{
					Node* newnode = (Node*)malloc(sizeof(Node));
					strcpy(newnode->filename, name);
					newnode->next = tmp; //link node
					newnode->prev = tmp->prev; //link node
					tmp->prev->next = newnode; //link node 
					tmp->prev = newnode; //link node
					return;
				}
			}

			else if ((buf.st_size - buf2.st_size)==0&&strcasecmp(Etmpname, Ename)>0) //compare string
			{
				if (tmp == Head) //when the new node insert before head node
				{
					Node* newnode = (Node*)malloc(sizeof(Node));
					strcpy(newnode->filename, name);
					newnode->prev = NULL;

					newnode->next = Head; //link node
					Head->prev = newnode; //link node
					Head = newnode; //declare Head
					return;
				}

				else //when the new node insert before tmp node
				{
					Node* newnode = (Node*)malloc(sizeof(Node));
					strcpy(newnode->filename, name);
					newnode->next = tmp; //link node
					newnode->prev = tmp->prev; //link node
					tmp->prev->next = newnode; //link node
					tmp->prev = newnode; //link node
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
		prevnode->next = newnode; //link node
		newnode->prev = prevnode; //link node
		Tail = newnode; //declare Tail
		return;

	}
}


//////////////////////////////////////////////////////////////////////
// For matching command function                                    //
// ================================================================ //
// Input: char** -> Information of parameter                        //
//	  int -> argment count                                      //
//                                                                  //
// Output: int  -> New count of argc                                //
//                                                                  //
// Purpose: For checking match command from parameter               //
//////////////////////////////////////////////////////////////////////
int matchfunction(char (*paname)[256], int argc)
{
	char Matchcmd[256][256]={0};
	int matchcount=0;

///////////////////////////////////////////////////////searching match command////////////////////////////////////////////////////////
	for(int i=1;i<argc;i++) //for check all command
	{
		for(int j=0;j<sizeof(paname[i]);j++)
		{
			if(paname[i][j]=='?' || paname[i][j]=='*') //if the command has '*' or '?'
			{
				strcpy(Matchcmd[matchcount],paname[i]); //copy
				matchcount++; //increase
				break;
			}
			else if(paname[i][j]=='[' && ((paname[i][j+1]>47&&paname[i][j+1]<58) || (paname[i][j+1]>64&&paname[i][j+1]<90) || (paname[i][j+1]>96&&paname[i][j+1]<123))
				&& paname[i][j+2]=='-' && ((paname[i][j+3]>47&&paname[i][j+3]<58) || (paname[i][j+3]>64&&paname[i][j+3]<90) || (paname[i][j+3]>96&&paname[i][j+3]<123)) && paname[i][j+4]==']') //if the command has 'index'
			{
				strcpy(Matchcmd[matchcount],paname[i]); //copy
				matchcount++; //increase
				break;
			}
			else if(paname[i][j]=='[' && ((paname[i][j+1]>47&&paname[i][j+1]<58) || (paname[i][j+1]>64&&paname[i][j+1]<90) || (paname[i][j+1]>96&&paname[i][j+1]<123))
				&& paname[i][j+2]==']')  //if the command has 'index'
			{
				strcpy(Matchcmd[matchcount],paname[i]); //copy
				matchcount++; //increase
				break;
			}
		}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////delete match cmd////////////////////////////////////////////////////////////////////////////
	for(int i=0;i<matchcount;i++) //check all cmd
	{
		for(int j=1;j<argc;j++)
		{
			if(!strcmp(paname[j],Matchcmd[i])) //if the command is matching
			{
				for(int k=j;k<argc;k++)
					strcpy(paname[k],paname[k+1]); //delete
				
				argc--; //decrease count
				break;
			}
		}
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int newargc=argc; //integer
	int flag=0; //integer
	struct dirent *dir;
	struct stat buf;
	DIR *dirp;
	char pathname[256][256]={0};
	char cmd[256][256]={0};

	for(int i=0;i<matchcount;i++) //for check match command
	{
		int j=0;
		for(;Matchcmd[i][j]!='\0';j++); //move pointer to end
		for(;Matchcmd[i][j]!='/'&&j!=0;j--); //search charcater of '/'
	
		for(int a=0;a<j;a++)
		{	
			pathname[i][a]=Matchcmd[i][a]; //copy path of command
			pathname[i][a+1]='\0'; //save null
		}

		for(int a=0,b=j;Matchcmd[i][a]!='\0';a++,b++)
		{
			cmd[i][a]=Matchcmd[i][b]; //copy of match command
			cmd[i][a+1]='\0'; //save null
		}
		
	}
	

	for(int j=0;j<matchcount;j++) //for check command
	{
		int currentflag=0; //declare flag
		
		if(cmd[j][0]=='/') //delete '/'
			for(int i=0;cmd[j][i]!='\0';i++)
				cmd[j][i]=cmd[j][i+1];

		if(strlen(pathname[j])==0) //check path name
			dirp=opendir(".");
		else
		{
			currentflag=1; //on flag
			dirp=opendir(pathname[j]); //open pathname directory
		}
		chdir((char *)getenv("PWD")); //change directory

		
		if(dirp==NULL) //Check null
		{
			strcpy(paname[newargc],Matchcmd[j]); //command return parameter
			newargc++; //increase
			continue;
		}

		
		do
		{

			dir = readdir(dirp); //read file		
			if (dir == NULL) //check NULL
				break; //stop repeat functsion

			else
			{
				if(!fnmatch(cmd[j],dir->d_name,0)&&(dir->d_name[0]!='.')) //function of match
				{
					//printf("%s\n",cmd[j]);
		

					char realpath[256]={0}; //for real path
					
					strcat(realpath,pathname[j]); //for full format of path
					if(currentflag==1)
						strcat(realpath,"/");
					strcat(realpath,dir->d_name);
					
					strcpy(paname[newargc],realpath); //copy string
					newargc++;
					flag=1; //on flag
				}
			}

		} while (1);

		if(flag==0) //if flag is 0
		{
			strcpy(paname[newargc],Matchcmd[j]); //copy command
			newargc++;
		}
		flag=0; //off flag
		rewinddir(dirp); //rewind
	} 
	return newargc; //return new vector count
	
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
	if(str[0]!='.')
		return 0;
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
// Checking function                                                //
// ================================================================ //
// Input: char* -> The string is checked                            //
//                                                                  //
// Output: void                                                     //
//                                                                  //
// Purpose: For eliminating '/' symbol                              //
//////////////////////////////////////////////////////////////////////
int checkexist(char* str)
{
	for(int i=0;str[i]!='\0';i++) //cehck string
	{
		if(str[i]=='/') //if match '/'
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
		return('-'); //return -
	case S_IFDIR:
		return('d'); //return d
	case S_IFCHR:
		return('c'); //return c
	case S_IFBLK:
		return('b'); //return b
	case S_IFLNK:
		return('l'); //return l
	case S_IFIFO:
		return('p'); //return p
	case S_IFSOCK:
		return('s'); //return s
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
	strcpy(perms, "---------"); //setting base permission

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
	if ((mode & S_ISUID) != 0) //check mode
		perms[2] = 's';

	if ((mode & S_ISGID) != 0) //check mode
		perms[5] = 's';

	if ((mode & S_ISVTX) != 0) //check mode
		perms[8] = 't';

	return(perms); //return permission
}
