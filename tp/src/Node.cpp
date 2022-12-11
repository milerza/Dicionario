#include "Node.hpp"

node::node(){
    this->folhaEsquerda = nullptr;
    this->folhaDireita = nullptr;
    this->pai = nullptr;
}

node::~node(){
    delete this->folhaEsquerda;
    delete this->folhaDireita;
    delete this->pai;
}

int node::alturaNo(){
    if(this == NULL)
        return -1;
    else
        return this->altura;
}