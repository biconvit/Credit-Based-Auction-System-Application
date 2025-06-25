#include <iostream>
#include "Data.h"

void tryOpenFile(string fileName) {
        fstream data;

        //Try to open file
        data.open(fileName, std::ios::in);
        
        //If the file cannot be open, create a new one
        if(!data) data.open(fileName, std::ios::out);

        //Check again
        if(!data) {
                cerr << "Failed to open file!\n";
                return;
        }

        data.close();
}
