#include <iostream>
#include <dirent.h>
#include "../inc/GameWorld.hpp"
#include <stdlib.h>

using namespace std;

int main(int argc, char * argv[])
{

    string xml_file = "sample.txt.xml";

    if(argc > 1)
    {
        xml_file = string(argv[1]);
    }
    // cout << xml_file << endl;


    FILE * fptr = fopen(xml_file.c_str(), "r");
    if(fptr == nullptr)
    {
        fclose(fptr);
        cout << "XML file is not found" << endl;   
        return EXIT_FAILURE;
    }

    fclose(fptr);


    GameWorld gw;
    if (gw.InitGame(xml_file))
    {
        gw.GameLoop();
    }

    return EXIT_SUCCESS;
}
