#ifndef _ARV_AVL_
#define _ARV_AVL_

#include "Verbete.hpp"

class node {
    public:
        Verbete item;
        int altura;
        node *folhaEsquerda;
        node *folhaDireita;
        node *pai;
};


class ArvAVL{
    public:
        node *root;

        ArvAVL();
        ~ArvAVL();

        int pesquisaDic(Verbete it);
        int insereDic(Verbete * it);
        void imprimeDic();
        int atualizaDic(Verbete * it);
        int removeDic(Verbete * it);
        
    
    private:
        void insereRecursivo(node* &p, Verbete it);
        node * pesquisaRecursivo(node* &p, Verbete it);
        void removeRecursivo(node* &p, Verbete it);
        void antecessor(node* q, node* &r);
        void emOrdem(node* p);
        int fatorBalanceamento(node *p);
        node * rotacaoEsquerda(node *x);
        node * rotacaoDireita(node *x);
        int max(int v1, int v2);

        
};


#endif