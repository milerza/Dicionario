#ifndef _FILA_ENCADEADA_
#define _FILA_ENCADEADA_


#include <string>

class TipoItem{
    public:
        int ID;
        std::string significado;
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
        void enfilera(std::string it);
        void imprimir();
        
    protected:
        int tamanho;

    private:
        TipoCelula* Posiciona(int prioridade);
        TipoCelula* frente;
        TipoCelula* tras;
};
#endif