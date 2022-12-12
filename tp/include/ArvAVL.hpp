#ifndef _ARV_AVL_
#define _ARV_AVL_

#include "Node.hpp"

class ArvAVL{
    public:
        node *root;

        ArvAVL();
        ~ArvAVL();

        node * pesquisa(Verbete it);
        int insere(Verbete it);
        void imprime();
        int atualiza(Verbete it);
        int remove(Verbete it);        
    
    private:
        static const int minFB = -1,
            maxFB = 1;

        void insereRecursivo(node* &p, Verbete * it);
        node *balancearArvore(node *p);
        node * pesquisaRecursivo(node* &p, Verbete it);
        node * removeRecursivo(node* &p, Verbete it);
        void emOrdem(node* p);
        int fatorBalanceamento(node* p);
        node * rotacaoEsquerda(node* x);
        node * rotacaoDireita(node* x);
        node * rotacaoEsquerdaDireita(node* x);
        node * rotacaoDireitaEsquerda(node* x);
        int max(int v1, int v2);

        
};


#endif