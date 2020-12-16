//////////////////////////////////////////////////////////////////////
//File Name         :web_server.c                                   //
//Date              :2019/05/24                                     //
//Os                :Ubuntu 16.04 LTS 64bits                        //
//Author            :Jeong yong hoon                                //
//Student ID        :2015722025                                     //
//------------------------------------------------------------------//
//Title : System Programing Assignment #3-3 (Web_server)            //
//Description : The 3-3 task is to implement a server that follows  //
//              a power of 3-2 and allows multiple clients to access//
//              simultaneously through the fork and signal functions//
//              and performs certain actions repeatedly. It also    //
//              allows access to only the additionally allowed IPs. //
//              Although there is little difficulty in implementing //
//              it, it is thought to be an important task to        //
//              understand conceptually.                            //
//////////////////////////////////////////////////////////////////////
#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
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
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<signal.h>
#include<sys/wait.h>

#define URL_LEN 256
#define BUFSIZE 1024
#define PORTNO 40229


typedef struct Node //The struct for linked list
{
	char filename[256]; //information
	struct Node *next; //next
	struct Node *prev; //prev
}Node;

typedef struct p_info
{
	int Num;
	char IP[50];
	int Pid;
	int Portnum;
	char Atime[50];
	struct p_info *next;
}p_info;

Node *Head = NULL; //Head of linked list
Node *Tail = NULL; //Tail of linked list

p_info *Info_Head = NULL;

int flagA = 0, flagL = 0, flagh = 0, flagS = 0, flagr = 0; //value of option
int Nofilecount = 0, Filecount = 0, Optioncount = 0, Directorycount = 0;
int excount = 1; //excution count

int HTMLflag = 0;
int Noparameter = 0;

void Nodeinsert(char* fname);

void deletelist();
int checkstring(char* str);
void Eliminate(char *str, char ch);
char *printPerm(mode_t mode);
char printType(mode_t mode);
void NodeinsertS(char* name);
int matchfunction(char(*paname)[256], int argc);
void sortingfile(char(*paname)[256], int argc);
int checkexist(char* str);
int Opswitch=0;
int urlswitch=0;
int urlcount=0;
int status;
int Con_count=0;

void printOph(long int sizem, FILE *file);
void printfileHTML(FILE *file, int flagA, int flagL, char *name);
void printHTML(int client_fd, FILE *file, int flagA, int flagL, int total, char *dirpath);
void printHTMLr(int client_fd, FILE *file, int flagA, int flagL, int total, int argc, char *dirpath);

int Image(char *urlname, int client_fd, unsigned char *image_message);
int Html(char* url,int client_fd,unsigned char *html_message);
int Normal(char *urlname,int client_fd,unsigned char *normal_message);
int Notfound(unsigned char* response_message,char* urlname);
int Deny(unsigned char* response_message,char* a_IP);
void UpdateInfo(struct sockaddr_in client_addr,int PID);
void PrintInfo();
int duplication_ico(char* name);


