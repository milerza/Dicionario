#include "Verbete.hpp"

void Verbete::inserirSignificado(FilaEncadeada * p){
    while (!p->vazia()){
        this->significado->enfilera(p->desenfileira().significado);
    }
}

void Verbete::imprime(){
    this->significado->imprimir();
}