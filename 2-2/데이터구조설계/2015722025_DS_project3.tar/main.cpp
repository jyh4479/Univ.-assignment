#include "Manager.h"

int main(int argc, char* argv[]) //main
{
    const char* commandFilepath = "command.txt"; //declare name of command txt
    if (argc > 1)
        commandFilepath = argv[1];

    Manager m; //Declare manager
    m.Run(commandFilepath); //run

    return 0;
}