//
// Created by thuan on 24/04/18.
//

#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <fstream>


using namespace std;

int main(int argumentNumber, char *argumentValues[]) {


    FILE *file = fopen("/test.txt" , "rb");
    if ( file == nullptr )
    {
        cout << "Unable to open the file for reading";
    }
    else {
        string fileContent ="";
        while ( !feof(file))
        {
            string line;
            char c = fgetc(file);
            if (c < 0)
            {
                break;
            }
            if (c == '\n' || c == '\r') {

                fileContent+='\r';
                fileContent+= '\n';
                continue;
            }
            fileContent += c;
        }
        fclose(file);
        cout << fileContent ;
    }




}