//////////////////////////////////////////////////////////////////////
// Declare working according to signal                              //
// ================================================================ //
// Input: int -> Signal                                             //
//                                                                  //
// Output:                                                          //
//                                                                  //
// Purpose: Declare working from signal                             //
//////////////////////////////////////////////////////////////////////
void signalHandler(int sig)
{
	if(sig == SIGALRM) //alram signal
	{
		PrintInfo(); //print information of history
		alarm(10); //10 second, alram signal
	}

	if(sig == SIGCHLD) //Child die signal
		wait(&status); //wait and get pid
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
	signal(SIGCHLD, signalHandler);
	signal(SIGALRM, signalHandler);

	int c = 0;
	int height = 2;
	DIR *dirp;

	struct dirent *dir;
	struct stat buf,Rbuf;
	struct group *gid;
	struct passwd *uid;

	struct tm *time;
	char buff[256];

	int argcount = 0;
	int total = 0;
	char swap[256];
	char Subargv[256][256] = { '\0' };
	char match[256];
	int count = 1;
	char NULLpath[256] = { 0 };

	int NofilePcount = 0;
	int filePcount = 0;
	char title[256] = { 0 };
	char cwd[256]={0, };

	////////////////////////Server value////////////////////////
	struct sockaddr_in server_addr, client_addr;
	int socket_fd, client_fd;
	int len, len_out;
	int opt = 1;
	////////////////////////////////////////////////////////////

	getcwd(title, sizeof(title)); //load current working directory
	getcwd(cwd, sizeof(cwd)); //load current working directory
	
	for(int i=0;cwd[i]!='\0';i++)
	{
		if(cwd[i]=='/')
			urlcount++;
	}

	////////////////////////For Connecting Server////////////////////////
	if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0))<0)
	{
		printf("Server : Can't open stream socket\n");
		return 0;
	}

	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORTNO);

	if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))<0)
	{
		printf("Server : Cna't bind local address\n");
		return 0;
	}

	listen(socket_fd, 5);
	alarm(10);
	////////////////////////////////////////////////////////////////////

	while (1) //start server
	{
		struct in_addr inet_client_address;
		char Sbuf[BUFSIZE] = { 0, };
		char tmp[BUFSIZE] = { 0, };
		char response_header[BUFSIZE] = { 0, };
		char response_message[BUFSIZE] = { 0, };
		char url[URL_LEN] = { 0, };
		char method[20] = { 0, };
		char * tok = NULL;
		FILE *a_file;
		char a_usr[256]={0, };
		int PID;
		int status;

		len = sizeof(client_addr);
		client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &len); //accept client
		if (client_fd<0)
		{
			printf("Server : accept failed\n");
			return 0;
		}

		if((a_file=fopen("accessible.usr","r"))==NULL) //for checking deny address
		{
			printf("File : open failed\n");
			return 0;
		}

		int a_flag=0; //flag
		while(fgets(a_usr,sizeof(a_usr),a_file)) //load information of address
		{
			int i;
			for(i=0;a_usr[i]!='\n';i++); //delete enter
			a_usr[i]='\0'; //insert NULL
	
			if(fnmatch(a_usr,inet_ntoa(client_addr.sin_addr),0)==0) //check match
				a_flag=1; //on flag		
		}

		if (a_flag==0)
		{	
			long unsigned int filesize=0; //file size
			unsigned char html_message[3000000]={0, }; //message buffer
			
			filesize=Deny(html_message,inet_ntoa(client_addr.sin_addr));
			sprintf(response_header, //Declare message of header
			"HTTP/1.0 403.6 Access denied\r\n"
			"Server:2019 simple web server\r\n"
			"Content-length:%lu\r\n"
			"Content-type:text/html\r\n\r\n", filesize);
		
			write(client_fd, response_header, strlen(response_header)); //send header
			write(client_fd, html_message, filesize); //send entity
			continue;
		}
			
		inet_client_address.s_addr = client_addr.sin_addr.s_addr;
		read(client_fd, Sbuf, BUFSIZE); //read
		strcpy(tmp, Sbuf);
		if(duplication_ico(tmp)<0) continue ;//check favicon.ico
		if(Sbuf[0]=='\0') continue; //for detecting autometic connection

		if((PID=fork())>0)
		{
			UpdateInfo(client_addr,PID); //update information of history
			continue;
		}
		
		else
		{
			printf("============= New client =============\n");
			printf("IP : %s\n",inet_ntoa(client_addr.sin_addr));
			printf("Port : %d\n",client_addr.sin_port);
			printf("PID : %d\n",getpid());
			printf("======================================\n");
		
			tok = strtok(tmp, " ");
			strcpy(method, tok);
			if (strcmp(method, "GET") == 0) //for save information of url
			{
				tok = strtok(NULL, " ");
				strcpy(url, tok);
			}
			int c=0;
			for(;url[c]!='\0';c++);
			if(c!=1&&url[c-1]=='/')
				urlswitch=1;

			////////////////////////////Declare head///////////////////////////////////////////////
			char urlname[256]={0,};
				for(int i=1;url[i];i++)
					urlname[i-1]=url[i];
			char real[256]={0,};
		
			realpath(urlname,real); //load real path
			lstat(urlname,&buf); //read rulname for checking directory
			lstat(real, &Rbuf); //for link path

			if(fnmatch("*.jpg",urlname,FNM_CASEFOLD)==0|| //check type of file (Image)
			   fnmatch("*.png",urlname,FNM_CASEFOLD)==0||
			   fnmatch("*.jpeg",urlname,FNM_CASEFOLD)==0||
			   fnmatch("*.jpg",real,FNM_CASEFOLD)==0||
			   fnmatch("*.png",real,FNM_CASEFOLD)==0||
			   fnmatch("*.jpeg",real,FNM_CASEFOLD)==0)
			{
				long unsigned int filesize=0; //file size
				unsigned char image_message[3000000]={0, }; //message buffer
				filesize=Image(urlname,client_fd,image_message); //return size of file

				if(filesize==-1) //check not found
				{
					filesize=Notfound(image_message,urlname);
					sprintf(response_header, //Declare message of header
					"HTTP/1.0 404 Notfound\r\n"
					"Server:2019 simple web server\r\n"
					"Content-length:%lu\r\n"
					"Content-type:text/html\r\n\r\n", filesize);
				}

				else
				{			
					sprintf(response_header, //Declare message of header
					"HTTP/1.0 200 OK\r\n"
					"Server:2019 simple web server\r\n"
					"Content-length:%lu\r\n"
					"Content-type:image/*\r\n\r\n",filesize);
				}
				write(client_fd, response_header, strlen(response_header)); //send header
				write(client_fd, image_message, filesize); //send entity
			}
		
			else if(S_ISDIR(buf.st_mode)||S_ISDIR(Rbuf.st_mode)||!strcmp(urlname,"\0")) //check type of file (Directory)
			{	long unsigned int filesize=0; //file size
				unsigned char html_message[3000000]={0, }; //message buffer
				filesize=Html(url,client_fd,html_message); //return size of file

				if(filesize==-1) //check not found
				{
					filesize=Notfound(html_message,urlname);
					sprintf(response_header, //Declare message of header
					"HTTP/1.0 404 Notfound\r\n"
					"Server:2019 simple web server\r\n"
					"Content-length:%lu\r\n"
					"Content-type:text/html\r\n\r\n", filesize);
				}

				else
				{
					sprintf(response_header, //Declare message of header
					"HTTP/1.0 200 OK\r\n"
					"Server:2019 simple web server\r\n"
					"Content-length:%lu\r\n"
					"Content-type:text/html\r\n\r\n", filesize);
				}
				write(client_fd, response_header, strlen(response_header)); //send header
				write(client_fd, html_message, filesize); //send entity
			}

			else //type of others
			{
				long unsigned int filesize=0; //file size
				unsigned char normal_message[3000000]={0, }; //message buffer
				filesize=Normal(urlname,client_fd,normal_message); //return size of file
			
				if(filesize==-1) //check not found
				{
					filesize=Notfound(normal_message,urlname);
					sprintf(response_header, //Declare message of header
					"HTTP/1.0 404 Notfound\r\n"
					"Server:2019 simple web server\r\n"
					"Content-length:%lu\r\n"
					"Content-type:text/html\r\n\r\n", filesize);
				}

				else
				{
					sprintf(response_header, //Declare message of header
					"HTTP/1.0 200 OK\r\n"
					"Server:2019 simple web server\r\n"
					"Content-length:%lu\r\n"
					"Content-type:text/plain\r\n\r\n", filesize);
				}
				write(client_fd, response_header, strlen(response_header)); //send header
				write(client_fd, normal_message, filesize); //send entityW
			
			}
			printf("========= Disconeected Client ========\n");
			printf("IP : %s\n",inet_ntoa(client_addr.sin_addr));
			printf("Port : %d\n",client_addr.sin_port);
			printf("======================================\n");

			close(client_fd); //close client			
			exit(0);
		}
	}
	close(socket_fd); //close socket
	return 0;
}

