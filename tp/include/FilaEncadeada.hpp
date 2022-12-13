#ifndef _FILA_ENCADEADA_
#define _FILA_ENCADEADA_

#include <string>

#include "Verbete.hpp"

class TipoItem{
    public:
        int ID;
        Verbete verbete;
};

class TipoCelula{
    public:
        TipoCelula();
        TipoCelula *prox;
        TipoItem item;  

    friend class FilaEncadeada;
};

class FilaEncadeada{
    public:
        FilaEncadeada();
        ~FilaEncadeada();
        int getTamanho() {return tamanho;};
        bool vazia() {return tamanho == 0;};
        TipoItem desenfileira();
        void limpa();
        void enfilera(TipoItem item);
        void imprimir(std::string output);
        
    protected:
        int tamanho;

    private:
        TipoCelula* frente;
        TipoCelula* tras;
};
#endif