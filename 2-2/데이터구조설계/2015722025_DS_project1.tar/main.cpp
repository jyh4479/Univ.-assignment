#include "Manager.h"
#include <iostream>
#include <fstream>

#ifndef _DEBUG // declaration to check memory leak
#define new new(_CLIENT_BLOCK,__FILE__,__LINE) // declaration to check memory leak
#endif // declaration to check memory leak

using namespace std;

static ofstream flog;

int main() 
{
	Manager manager; //Declare manager
	manager.run("command.txt", flog); //send the name of txt file
	//_CrtDumpMemoryLeaks(); //check memory leak
	return 0;
}
