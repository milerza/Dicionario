#include "FilaEncadeada.hpp"

#include <iostream>

TipoCelula::TipoCelula(){
    prox = nullptr;
}

FilaEncadeada::FilaEncadeada(){
    tamanho = 0;
    frente = new TipoCelula();
    tras = frente;
}

FilaEncadeada::~FilaEncadeada(){
    limpa();
}

TipoItem FilaEncadeada::desenfileira(){
    TipoCelula *p;
    TipoItem aux;
    if (tamanho == 0)
        throw "Fila vazia";

    aux = frente->prox->item;    
    p = frente;
    frente = frente->prox;

    delete p;
    tamanho--;

    return aux;
}

void FilaEncadeada::limpa(){
    TipoCelula *p;
    p = frente->prox;

    while(p!=NULL){
        frente->prox = p->prox;
        delete p;
        p = frente->prox;
    }

    tamanho = 0;
    tras = frente;
}

void FilaEncadeada::enfilera(std::string it){
    TipoCelula *nova;

    nova = new TipoCelula();
    nova->item.significado = it;
    tras->prox = nova;
    tras = nova;
    tamanho++;

    nova->item.ID = tamanho;
}

void FilaEncadeada::imprimir() {
    TipoCelula *p;
    p = frente->prox;

    while (p!=nullptr) {
        std::cout << p->item.ID << ". " << p->item.significado<< std::endl;
        p = p->prox;
    }
}