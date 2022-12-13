#include "Verbete.hpp"

void Verbete::inserirSignificado(FilaEncadeada * p){
    std::string pal = p->desenfileira().palavra;
    std::string sig = p->desenfileira().significado;
    char pro = p->desenfileira().tipoPalavra;

    while (!p->vazia()){
        this->significado->enfilera(pal, sig, pro);
    }
}

void Verbete::imprime(std::string output){
    this->significado->imprimir(output);
}