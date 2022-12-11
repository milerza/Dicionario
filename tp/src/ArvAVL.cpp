#include "ArvAVL.hpp"

int ArvAVL::pesquisaDic(Verbete it){
    node * p = pesquisaRecursivo(root, it);
    while (p->item->palavra == it.palavra)
    {
        p = pesquisaRecursivo(root, it);
    }
    
    
    
}

int ArvAVL::insereDic(Verbete * it){

}

void ArvAVL::imprimeDic(){
    this->emOrdem(this->root);
}

int ArvAVL::atualizaDic(Verbete* it){

}

int ArvAVL::removeDic(Verbete* it){

}



void ArvAVL::insereRecursivo(node* &p, Verbete* it){
    if(p == nullptr){
        p = new node();
        p->item = it;
    }
    else{
        if(it->palavra < p->item->palavra)
            insereRecursivo(p->folhaEsquerda, it);
        else if(it->palavra > p->item->palavra){
            insereRecursivo(p->folhaDireita, it);
        } else{
            //p->item->significado;
        }
    }
}

node *  ArvAVL::pesquisaRecursivo(node* &p, Verbete  it){
    if(p == nullptr){
        throw it;
    }
    if(p->item->palavra == it.palavra){
        return p;
    } 
    else{
        if(it.palavra < p->item->palavra)
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
        p->item->imprime();
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
    y->folhaEsquerda = x;
    x->folhaDireita = t;

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
    y->folhaDireita = x;
    x->folhaEsquerda = t; 

    //corrigindo pais
    y->pai = x->pai;
    x->pai = y;
    t->pai = x;

    // recalcula a altura dos nós que foram movimentados
    x->altura = max(x->folhaEsquerda->altura, x->folhaDireita->altura) + 1;
    y->altura = max(y->folhaEsquerda->altura, y->folhaDireita->altura) + 1;

    return y;
}

node* ArvAVL::rotacaoEsquerdaDireita(node* x){ 
    x->folhaEsquerda = this->rotacaoEsquerda(x->folhaEsquerda);
    return this->rotacaoDireita(x);
}

node* ArvAVL::rotacaoDireitaEsquerda(node* x){
    x->folhaDireita = this->rotacaoDireita(x->folhaEsquerda);
    return rotacaoEsquerda(x);
}

int ArvAVL::max(int v1, int v2) {
    if (v1 > v2) return v1;
    else return v2;
}