//////////////////////////////////////////////////////////////////////
// For updating list of history                                     //
// ================================================================ //
// Input: struct sockaddr_in -> For catching client address         //
//        int -> For loading Pid                                    //
//                                                                  //                                                       
// Output:                                                          //
//                                                                  //
// Purpose: Update list                                             //
//////////////////////////////////////////////////////////////////////
void UpdateInfo(struct sockaddr_in client_addr,int PID)
{
	p_info* newnode = (p_info*)malloc(sizeof(p_info)); //create node of information
	
	time_t cur_time=time(NULL); //current time
      	char time_buf[256]={0,}; //time buffer
      	strcpy(time_buf,asctime(localtime(&cur_time))); // time string

	if(Info_Head==NULL) //if head is NULL
	{
		newnode->Num=1; //number of list
		strcpy(newnode->IP,inet_ntoa(client_addr.sin_addr)); //declare information of node
		newnode->Portnum=client_addr.sin_port;
		newnode->Pid=PID;
		strcpy(newnode->Atime,time_buf);
		newnode->next=NULL;
		Info_Head=newnode; //declare head
		Con_count++; //increase count
	}

	else //If exist list
	{
		int count=0;
		newnode->Num=0;
		strcpy(newnode->IP,inet_ntoa(client_addr.sin_addr)); //declare information of node
		newnode->Portnum=client_addr.sin_port;
		newnode->Pid=PID;
		strcpy(newnode->Atime,time_buf);
		newnode->next=Info_Head; //For link node
		Info_Head=newnode; //change head

		for(p_info *tmp=Info_Head;tmp && count<10;tmp=tmp->next, count++) //Declare new number of list
			tmp->Num++;
		Con_count++; //increase count
	}
}

//////////////////////////////////////////////////////////////////////
// For printing history of connecting                               //
// ================================================================ //
// Input:                                                           //
//                                                                  //
//                                                                  //
// Output:                                                          //
//                                                                  //
// Purpose: For print history                                       //
//////////////////////////////////////////////////////////////////////
void PrintInfo()
{	
	int count=0; //For printing number of 10
	printf("========= Connection History =========\n");
	printf("Number of request(s) : %d\n",Con_count);
	printf("NO.\tIP\t\tPID\tPORT\tTIME\n");
	for(p_info *tmp=Info_Head;tmp && count<10;tmp=tmp->next, count++) //repeat function
	{ //End list of print 10
		printf("%d\t",tmp->Num);
		printf("%s\t",tmp->IP);
		printf("%d\t",tmp->Pid);
		printf("%d\t",tmp->Portnum);
		printf("%s",tmp->Atime);
	}
	return;
}

//////////////////////////////////////////////////////////////////////
// Deny                                                             //
// ================================================================ //
// Input: unsionged char* -> For saving Denied page                 //
//        char * -> For saveing IP                                  //
//                                                                  //
// Output: int -> size of message                                   //
//                                                                  //
// Purpose: For sending size of message and Denied page             //
//////////////////////////////////////////////////////////////////////
int Deny(unsigned char* response_message,char *a_IP)
{
	sprintf(response_message, //Save not found page to message buffeer
	"<html>\n"
	"<h1>Access denied!</h1><br>\n"
	"<h2>Your IP : %s</h2>\n"
	"<h4>You havev no permission to access this web server.</h4>\n"
	"<h4>HTTP 403.6 - Forbidden: IP address reject</h4>\n",a_IP);

	return strlen(response_message); //return size of message
}

//////////////////////////////////////////////////////////////////////
// Notfound                                                         //
// ================================================================ //
// Input: unsionged char* -> For saving Not found page              //
//        char * -> For saveing path of not exist                   //
//                                                                  //
// Output: int -> size of message                                   //
//                                                                  //
// Purpose: For sending size of message and Not found page          //
//////////////////////////////////////////////////////////////////////
int Notfound(unsigned char* response_message,char* urlname)
{
	sprintf(response_message, //Save not found page to message buffeer
	"<html>\n"
	"<h1>Not Found</h1><br>\n"
	"<h4>The request URL<a style=color:red> /%s </a>was not found on this server</h4>\n"
	"<h4>HTTP 404 - Not Page Found</h4>\n",urlname);

	return strlen(response_message); //return size of message
}

//////////////////////////////////////////////////////////////////////
// Normal                                                           //
// ================================================================ //
// Input: unsionged char* -> For saving information of file         //
//        char * -> For checking path of url                        //
//        int    -> Number of client                                //
//                                                                  //
// Output: int -> size of message                                   //
//                                                                  //
// Purpose: For sending size of message and checking exist file     //
//////////////////////////////////////////////////////////////////////
int Normal(char *urlname,int client_fd,unsigned char *normal_message)
{
	char urlpath[256]={0};
	char urlfile[256]={0};
	char cwd[256]={0};
	char Openpath[256]={0};
	char Dirpath[256]={0};
	int searching=0;
	
	unsigned char response_message[3000000]={0, };
	struct stat buf;
	DIR *dirp;
	struct dirent *dir;

	getcwd(cwd, sizeof(cwd)); //load current working directory
	strcpy(urlpath,urlname);

	int i=0,j=0,count=0; //Make url
	for(;urlpath[i]!='\0';i++);
	for(;urlpath[i]!='/'&&i!=0;i--);
	if(urlpath[i]=='/')
		i++;
	for(;urlpath[i]!='\0';i++,j++) //for make url path
		urlfile[j]=urlpath[i];
	
	for(;urlpath[i]!='/'&&i!=0;i--); //rewind
	
	strcpy(Openpath,cwd); //copy current working directory

	if(i!=0)
		strcat(Openpath,"/");
	for(j=0;j<i;j++) //copy path
		Dirpath[j]=urlpath[j];

	strcat(Openpath,Dirpath);

////////////////////////open dir for checking image file////////////////////////////
	if((dirp = opendir(Openpath))==NULL)
		return -1;

	chdir(Openpath); //change directory
		do
		{
			dir = readdir(dirp); //read file

			if (dir == NULL) //check NULL
				break; //stop repeat functsion

			else if(!strcmp(urlfile,dir->d_name))
			{
				searching=1; //if exist file
				FILE *file=NULL;

				int ch;
				if((file=fopen(dir->d_name,"rb"))==NULL) //open file (read binary)
				{
					fputs("Error!",stderr);
					exit(1);
				}

				while((ch=fgetc(file))!=EOF) //load information before EOF
					normal_message[count++]=ch; //save information to buffer
			
				fclose(file); //close file
				break;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Declare response message
			}
		} while (1);
	chdir((char *)getenv("PWD")); //change directory

	if(searching==1)
		return count;

	return -1; //response Not found	
}

