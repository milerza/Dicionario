#ifndef _FILA_ENCADEADA_
#define _FILA_ENCADEADA_

#include <string>
#include <fstream>

class TipoItem{
    public:
        int ID;
        int tam = 0;
        int static const max = 10;
        std::string significado[10];
        std::string palavra;
        char tipoPalavra;
        bool vazio(){return tam == 0;}
        bool cheio(){return tam == max;}
        void imprimir(std::ofstream& outFile);
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
        void preencheLista(TipoItem *listaItens, int * l);
        void limpa();
        void enfilera(TipoItem item);
        void imprimir(std::ofstream& outFile);
        void AtualizaPosicao(TipoItem item, int pos);
        int PesquisaPosicao(std::string c);
        void pecorreERemove();
        TipoItem RemovePosicao(int pos);
        
    protected:
        int tamanho = 0;

    private:
        TipoCelula* Posiciona(int pos, bool antes=false);
        TipoCelula* frente;
        TipoCelula* tras;
};
#endif