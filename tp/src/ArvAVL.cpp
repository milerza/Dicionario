#include "ArvAVL.hpp"

int ArvAVL::pesquisaDic(Verbete it){
    node * p = pesquisaRecursivo(root, it);
    while (p->item.palavra == it.palavra)
    {
        p = pesquisaRecursivo(root, it);
    }
    
    
    
}

int ArvAVL::insereDic(Verbete * it){
}

void ArvAVL::imprimeDic(){
    this->emOrdem(this->root);
}

int ArvAVL::atualizaDic(Verbete * it){

}

int ArvAVL::removeDic(Verbete * it){

}

void ArvAVL::insereRecursivo(node* &p, Verbete it){

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