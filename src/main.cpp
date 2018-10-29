#include <iostream>
#include <dirent.h>
#include "../inc/GameWorld.hpp"
#include <stdlib.h>

using namespace std;

int main(int argc, char * argv[])
{

    char xml_file[] = "sample.txt.xml";

    if(argc > 1)
    {
        strcpy(xml_file, argv[1]);
    }
    cout << xml_file << endl;


    FILE * fptr = fopen(xml_file, "r");
    if(fptr == nullptr)
    {
        cout << "XML file is not found" << endl;   
        return EXIT_FAILURE;
    }

    fclose(fptr);


    GameWorld gw;
    if (gw.InitGame(xml_file))
    {
        gw.GameLoop();
    }
}
