#include "Verbete.hpp"

#include <iostream>
#include <fstream>>

void Verbete::imprime(std::string output){
    std::ofstream outFile;
    TipoCelula *p;

    outFile.open(output.c_str());
    outFile << this->palavra<< "("<< this->tipoPalavra <<")" << std::endl;
    

    outFile.close();
}