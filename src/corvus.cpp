//
// Corvus Browser
// version 1.0
// Written by Erik Ramos(erikram312@gmail.com)
// 
//
#include <string>
#include <iostream>

import browser;


int main(int argc, char *argv[]){
    if(argc < 2){
        std::cerr << "Error: missing arg url." << "\n";
        std::cout << "\n";
        return -1;
    }
    MainBrowser masterBrowser(argv[1]);
    masterBrowser.run();
    return 0;
};