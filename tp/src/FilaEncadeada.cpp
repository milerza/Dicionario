#include "FilaEncadeada.hpp"

#include <iostream>
#include <fstream>

TipoCelula::TipoCelula(){
    prox = nullptr;
}

FilaEncadeada::FilaEncadeada(){
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

void FilaEncadeada::enfilera(TipoItem item){
    TipoCelula *nova;
    nova = new TipoCelula();

    nova->item = item;
    tras->prox = nova;
    tras = nova;

    tamanho++;

    nova->item.ID = tamanho;
}

void FilaEncadeada::imprimir(std::ofstream& outFile) {
    TipoCelula *p;
    
    int i = 0;
    p = frente->prox;

    outFile << p->item.palavra << "("<< p->item.tipoPalavra<<")" << std::endl;
        
    while (p!=nullptr) {
        outFile<< p->item.ID << ". " << p->item.significado<< std::endl;
        p = p->prox;
        i++;
    }

}

