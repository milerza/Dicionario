#ifndef _FILA_ENCADEADA_
#define _FILA_ENCADEADA_

#include <string>

class TipoItem{
    public:
        int ID;
        std::string significado;
        std::string palavra;
        char tipoPalavra;
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
        void imprimir(std::ofstream& outFile);
        
    protected:
        int tamanho;

    private:
        TipoCelula* frente;
        TipoCelula* tras;
};
#endif