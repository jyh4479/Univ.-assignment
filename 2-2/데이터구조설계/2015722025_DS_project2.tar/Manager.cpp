#include "Manager.h"

Manager::Manager(int bpOrder){ //The Manager Constructor
	fout.open("log.txt", ios::app); //For log file
	avl = new AVLTree(&fout); //Declare AVLtree
	bp = new BpTree(&fout, bpOrder); //Declare B+ tree	
}

Manager::~Manager(){ //The destructor
	delete avl; //delete avl
	delete bp; //delete B+s
	fout.close(); //close log file
}

void Manager::run(const char* command_txt){ //The function of run
	ifstream fin;		fin.open(command_txt); //For loading command
	int	load = -1; //save -1 to load
		
	if(!fin){ //if fin is not opened
		cout<<"[ERROR] command file open error!"<<endl; //print
		return;
	}

	char*	str = NULL; //Declare for command string
	char*	str2 = NULL;     
	char*   str3 = NULL;		
	char*   str4 = NULL;     
	char	buf[128] = { 0 };
	char	buf2[128] = { 0 };

	while(fin.getline(buf, 64)){ //repeat the function until fin is ended
		strcpy(buf2, buf); //copy string
		str=strtok(buf, " \n"); //token
		
		if(strcmp(str, "LOAD") == 0) //if The command is Load
		{
			if(load == 1) //if load is 1
			{
				printErrorCode(100); //Error
				fout << endl;
				continue;
			}
			else if((str=strtok(NULL, " \n")) != NULL || !LOAD()) //practice the LOAD
			{
				printErrorCode(100); //Error
				fout << endl;
				continue;
			}
			printSuccess("LOAD");
			load = 1;
		}
		else if(strcmp(str, "SEARCH_AVL") == 0){ //if Command is SEARCH_AVL
			str2 = strtok(NULL," ");
			str3 = strtok(NULL," ");

			if (str2 == NULL || str3 != NULL) //check paramter
			{
				printErrorCode(300); //Error
				fout << endl;
				continue;
			}

			if (!SEARCH_AVL(str2)) //pracitce SEARCH_AVL
				printErrorCode(300);

		}
		else if(strcmp(str, "SEARCH_BP") == 0){ //If command is SEARCH_BP
			str2 = strtok(NULL, " ");
			str3 = strtok(NULL, " ");
			str4 = strtok(NULL, " ");
			
			if (str2 == NULL || str3 == NULL || str4 != NULL) //for checking parameter
			{
				printErrorCode(200); //Error
				fout << endl;
				continue;
			}
			
			double a = 0, b = 0; //Declare double

			a = atof(str2); //change type
			b = atof(str3);

			if (!SEARCH_BP(a, b)) //practice function of searching
				printErrorCode(200);
		}
		else if(strcmp(str, "RANK") == 0){ //If command is RANK
			str2 = strtok(NULL, " ");

			if (str2 != NULL) //checking paramter
			{
				printErrorCode(400);
				fout << endl;
				continue;
			}

			if (!RANK()) //pracitce RANK
				printErrorCode(400);
		}
		else if(strcmp(str, "PRINT_AVL") == 0){ //if command is PRINT_AVL
			str2 = strtok(NULL, " ");

			if (str2 != NULL) //check parameter
			{
				printErrorCode(600);
				fout << endl;
				continue;
			}

			if (!PRINT_AVL()) //practice Print function
				printErrorCode(600);
		}
		else if(strcmp(str, "PRINT_BP") == 0){ //if command is PRINT_BP
			str2 = strtok(NULL, " ");

			if (str2 != NULL) //checking parameter
			{
				printErrorCode(500);
				fout << endl;
				continue;
			}

			if (!PRINT_BP()) //practice print function
				printErrorCode(500);
		}
		else if (strcmp(str, "EXIT") == 0) { //if command is EXIT
			EXIT(); //practice EXIT
			printSuccess("EXIT");
			return; //return
		}
		fout<<endl;
	}	
	fin.close();
}

bool Manager::LOAD(){ //The Load function
	
	char*	str=NULL;
	char	buf[128]={0};
	char	buf2[128]={0};

	ifstream fin; //ifstream
	fin.open("stock_list.txt"); //load data of information
	
	if(!fin){ //if file is not opened
		return false; //return false
	}
		
	while(fin.getline(buf, 64)){ //repeat the function, if the information is not end
		StockData* pSto;
		strcpy(buf2, buf);

		str = strtok(buf, " "); //for divide information
		str = strtok(NULL, " ");
		str = strtok(NULL, " ");
		pSto = new StockData(); //create space of data

		str = strtok(buf2, " ");
		pSto->setStockID(atoi(str));
		str = strtok(NULL, " ");
		pSto->setName(str);
		int open = atoi(strtok(NULL, " "));
		pSto->setOpening_Price(open);
		int close = atoi(strtok(NULL, " "));
		pSto->setClosing_Price(close);
		int volume = atoi(strtok(NULL, " "));
		pSto->setVolume(volume);

		pSto->setEarning(open, close); //set Earning

		avl->Insert(pSto); //Insert data
		bp->Insert(pSto); //Insert data
	}
	return true; //return true
}

bool Manager::SEARCH_AVL(char* name){ //SEARCH AVL function
	if(!avl->Search(name))	return false;
	else							return true;
}

bool Manager::SEARCH_BP(double a, double b){ //SEARCH BP function
	if(!bp->Search(a, b))			return false;
	else							return true;
}

bool Manager::RANK(){ //RANK function
	if(!avl->Rank())		return false;
	else					return true;
}

bool Manager::PRINT_AVL(){ //PRINT AVL function
	if(!avl->Print())	return false;
	else					return true;
}

bool Manager::PRINT_BP(){ //PRINT BP function
	if(!bp->Print())		return false;
	else					return true;
}

bool Manager::EXIT() { //EXIT function
	avl->Exit();
	return true;
}

void Manager::printErrorCode(int n){ //print Error
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout<<"======================="<<endl;
}

void Manager::printSuccess(char *n) { //print success
	fout << "======== "<<n<<" ========" << endl;
	fout << "Success" << endl;
	fout << "=======================" << endl;
}

