#include <iostream>
#include <dirent.h>
#include "../inc/GameWorld.hpp"
#include <stdlib.h>

using namespace std;

int main() {

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./")) != NULL)
    {
        /* print all the files and directories within directory */
        
        ent = readdir(dir);
        bool FLAG = false;
        while (ent)
        {
            cout <<  ent->d_name << endl;
            if(strcmp(ent -> d_name,"sample.txt.xml"))
            {
                FLAG = true;
                break;
            }
            
            ent = readdir(dir);
        }
        if(FLAG == false)
        {
            cout << "XML file not in the current directory" << endl;
            return EXIT_FAILURE;
        }
        else
        {
            cout << "XML file is found" << endl;
        }
    }
    


    GameWorld gw;
    if(gw.InitGame())
    {
        gw.GameLoop();
    }
    
}