//////////////////////////////////////////////////////////////////////
// Html                                                             //
// ================================================================ //
// Input: unsionged char* -> For saving Not found page              //
//        char * -> For saveing path of not exist                   //
//                                                                  //
// Output: int -> size of message                                   //
//                                                                  //
// Purpose: For sending size of message and Not found page          //
//////////////////////////////////////////////////////////////////////
int Html(char *url,int client_fd,unsigned char *html_message)
{
	DIR *dirp;
	struct dirent *dir;
	struct stat buf;
	struct group *gid;
	struct passwd *uid;
	struct tm *time;
	FILE *htmlfile;
	struct sockaddr_in server_addr, client_addr;
	struct in_addr inet_client_address;
	
	int total = 0,count=0;
	char response_message[3000000] = { 0, };
	char NULLpath[256]={0, };

	//////////////////////////////////////Open DIR and wirte/////////////////////////////////////////////////
	htmlfile=fopen("html_ls.html","w"); //file open for HTML
	
	if(strlen(url)==1)
	{
		Opswitch=1;
		dirp = opendir("."); //open current directory
		chdir("."); //change directory
	
		do
		{
			dir = readdir(dirp); //read file

			if (dir == NULL) //check NULL
				break; //stop repeat functsion

			else
			{
				lstat(dir->d_name, &buf);
				if (flagA != 0 || dir->d_name[0] != '.') //check hidden file
					total += buf.st_blocks / 2;
				Nodeinsert(dir->d_name); //insert node
			}

		} while (1);
	}

	else
	{
		Opswitch=0;
		char urlpath[256]={0,};
		for(int i=1;url[i];i++)
			urlpath[i-1]=url[i];

		if((dirp = opendir(urlpath))==NULL) //open current directory
			return -1;

		chdir(urlpath); //change directory
		do
		{
			dir = readdir(dirp); //read file

			if (dir == NULL) //check NULL
				break; //stop repeat functsion

			else
			{
				lstat(dir->d_name, &buf);
				if (flagA != 0 || dir->d_name[0] != '.') //check hidden file
					total += buf.st_blocks / 2;
					Nodeinsert(dir->d_name); //insert node
			}

		} while (1);
	}


	if(strlen(url)==1) //root path
	{
		strcpy(response_message, "<h1>Welcome to System Programming Http</h1><br>\n"); //copy
		fprintf(htmlfile,"<h1>Welcome to System Programming Http</h1><br>\n"); //write to file
	}
		
	else
	{
		strcpy(response_message, "<h1>System Programming Http</h1><br>\n"); //copy
		fprintf(htmlfile,"<h1>System Programming Http</h1><br>\n"); //write to file
	}
		printHTML(client_fd, htmlfile, flagA, flagL, total, NULLpath); //For write to file all information of file

		deletelist(); //delete list
		chdir((char *)getenv("PWD")); //change directory
		total = 0;
		fclose(htmlfile); //close file

		FILE *file=NULL;

		if((file=fopen("html_ls.html","rb"))==NULL) //open html file
		{
			fputs("Error!",stderr);
			exit(1);
		}

		int ch;
		while((ch=fgetc(file))!=EOF) //read file before EOF
			html_message[count++]=ch; //save information to message
			
		fclose(file); //close file
			
	return count; //return file size
}

