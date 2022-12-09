#include "ArvAVL.hpp"

#include<iostream>

node * ArvAVL::pesquisaDic(Verbete it){
    node * p = pesquisaRecursivo(root, it);
   return p;
}

int ArvAVL::insereDic(Verbete * it){
    insereRecursivo(this->root, *it);
}

void ArvAVL::imprimeDic(){
    this->emOrdem(this->root);
}

int ArvAVL::atualizaDic(Verbete * it){

}

int ArvAVL::removeDic(Verbete * it){
    
}

void ArvAVL::insereRecursivo(node* &p, Verbete it){
    if(p == nullptr){
        p = new node();
        p->item = it;
        std::cout << "OK: CONTA "<< p->item.palavra << " CADASTRADA" << std::endl;
    }
    else{
        if(it.palavra < p->item.palavra)
            insereRecursivo(p->folhaEsquerda, it);
        else if(it.palavra > p->item.palavra)
            insereRecursivo(p->folhaDireita, it);
        else {
            std::string sig = it.significado->desenfileira().significado;
            if(!sig.empty()) p->item.significado->enfilera(sig);
        }
    }
}

node *  ArvAVL::pesquisaRecursivo(node* &p, Verbete it){
    if(p == nullptr){
        throw it;
    }
    if(p->item.palavra == it.palavra){
        return p;
    } 
    else{
        if(it.palavra < p->item.palavra)
           return pesquisaRecursivo(p->folhaEsquerda, it);
        else
           return pesquisaRecursivo(p->folhaDireita, it);
    }
}

void ArvAVL::removeRecursivo(node* &p, Verbete it){

}

void ArvAVL::antecessor(node* q, node* &r){
    
}


void ArvAVL::emOrdem(node *p){
    if(p != nullptr){
        emOrdem(p->folhaEsquerda);
        p->item.Imprime();
        emOrdem(p->folhaDireita);
    }
}

int ArvAVL::fatorBalanceamento(node *p){
    if (p == nullptr) return 0;

    int balanco = p->folhaDireita->altura - p->folhaEsquerda->altura;
    
    return balanco;
}

node * ArvAVL::rotacaoEsquerda(node *x){
    node *y, *t;

    //guardando ponteiros
    y = x->folhaDireita; 
    t = y->folhaEsquerda; 

    //rotacao
    y->folhaEsquerda = x; //a raiz x vira folha esquerda de y
    x->folhaDireita = t; // a folha esquerda de y vira folha direita de x

    //corrigindo pais
    y->pai = x->pai;
    x->pai = y;
    t->pai = x;

    // recalcula a altura dos nós que foram movimentados
    x->altura = max(x->folhaEsquerda->altura, x->folhaDireita->altura) + 1;
    y->altura = max(y->folhaEsquerda->altura, y->folhaDireita->altura) + 1;

    return y;
}

node * ArvAVL::rotacaoDireita(node *x){
    node *y, *t;

    //guardando ponteiros
    y = x->folhaEsquerda; 
    t = y->folhaDireita; 

    //rotacao 
    y->folhaDireita = x; //a raiz x vira folha de y
    x->folhaEsquerda = t; // t vira a folha direita de x

    //corrigindo pais
    y->pai = x->pai;
    x->pai = y;
    t->pai = x;

    // recalcula a altura dos nós que foram movimentados
    x->altura = max(x->folhaEsquerda->altura, x->folhaDireita->altura) + 1;
    y->altura = max(y->folhaEsquerda->altura, y->folhaDireita->altura) + 1;

    return y;
}

int ArvAVL::max(int v1, int v2) {
    if (v1 > v2) return v1;
    else return v2;
}
