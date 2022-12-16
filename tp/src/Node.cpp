#include "Node.hpp"
#include <iostream>
#include <fstream>

extern "C"{
    #include <msgassert.h>
    #include <memlog.h>
    #include <sys/time.h>
    #include <sys/resource.h>
}

Verbete::Verbete(){
    significado = new std::string[10];
}

node::node(){
    this->folhaEsquerda = nullptr;
    this->folhaDireita = nullptr;
    altura = 1;
    item = new Verbete;
}

int node::insereVerbete(Verbete * verbete){
    if(verbete->vazio() && !item->vazio()) return -1; //nao insere se já existir e nao tiver significado
    escreveMemLog((long int)(verbete), sizeof(long int), 1);

    if(item->vazio()){
        this->item->palavra = verbete->palavra;
        this->item->significado = verbete->significado;
        this->item->tipoPalavra = verbete->tipoPalavra;

        if(verbete->significado[0] != "" ||verbete->significado[0] != "\r" )
            this->item->tam++;
        return 1; //insere
    } 
    else if(!item->cheio()){
        this->item->significado[item->tam] = verbete->significado[0];
        this->item->tam++;
    } 
    else 
        throw "Item cheio!";

    return 0;
    //nao insere porque o vetor está cheio
}

void node::imprimirNo(std::ofstream& outFile){
    
    outFile << item->palavra<< " ("<< item->tipoPalavra <<")" << std::endl;
    
    for (int i = 0; i < item->tam; i++){
        outFile << i+1 << "." << item->significado[i] << std::endl;
    }
}
    