//////////////////////////////////////////////////////////////////////
// Image                                                            //
// ================================================================ //
// Input: unsionged char* -> For saving information of image        //
//        char * -> For checking path of url                        //
//        int    -> Number of client                                //
//                                                                  //
// Output: int -> size of message                                   //
//                                                                  //
// Purpose: For sending size of message and checking exist file     //
//////////////////////////////////////////////////////////////////////
int Image(char *urlname, int client_fd,unsigned char *image_message)
{
	char urlpath[256]={0};
	char urlfile[256]={0};
	char cwd[256]={0};
	char Openpath[256]={0};
	char Dirpath[256]={0};
	int searching=0;
	unsigned char response_message[3000000]={0, };
	struct stat buf;
	DIR *dirp;
	struct dirent *dir;

	getcwd(cwd, sizeof(cwd)); //load current working director
	strcpy(urlpath,urlname);

	int i=0,j=0,count=0;
	for(;urlpath[i]!='\0';i++); //for make url path
	for(;urlpath[i]!='/'&&i!=0;i--);
	if(urlpath[i]=='/')
		i++;
	for(;urlpath[i]!='\0';i++,j++) //for make url path
		urlfile[j]=urlpath[i];
	for(;urlpath[i]!='/'&&i!=0;i--); //rewind
	strcpy(Openpath,cwd);

	if(i!=0)
		strcat(Openpath,"/");
	for(j=0;j<i;j++) //copy path
		Dirpath[j]=urlpath[j];
	strcat(Openpath,Dirpath);


////////////////////////open dir for checking image file////////////////////////////
	if((dirp = opendir(Openpath))==NULL) //open directory
		return -1;

	chdir(Openpath); //change directory
		do
		{
			dir = readdir(dirp); //read file

			if (dir == NULL) //check NULL
				break; //stop repeat functsion

			else if(!strcmp(urlfile,dir->d_name)) //compare name of file
			{
				searching=1;
				FILE *file=NULL;

				int ch;
				if((file=fopen(dir->d_name,"rb"))==NULL) //open file (read binary mode)
				{
					fputs("Error!",stderr);
					exit(1);
				}

				while((ch=fgetc(file))!=EOF) //repeat function until before EOF
					image_message[count++]=ch; //save information to message
				
				fclose(file); //close file
				break;

			}
		} while (1);
	chdir((char *)getenv("PWD")); //change directory

	if(searching==1)
		return count; //return size

	return -1; //response Not found	
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
void printHTML(int client_fd, FILE* file, int flagA, int flagL, int total, char *dirpath)
{
	struct group *gid;
	struct passwd *uid;
	struct tm *time;
	char buff[256];
	char cwd[256];
	struct stat buf;
	struct dirent *dir;

	int k = 0, m = 0;
	char subpath[256] = { 0 };
	char subdirpath[256] = { 0 };
	char checkpath[256] = { 0 };
	char color[256] = { 0 };

	int createflag = 0;
	char content[BUFSIZE] = { 0, };

	getcwd(cwd, sizeof(cwd)); //load current working directory

	for (k=0; cwd[k] != '\0'; k++); //for make path
	for (; cwd[k] != '/'; k--);
	for (; m < k; m++)
		subpath[m] = cwd[m];

	for (k = 0; dirpath[k] != '\0'; k++); //move pointer to end
	for (; dirpath[k] != '/'&&k != 0; k--); //search '/'
	if (dirpath[k] == '/') k++; //check character
	for (m = 0; dirpath[k] != '\0'; m++, k++)
		subdirpath[m] = dirpath[k];

	strcat(checkpath, subpath); //letter aggregation
	strcat(checkpath, "/"); //letter aggregation
	strcat(checkpath, subdirpath); //letter aggregation
								 
	lstat(checkpath, &buf); //read type of file
	if (S_ISLNK(buf.st_mode))
		strcpy(cwd, checkpath);

	sprintf(content, "<title>/home/sp2015722025/work</title>\n");
	fprintf(file, "<title>/home/sp2015722025/work</title>\n");

	sprintf(content, "<h3>Directory path : %s</h3>\n", cwd);
	fprintf(file, "<h3>Directory path : %s</h3>\n", cwd);

	sprintf(content, "<h3>total %d</h3>\n", total); //print format of html
	fprintf(file, "<h3>total %d</h3>\n", total); //print format of html


	if (createflag == 0)
	{
		sprintf(content, "<body>\n"); //print format of html
		fprintf(file, "<body>\n"); //print format of html
		
		sprintf(content, "<table border=1>\n"); //print format of html
		fprintf(file, "<table border=1>\n"); //print format of html

		sprintf(content, "<tr><th>Name</th><th>Permission</th><th>Link</th><th>Owner</th><th>Group</th><th>Size</th><th>Last Modified</th></tr>\n"); //print format of html
		fprintf(file, "<tr><th>Name</th><th>Permission</th><th>Link</th><th>Owner</th><th>Group</th><th>Size</th><th>Last Modified</th></tr>\n"); //print format of html
			
		createflag = 1;
	}

	for (Node* tmp=Head; tmp; tmp = tmp->next) //Repeat function for printing all list
	{
		if(Opswitch==1&&tmp->filename[0]=='.')
			continue;
		if(!strcmp(tmp->filename,"html_ls.html"))
			continue;
		lstat(tmp->filename, &buf); //read file

		strcpy(color, "style=color:red"); //check type of file or directory
		if (S_ISDIR(buf.st_mode))
			strcpy(color, "style=color:blue"); //blue
		else if (S_ISLNK(buf.st_mode))
			strcpy(color, "style=color:green"); //green
		
		char *tok;
		char urlpath[256]={0, };
		char newurlpath[256]={0, };
		int Rootsignal=0;
		int comparecount=urlcount-2;
		getcwd(cwd, sizeof(cwd)); //load current working directory
		chdir(cwd);

		int CUcount=0; //for check base count of '/' from url
		for(int i=0;cwd[i]!='\0';i++)
		{
			if(cwd[i]=='/')
				CUcount++;
		}

		if(urlcount==CUcount) //home url
			strcpy(urlpath,"\0");
		else //else
		{ //make path of url
			int Uc=0, Ucount=0;
			for(;cwd[Uc]!='\0';Uc++)
			{
				if(cwd[Uc]=='/')
					Ucount++;
				if(Ucount==urlcount+1)
					break;
			}
			for(int i=0;cwd[Uc]!='\0';Uc++,i++)
				urlpath[i]=cwd[Uc];
			strcat(urlpath,"/");
		}	

		if(!strcmp(tmp->filename,".")) //current url
			urlpath[strlen(urlpath)-1]='\0';
		
		else
			strcat(urlpath,tmp->filename); //make full format of url path
		
		if(urlswitch==1) //check signal
		{
			strcpy(urlpath,tmp->filename);
			/*int i=0,j=0;
			char save[256]={0, };
			for(;urlpath[i]!='/'&&urlpath[i]!='\0';i++);
				i++;
			
			for(;urlpath[i]!='\0';i++,j++)
				save[j]=urlpath[i];

			strcpy(urlpath,save); //copy path*/
		}

		uid = getpwuid(buf.st_uid); //get user id
		gid = getgrgid(buf.st_gid); //get group id

		time = localtime(&buf.st_mtime);//save time of fixed file

		if (printType(buf.st_mode) == 'l') //for printing link file
		{
			char link[256];
			char realp[256];
			int i = 0;
			int j = 0;

			realpath(tmp->filename, link); //real path of link file
			for (; link[i] != '\0'; i++); //move pointer to end
			for (; link[i] != '/'; i--); //search '/'
			for (; link[i] != '\0'; i++, j++)
				realp[j] = link[i + 1];
			realp[j + 1] = '\0';
			strcat(tmp->filename, "->"); //letter aggregation
			strcat(tmp->filename, realp); //letter aggregation
		}
		strftime(buff, 255, "%b %d %H:%M", time);
		
		sprintf(content, "<tr %s><td><a href=%s>%s</a></td>\n", color, urlpath, tmp->filename); //print format of html
		fprintf(file, "<tr %s><td><a href=%s>%s</a></td>\n", color, urlpath, tmp->filename); //print format of html

		sprintf(content, "<td>%c%s</td>\n", printType(buf.st_mode), printPerm(buf.st_mode)); //print format of html
		fprintf(file, "<td>%c%s</td>\n", printType(buf.st_mode), printPerm(buf.st_mode)); //print format of htm

		sprintf(content, "<td>%ld</td>\n", buf.st_nlink); //print format of html
		fprintf(file, "<td>%ld</td>\n", buf.st_nlink); //print format of html

		sprintf(content, "<td>%s</td>\n", uid->pw_name); //print format of html
		fprintf(file, "<td>%s</td>\n", uid->pw_name); //print format of html

		sprintf(content, "<td>%s</td>\n", gid->gr_name); //print format of html
		fprintf(file,"<td>%s</td>\n", gid->gr_name); //print format of html
	
		sprintf(content, "<td>%ld\t</td>\n", buf.st_size); //print format of html
		fprintf(file,"<td>%ld\t</td>\n", buf.st_size); //print format of html
	
		sprintf(content, "<td>%s</td></tr>\n", buff); //print format of html
		fprintf(file,"<td>%s</td></tr>\n", buff); //print format of html

	}
	chdir((char *)getenv("PWD")); //change directory
	urlswitch=0;
	sprintf(content, "</table>\n</body>\n"); //end of html format
	fprintf(file,"</table>\n</body>\n"); //end of html format
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
void printHTMLr(int client_fd, FILE* file, int flagA, int flagL, int total, int argc, char *dirpath)
{
	struct group *gid;
	struct passwd *uid;
	struct tm *time;
	char buff[256];
	char cwd[256];
	struct stat buf;
	struct dirent *dir;

	int k = 0, m = 0;
	char subpath[256] = { 0 };
	char subdirpath[256] = { 0 };
	char checkpath[256] = { 0 };
	char color[256] = { 0 };

	int createflag = 0;


	getcwd(cwd, sizeof(cwd)); //load current working directory

	if (flagL == 1 || argc>2) //check option if '-l'
	{
		//getcwd(cwd, sizeof(cwd)); //load current working directory
		for (; cwd[k] != '\0'; k++);
		for (; cwd[k] != '/'; k--);
		for (; m<k; m++)
			subpath[m] = cwd[m];

		for (k = 0; dirpath[k] != '\0'; k++); //move pointer to end
		for (; dirpath[k] != '/'&&k != 0; k--); //search '/'
		if (dirpath[k] == '/') k++; //check character
		for (m = 0; dirpath[k] != '\0'; m++, k++)
			subdirpath[m] = dirpath[k];

		strcat(checkpath, subpath); //letter aggregation
		strcat(checkpath, "/"); //letter aggregation
		strcat(checkpath, subdirpath); //letter aggregation						

		lstat(checkpath, &buf); //read file
		if (S_ISLNK(buf.st_mode)) //check type of file
			strcpy(cwd, checkpath); //make path

		if (flagL == 0 && (Directorycount + Nofilecount + Filecount>1)) //check option
			fprintf(file, "<h3>Directory path : %s</h3>\n", cwd); //print format of html
		else if (flagL == 1 && (Directorycount + Nofilecount + Filecount>1))
		{
			fprintf(file, "<h3>Directory path : %s</h3>\n", cwd); //print format of html
			fprintf(file, "<h3>total %d</h3>\n", total); //print format of html
		}
		else if (flagL == 1)
			fprintf(file, "<h3>total %d</h3>\n", total); //print format of html

	}

	Node *tmp = Head;
	for (; tmp->next; tmp = tmp->next);
	for (; tmp; tmp = tmp->prev) //Repeat function for printing all list
	{

		int m = 0, n = 0;
		char checkname[256] = { 0 };
		for (; tmp->filename[m] != '\0'; m++);
		for (; tmp->filename[m] != '/' &&m != 0; m--);
		for (; tmp->filename[m] != '\0'; n++, m++)
			checkname[n] = tmp->filename[m];

		if (!strcmp(checkname, "html_ls.html"))
			continue;

		char hyperlink[256] = { 0 };
		strcpy(hyperlink, cwd);
		strcat(hyperlink, "/");

		if ((flagL == 1 && flagA == 0 && tmp->filename[0] != '.') || (flagL == 1 && flagA == 1))
		{ //check option of '-l'
			if (createflag == 0)
			{
				fprintf(file, "<body>\n"); //print format of html
				fprintf(file, "<table border=1>\n"); //print format of html
				if (flagL == 1)
					fprintf(file, "<tr><th>Name</th><th>Permission</th><th>Link</th><th>Owner</th><th>Group</th><th>Size</th><th>Last Modified</th></tr>\n"); //print format of html
				else
					fprintf(file, "<tr><th>Name</th></tr>\n");//print format of html
				createflag = 1;
			}


			lstat(tmp->filename, &buf); //read file

			strcpy(color, "style=color:red>"); //check type of file or directory
			if (S_ISDIR(buf.st_mode))
				strcpy(color, "style=color:blue>");
			else if (S_ISLNK(buf.st_mode))
				strcpy(color, "style=color:green>");

			strcat(hyperlink, tmp->filename);
			if (tmp->filename[0] == '/')
				strcpy(hyperlink, tmp->filename);

			uid = getpwuid(buf.st_uid); //get user id
			gid = getgrgid(buf.st_gid); //get group id

			time = localtime(&buf.st_mtime);//save time of fixed file

			if (printType(buf.st_mode) == 'l') //for printing link file
			{
				char link[256];
				char realp[256];
				int i = 0;
				int j = 0;

				realpath(tmp->filename, link); //real path of link file
				for (; link[i] != '\0'; i++); //move pointer to end
				for (; link[i] != '/'; i--); //search '/'
				for (; link[i] != '\0'; i++, j++)
					realp[j] = link[i + 1];
				realp[j + 1] = '\0';
				strcat(tmp->filename, "->"); //letter aggregation
				strcat(tmp->filename, realp); //letter aggregation
			}

			strftime(buff, 255, "%b %d %H:%M", time);

			fprintf(file, "<tr %s<td><a href=%s>%s</a></td>", color, hyperlink, tmp->filename); //print format of html
			fprintf(file, "<td>%c%s</td>", printType(buf.st_mode), printPerm(buf.st_mode)); //print format of html
			fprintf(file, "<td>%ld</td>", buf.st_nlink); //print format of html
			fprintf(file, "<td>%s</td>", uid->pw_name); //print format of html
			fprintf(file, "<td>%s</td>", gid->gr_name); //print format of html
			if (flagh == 1) //check flag h
				printOph(buf.st_size, file); //change format of size

			else
				fprintf(file, "<td>%ld\t</td>", buf.st_size); //print format of html
			fprintf(file, "<td>%s</td></tr>", buff); //print format of html

		}

		else if ((flagL == 0 && flagA == 0 && tmp->filename[0] != '.') || (flagL == 0 && flagA == 1))
		{
			if (createflag == 0)
			{
				fprintf(file, "<body>\n"); //print format of html
				fprintf(file, "<table border=1>\n"); //print format of html
				if (flagL == 1)
					fprintf(file, "<tr><th>Name</th><th>Permission</th><th>Link</th><th>Owner</th><th>Group</th><th>Size</th><th>Last Modified</th></tr>\n"); //print format of html
				else
					fprintf(file, "<tr><th>Name</th></tr>\n"); //print format of html
				createflag = 1;
			}
			strcat(hyperlink, tmp->filename); //make hyperlink
			if (tmp->filename[0] == '/') //check absolute path
				strcpy(hyperlink, tmp->filename);
			fprintf(file, "<tr><td><a href=%s>%s</a></td></tr>", hyperlink, tmp->filename); //print format of html
		}

	}
	fprintf(file, "</table>\n</body>"); //end of html format
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
void printfileHTML(FILE *file, int flagA, int flagL, char *name) //The function is equal function of printlist
{
	struct group *gid;
	struct passwd *uid;
	struct tm *time;
	char buff[256];
	char cwd[256];
	struct stat buf;
	struct dirent *dir;

	int k = 0, m = 0;
	char subpath[256] = { 0 };
	char subdirpath[256] = { 0 };
	char checkpath[256] = { 0 };

	int v = 0, n = 0;
	char checkname[256] = { 0 };
	for (; name[v] != '\0'; v++);
	for (; name[v] != '/' &&v != 0; v--);
	for (; name[v] != '\0'; n++, v++)
	{
		if (name[v] == '/')
			v++;
		checkname[n] = name[v];
	}

	if (!strcmp(checkname, "html_ls.html"))
		return;

	char hyperlink[256] = { 0 };
	getcwd(cwd, sizeof(cwd)); //load current working directory
	strcpy(hyperlink, cwd);
	strcat(hyperlink, "/");


	if ((flagL == 1 && flagA == 0 && name[0] != '.') || (flagL == 1 && flagA == 1)) //check flag and others
	{ //check option of '-l'

		lstat(name, &buf); //read file
		char color[256] = { 0 };
		strcpy(color, "red");
		if (S_ISLNK(buf.st_mode))
			strcpy(color, "green");

		uid = getpwuid(buf.st_uid); //get user id
		gid = getgrgid(buf.st_gid); //get group id

		time = localtime(&buf.st_mtime);//save time of fixed file

		char link[256];
		if (printType(buf.st_mode) == 'l') //for printing link file
		{
			char realp[256];
			int i = 0;
			int j = 0;

			realpath(name, link); //real path of link file
			for (; link[i] != '\0'; i++); //move pointer to end
			for (; link[i] != '/'; i--); //search '/'
			for (; link[i] != '\0'; i++, j++)
				realp[j] = link[i + 1];
			realp[j + 1] = '\0';
			strcat(name, "->"); //letter aggregation
			strcat(name, realp); //letter aggsregation
		}
		strftime(buff, 255, "%b %d %H:%M", time);

		strcat(hyperlink, name); //make path of hyperlink
		if (name[0] == '/') //check path of absolute
			strcpy(hyperlink, name); //change hyperlink
		if (S_ISLNK(buf.st_mode))
			strcpy(hyperlink, link);
		fprintf(file, "<tr style=color:%s><td><a href=%s>%s</a></td>", color, hyperlink, name); //print format of html
		fprintf(file, "<td>%c%s</td>", printType(buf.st_mode), printPerm(buf.st_mode)); //print format of html
		fprintf(file, "<td>%ld</td>", buf.st_nlink); //print format of html
		fprintf(file, "<td>%s</td>", uid->pw_name); //print format of html
		fprintf(file, "<td>%s</td>", gid->gr_name); //print format of html
		if (flagh == 1) //check option of h
			printOph(buf.st_size, file); //change format of size

		else
			fprintf(file, "<td>%ld\t</td>", buf.st_size); //print format of html
		fprintf(file, "<td>%s</td></tr>", buff); //print format of html

	}

	if ((flagL == 0 && flagA == 0 && name[0] != '.') || (flagL == 0 && flagA == 1)) //check flag and others
	{
		strcat(hyperlink, name); //make path of hyperlink
		if (name[0] == '/') //check path of absolute
			strcpy(hyperlink, name); //change hyperlink
		fprintf(file, "<tr><td><a href=%s>%s</a></td></tr>", hyperlink, name); //print format of html
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
void printOph(long int size, FILE *file)
{
	int k = 0, flag = 0;
	double sub_size;

	sub_size = (double)size;

	for (k = 0; 1; k++) //for check size of k(unit)
	{
		if (sub_size>(double)1024)
			sub_size /= 1024;

		else
			break;
	}
	size = (int)sub_size; //change of type
	sub_size = (int)(sub_size * 10); //Remove from decimal second
	sub_size = sub_size / 10;
	if (size * 10 == (int)(sub_size * 10)) //check first decimal point
		flag = 1;

	int size_int = 0;

	if (k == 0) //below kilobytes
	{

		size_int = (int)sub_size;
		fprintf(file, "<td>%d</td>", size_int);

	}

	else if (k == 1) //kilobytes
	{
		if (flag == 1) //flag of intger
		{
			size_int = (int)sub_size;
			fprintf(file, "<td>%d%s</td>", size_int, "K");
		}
		else //exist decimal point
			fprintf(file, "<td>%.1lf%s</td>", sub_size, "K");
	}

	else if (k == 2) //megabytes unit
	{
		if (flag == 1) //flag of intger
		{
			size_int = (int)sub_size;
			fprintf(file, "<td>%d%s</td>", size_int, "M");
		}
		else //exist decimal point
			fprintf(file, "<td>%.1lf%s</td>", sub_size, "M");
	}

	else if (k == 3) //gigabytes unit
	{
		if (flag == 1) //flag of intger
		{
			size_int = (int)sub_size;
			fprintf(file, "<td>%d%s</td>", size_int, "G");
		}
		else //exist decimal point
			fprintf(file, "<td>%.1lf%s</td>", sub_size, "G");
	}

	else if (k == 4) //terabytes unit
	{
		if (flag == 1) //flag of intger
		{
			size_int = (int)sub_size;
			fprintf(file, "<td>%d%s</td>", size_int, "T");
		}
		else //exist decimal point
			fprintf(file, "<td>%.1lf%s</td>", sub_size, "T");
	}
	return;
}

void sortingfile(char(*paname)[256], int argc)
{
	//Nofilecount = 0, Filecount = 0, Optioncount = 0;
	struct stat buf;
	struct stat buf2;
	char subarray[256][256] = { 0 };
	char tmp[256] = { 0 };
	int count = 0;


	for (int i = (Optioncount + Nofilecount + 1), j = 0; i<(Optioncount + Nofilecount + Filecount + 1); i++, j++, count++) //for move content to subarray
		strcpy(subarray[j], paname[i]); //copy

	for (int loop = 0; loop < count - 1; loop++)
	{
		for (int i = 0; i < count - 1 - loop; i++)
		{
			lstat(subarray[i], &buf);
			lstat(subarray[i + 1], &buf2);
			if (flagr == 1 && buf.st_size>buf2.st_size) //If flagr is on
			{//practice swap
				strcpy(tmp, subarray[i + 1]); //copy
				strcpy(subarray[i + 1], subarray[i]); //copy
				strcpy(subarray[i], tmp); //copy
			}

			else if (flagr == 0 && buf.st_size<buf2.st_size) //If Subargv[j] is bigger than Subargv[j+1] 
			{//practice swap
				strcpy(tmp, subarray[i + 1]); //copy
				strcpy(subarray[i + 1], subarray[i]); //copy
				strcpy(subarray[i], tmp); //copy
			}
		}
	}

	for (int i = (Optioncount + Nofilecount + 1), j = 0; i<(Optioncount + Nofilecount + Filecount + 1); i++, j++) //for move content to paname
		strcpy(paname[i], subarray[j]); //copy


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
			lstat(name, &buf); //read file
			lstat(tmp->filename, &buf2); //read file
										 //////////For checking symbol in string//////////
			strcpy(Ename, name);
			strcpy(Etmpname, tmp->filename);

			if (checkstring(Ename)) //check string
				Eliminate(Ename, '.'); //delete
			if (checkstring(Etmpname))
				Eliminate(Etmpname, '.');
			/////////////////////////////////////////////////
			if ((buf.st_size - buf2.st_size)>0)
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

			else if ((buf.st_size - buf2.st_size) == 0 && strcasecmp(Etmpname, Ename)>0) //compare string
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
int matchfunction(char(*paname)[256], int argc)
{
	char Matchcmd[256][256] = { 0 };
	int matchcount = 0;

	///////////////////////////////////////////////////////searching match command////////////////////////////////////////////////////////
	for (int i = 1; i<argc; i++) //for check all command
	{
		for (int j = 0; j<sizeof(paname[i]); j++)
		{
			if (paname[i][j] == '?' || paname[i][j] == '*') //if the command has '*' or '?'
			{
				strcpy(Matchcmd[matchcount], paname[i]); //copy
				matchcount++; //increase
				break;
			}
			else if (paname[i][j] == '[' && ((paname[i][j + 1]>47 && paname[i][j + 1]<58) || (paname[i][j + 1]>64 && paname[i][j + 1]<90) || (paname[i][j + 1]>96 && paname[i][j + 1]<123))
				&& paname[i][j + 2] == '-' && ((paname[i][j + 3]>47 && paname[i][j + 3]<58) || (paname[i][j + 3]>64 && paname[i][j + 3]<90) || (paname[i][j + 3]>96 && paname[i][j + 3]<123)) && paname[i][j + 4] == ']') //if the command has 'index'
			{
				strcpy(Matchcmd[matchcount], paname[i]); //copy
				matchcount++; //increase
				break;
			}
			else if (paname[i][j] == '[' && ((paname[i][j + 1]>47 && paname[i][j + 1]<58) || (paname[i][j + 1]>64 && paname[i][j + 1]<90) || (paname[i][j + 1]>96 && paname[i][j + 1]<123))
				&& paname[i][j + 2] == ']')  //if the command has 'index'
			{
				strcpy(Matchcmd[matchcount], paname[i]); //copy
				matchcount++; //increase
				break;
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////delete match cmd////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i<matchcount; i++) //check all cmd
	{
		for (int j = 1; j<argc; j++)
		{
			if (!strcmp(paname[j], Matchcmd[i])) //if the command is matching
			{
				for (int k = j; k<argc; k++)
					strcpy(paname[k], paname[k + 1]); //delete

				argc--; //decrease count
				break;
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int newargc = argc; //integer
	int flag = 0; //integer
	struct dirent *dir;
	struct stat buf;
	DIR *dirp;
	char pathname[256][256] = { 0 };
	char cmd[256][256] = { 0 };

	for (int i = 0; i<matchcount; i++) //for check match command
	{
		int j = 0;
		for (; Matchcmd[i][j] != '\0'; j++); //move pointer to end
		for (; Matchcmd[i][j] != '/'&&j != 0; j--); //search charcater of '/'

		for (int a = 0; a<j; a++)
		{
			pathname[i][a] = Matchcmd[i][a]; //copy path of command
			pathname[i][a + 1] = '\0'; //save null
		}

		for (int a = 0, b = j; Matchcmd[i][a] != '\0'; a++, b++)
		{
			cmd[i][a] = Matchcmd[i][b]; //copy of match command
			cmd[i][a + 1] = '\0'; //save null
		}

	}


	for (int j = 0; j<matchcount; j++) //for check command
	{
		int currentflag = 0; //declare flag

		if (cmd[j][0] == '/') //delete '/'
			for (int i = 0; cmd[j][i] != '\0'; i++)
				cmd[j][i] = cmd[j][i + 1];

		if (strlen(pathname[j]) == 0) //check path name
			dirp = opendir(".");
		else
		{
			currentflag = 1; //on flag
			dirp = opendir(pathname[j]); //open pathname directory
		}
		chdir((char *)getenv("PWD")); //change directory


		if (dirp == NULL) //Check null
		{
			strcpy(paname[newargc], Matchcmd[j]); //command return parameter
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
				if (!fnmatch(cmd[j], dir->d_name, 0) && (dir->d_name[0] != '.')) //function of match
				{
					char realpath[256] = { 0 }; //for real path

					strcat(realpath, pathname[j]); //for full format of path
					if (currentflag == 1)
						strcat(realpath, "/");
					strcat(realpath, dir->d_name);

					strcpy(paname[newargc], realpath); //copy string
					newargc++;
					flag = 1; //on flag
				}
			}

		} while (1);

		if (flag == 0) //if flag is 0
		{
			strcpy(paname[newargc], Matchcmd[j]); //copy command
			newargc++;
		}
		flag = 0; //off flag
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
	if (str[0] != '.')
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
	for (int i = 0; str[i] != '\0'; i++) //cehck string
	{
		if (str[i] == '/') //if match '/'
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


//////////////////////////////////////////////////////////////////////
// duplication function                                             //
// ================================================================ //
// Input: char* -> The name pointer                                 //
//                                                                  //
// Output: int -> For practice continue or not                      //
//                                                                  //
// Purpose: duplication checking                                    //
//////////////////////////////////////////////////////////////////////
int duplication_ico(char* name) //for checking favicon.ico
{
   char html[256]={"favicon.ico"}; // html file
   for(int count=0; count<strlen(name); count++) // loop for checking duplication
   {
      if(name[count]==html[0]) //check character of first
      {
         int a=count;
         int b=0;
         int cnt=0;
        for(;1;) // repeat before break
         {
            if(name[a]==html[b]) // duplication check condition
            {
               cnt++;
               a++;
               b++;
            }
            else 
		break; //break
         
            if(cnt==strlen(html)) // duplication
		return -1; // return -1
         }
      }
   }
   return 1; //return 1
}
