#include "Node.hpp"
#include <iostream>
#include <fstream>

node::node(){
    this->folhaEsquerda = nullptr;
    this->folhaDireita = nullptr;
    altura = 1;
}

int node::alturaNo(){ 
    if(this == nullptr) return 0;
    return this->altura;
}

int node::insereVerbete(Verbete * verbete){
    if(verbete->vazio() && !item.vazio()) return -1; //nao insere se já existir e nao tiver significado
    
    if(item.vazio()){
        this->item = *verbete;
        if(verbete->significado[0] != "")
            this->item.tam++;
        return 1; //insere
    } else if(!item.cheio()){
        this->item.significado[item.tam] = *verbete->significado;
        this->item.tam++;
    } else 
        throw "Item cheio!";

    return 0;
    //nao insere porque o vetor está cheio
}

void node::imprimirNo(std::ofstream& outFile){
    
    outFile << item.palavra<< " ("<< item.tipoPalavra <<")" << std::endl;
    
    for (int i = 0; i < item.tam; i++){
        outFile << i+1 << "." << item.significado[i] << std::endl;
    }
}
    