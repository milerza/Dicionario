#include "FilaEncadeada.hpp"

#include <iostream>

void TipoItem::imprimir(std::ofstream& outFile){

    outFile << this->palavra << "("<< this->tipoPalavra<<")" << std::endl;
            
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

    if (!q->item.vazio()){
        p->prox = q->prox;
        tamanho--;
        aux = q->item;
        delete q;

        if(p->prox == nullptr)
            tras = p;
    }

    return aux;
}

void FilaEncadeada::enfilera(TipoItem item){
    TipoCelula *nova;
    nova = new TipoCelula();

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
        
    while (p!=nullptr) {
        p->item.imprimir(outFile);
        p = p->prox;
    }
}

// Caso a palavra exista, adiciona o significado na posicao dela
void FilaEncadeada::AtualizaPosicao(TipoItem it, int pos){
    TipoCelula *p;

    p = Posiciona(pos, true);

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
        throw "ERRO: Posicao Invalida!";

    // Posiciona na célula anterior a desejada
    p = frente;

    for(i = 1; i < pos; i++){
        p = p->prox;
    }

    if(!antes)
        p = p->prox;

    return p;
}

