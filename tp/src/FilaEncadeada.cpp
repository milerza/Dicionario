#include "FilaEncadeada.hpp"

#include <iostream>
#include <fstream>

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

void FilaEncadeada::enfilera(std::string palavra, std::string significado, char tipoPalavra){
    TipoCelula *nova;

    nova = new TipoCelula();
    nova->item.palavra = palavra;
    nova->item.significado = significado;
    nova->item.tipoPalavra = tipoPalavra;
    tras->prox = nova;
    tras = nova;
    tamanho++;

    nova->item.ID = tamanho;
}

void FilaEncadeada::imprimir(std::string output) {
    std::ofstream outFile;
    TipoCelula *p;

    outFile.open(output.c_str());
    
    int i = 0;
    p = frente->prox;

    while (p!=nullptr) {
        if(p->item.ID == 1){
            outFile <<  p->item.palavra << "("<< p->item.tipoPalavra<<")" << std::endl;
        }
        outFile<< p->item.ID << ". " << p->item.significado<< std::endl;
        p = p->prox;
        i++;
    }

    outFile.close();
}

