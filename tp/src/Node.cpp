#include "Node.hpp"

node::node(){
    this->folhaEsquerda = nullptr;
    this->folhaDireita = nullptr;
}

node::~node(){
    delete this->folhaEsquerda;
    delete this->folhaDireita;
}

int node::alturaNo(){
    if(this == nullptr) return -1;
    else return this->altura;
}