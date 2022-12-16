#include "FilaEncadeada.hpp"

#include <iostream>

extern "C"{
    #include <msgassert.h>
    #include <memlog.h>
    #include <sys/time.h>
    #include <sys/resource.h>
}

void TipoItem::imprimir(std::ofstream& outFile){

    outFile << this->palavra << " ("<< this->tipoPalavra<<")" << std::endl;
            
    for(int i = 0; i< this->tam; i++ ) {
        outFile<< i+1 << ". " << this->significado[0]<< std::endl;
    }
}

TipoCelula::TipoCelula(){
    prox = nullptr;
}


FilaEncadeada::FilaEncadeada(){
    frente = new TipoCelula();
    tras = frente;
}

FilaEncadeada::~FilaEncadeada(){
    limpa();
    delete frente;
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

void FilaEncadeada::pecorreERemove(){
    int x = tamanho;
    for(int i = 1; i<=tamanho; i++){
        RemovePosicao(i);
        if(x>tamanho){
            i--; x--;
        }
    }
}

// Remove a célula de acordo a posição
TipoItem FilaEncadeada::RemovePosicao(int pos) {
    TipoItem aux;
    TipoCelula *p, *q;

    if (tamanho == 0)
        throw "ERRO: Lista vazia!";

    // posiciona p na celula anterior à pos
    p = Posiciona(pos, true);
    q = p->prox;
    leMemLog((long int)(q), sizeof(long int), 3);

    if (!q->item.vazio()){
        escreveMemLog((long int)(p->prox), sizeof(long int), 3);
        p->prox = q->prox;
        tamanho--;
        aux = q->item;
        delete q;

        if(p->prox == nullptr)
            tras = p;
    }

    return aux;
}

void FilaEncadeada::preencheLista(TipoItem *listaItens, int * l){
    TipoCelula *p;
    
    p = frente->prox;
    
    leMemLog((long int)(p), sizeof(long int), 2);
    while (p!=nullptr) {
        listaItens[*l] = p->item;
        (*l)++;
        p = p->prox;
    }
}

void FilaEncadeada::enfilera(TipoItem item){
    TipoCelula *nova;
    nova = new TipoCelula();

    escreveMemLog((long int)(nova), sizeof(long int), 1);

    nova->item = item;
    tras->prox = nova;
    tras = nova;

    tamanho++;
    
    if(nova->item.significado[0] != "")
        nova->item.tam++;

    nova->item.ID = tamanho;
}

//Imprime a fila
void FilaEncadeada::imprimir(std::ofstream& outFile) {
    TipoCelula *p;   
    p = frente->prox;
    
    leMemLog((long int)(p), sizeof(long int), 2);

    while (p!=nullptr) {
        p->item.imprimir(outFile);
        p = p->prox;
    }
}

// Caso a palavra exista, adiciona o significado na posicao dela
void FilaEncadeada::AtualizaPosicao(TipoItem it, int pos){
    TipoCelula *p;
    
    p = Posiciona(pos, true);

    leMemLog((long int)(p), sizeof(long int), 1);

    if(p->item.tam < p->item.max){
        p->item.significado[p->item.tam] = it.palavra;
        p->item.tam++;
    }
}

// Retorna a posicao na fila, caso já exista
int FilaEncadeada::PesquisaPosicao(std::string c){
    TipoItem aux;
    TipoCelula *p;
    
    if (tamanho == 0)
       return -1;

    aux.ID = -1;

    p = frente->prox;

    leMemLog((long int)(p), sizeof(long int), 1);
    leMemLog((long int)(p), sizeof(long int), 3);
    
    escreveMemLog((long int)(p), sizeof(long int), 1);
    escreveMemLog((long int)(p), sizeof(long int), 3);
    while (p != nullptr) {
        if (p->item.palavra == c) {
            aux = p->item;
            break;
        }
        p = p->prox;
    }
    return aux.ID;
}

TipoCelula* FilaEncadeada::Posiciona(int pos, bool antes){
    TipoCelula *p; 
    int i;
  
    if ( (pos > tamanho) || (pos <= 0) )
        avisoAssert(pos <  tamanho || pos > 0 , "Posição inválida!");
    

    // Posiciona na célula anterior a desejada
    p = frente;

    leMemLog((long int)(p), sizeof(long int), 1);
    leMemLog((long int)(p), sizeof(long int), 3);

    for(i = 1; i < pos; i++){
        p = p->prox;
    }

    if(!antes)
        p = p->prox;

    return p;
}

