#ifndef _ARV_AVL_
#define _ARV_AVL_

#include "Node.hpp"
#include <fstream>

class ArvAVL{
    public:
        node *root;

        ArvAVL();
        ~ArvAVL();

        void insere(Verbete it);
        void imprime(std::ofstream& outFile);
        void removeSig();       
    
    private:
        static const int minFB = -1,
            maxFB = 1;

        node* insereRecursivo(node* &p, Verbete it);
        node *balancearArvore(node *p);
        node * removeRecursivo(node* &p, Verbete it);
        void pesquisa(node * p, int * i);
        void RemoveVetor(node * p);
        void procuraNaoVazio(node * p, Verbete* a, int * i);  
        void emOrdem(node* p,  std::ofstream& outFile);
        int fatorBalanceamento(node* p);
        node * rotacaoEsquerda(node* x);
        node * rotacaoDireita(node* x);
        node * rotacaoEsquerdaDireita(node* x);
        node * rotacaoDireitaEsquerda(node* x);
        int max(int v1, int v2);
        void apagaRecursivo(node *p);
        void limpa();
        
};


#endif