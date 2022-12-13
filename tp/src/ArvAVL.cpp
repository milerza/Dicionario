#include "ArvAVL.hpp"

#include<iostream>

ArvAVL::ArvAVL(){
    root = nullptr;
}

ArvAVL::~ArvAVL(){
    limpa();
}

void ArvAVL::insere(Verbete it){
    insereRecursivo(this->root, &it);
}

void ArvAVL::imprime(std::ofstream& output){
    this->emOrdem(this->root, output);
}

void ArvAVL::removeNaoVazio(node * p){
   if(p == nullptr){
        return;
    }
    
    removeNaoVazio(p->folhaEsquerda);
    removeNaoVazio(p->folhaDireita);
    if(p!= nullptr)
    if(!p->item.vazio()){
        removeRecursivo(p, p->item);
    } 
}

void ArvAVL::removeSig(){
    removeNaoVazio(this->root);
    // balancea a arvore
     balancearArvore(this->root);
    std::cout << root->item.palavra <<std::endl;
    
}

void ArvAVL::insereRecursivo(node* &p, Verbete* it){
    if(p == nullptr){
        p = new node();
        p->item = *it;
        if(it->significado[0] != "")
            p->item.tam++;
    }
    else{
        if(it->palavra < p->item.palavra)
            insereRecursivo(p->folhaEsquerda, it);
        else if(it->palavra > p->item.palavra){
            insereRecursivo(p->folhaDireita, it);
        } else{
            p->insereVerbete(it);
        }
    }
    p->altura = this->max(p->folhaEsquerda->alturaNo(), p->folhaDireita->alturaNo()) + 1; //mexer aquiii

    p = this->balancearArvore(p);
}

node *ArvAVL::balancearArvore(node *p){
    short fb = fatorBalanceamento(p);

    // Rotação direita
    if(fb < minFB && fatorBalanceamento(p->folhaEsquerda) < 0)
        p = rotacaoDireita(p);

    // Rotação esquerda
    else if(fb > maxFB && fatorBalanceamento(p->folhaDireita) > 0)
        p = rotacaoEsquerda(p);

    // Rotação dupla: corrige quebra à direta 
    // com rotação à esquerda e rotaciona pra direita
    else if(fb > maxFB && fatorBalanceamento(p->folhaDireita) < 0)
        p = rotacaoEsquerdaDireita(p);

    // Rotação dupla: corrige quebra à esquerda 
    // com rotação à direita e rotaciona pra esquerda
    else if(fb < minFB && fatorBalanceamento(p->folhaEsquerda) > 0)
        p = rotacaoDireitaEsquerda(p);

    return p;
}

node * ArvAVL::removeRecursivo(node* &p, Verbete it){
    if(p == nullptr){
        std::cout <<"Valor nao encontrado!\n"<< it.palavra<<std::endl;
        return nullptr;
        
    } else { 
        // procura o nó a remover
        if(p->item.palavra == it.palavra) {
            // remove nós folhas (nós sem filhos)
            if(p->folhaEsquerda == nullptr && p->folhaDireita == nullptr) {
                delete p;
                
                std::cout <<"Elemento folha removido: "<< it.palavra<<std::endl;

                return p;
            }
            else{
                // remove nó que possue 2 filhos
                if(p->folhaEsquerda != nullptr && p->folhaDireita != nullptr){
                    node *aux = p->folhaEsquerda;

                    while(aux->folhaDireita != nullptr)
                        aux = aux->folhaDireita;

                    p->item = aux->item;
                    aux->item = it;

                    std::cout <<"Elemento trocado: "<< it.palavra<<std::endl;
                    
                    p->folhaEsquerda = removeRecursivo(p->folhaEsquerda, it);
                    return p;
                }
                else{
                    // remove nó que possue 1 filho
                    node *aux;

                    if(p->folhaEsquerda != nullptr)
                        aux = p->folhaEsquerda;
                    else
                        aux = p->folhaDireita;

                    delete p;

                    std::cout <<"Elemento com 1 filho removido: "<< it.palavra<<std::endl;
                    
                    return aux;
                }
            }
        } else {
            if(it.palavra < p->item.palavra)
                p->folhaEsquerda = removeRecursivo(p->folhaEsquerda, it);
            else
                p->folhaDireita = removeRecursivo(p->folhaDireita, it);
        }

        // recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        p->altura = max(p->folhaEsquerda->alturaNo(), p->folhaDireita->alturaNo()) + 1;

        return p;
    }
}

void ArvAVL::emOrdem(node *p, std::ofstream& outFile){
    if(p != nullptr){
        emOrdem(p->folhaEsquerda, outFile);
        p->imprimirNo(outFile);
        emOrdem(p->folhaDireita, outFile);
    }
}

int ArvAVL::fatorBalanceamento(node *p){
    if (p == nullptr) return 0;

    return p->folhaDireita->alturaNo() - p->folhaEsquerda->alturaNo();
}

node * ArvAVL::rotacaoEsquerda(node *x){
    node *y, *t;

    //guardando ponteiros
    y = x->folhaDireita; 
    t = y->folhaEsquerda; 

    //rotacao
    y->folhaEsquerda = x;
    x->folhaDireita = t;

    // recalcula a altura dos nós que foram movimentados
    x->altura = max(x->folhaEsquerda->alturaNo(), x->folhaDireita->alturaNo()) + 1;
    y->altura = max(y->folhaEsquerda->alturaNo(), y->folhaDireita->alturaNo()) + 1;

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

    // recalcula a altura dos nós que foram movimentados
    x->altura = max(x->folhaEsquerda->alturaNo(), x->folhaDireita->alturaNo()) + 1;
    y->altura = max(y->folhaEsquerda->alturaNo(), y->folhaDireita->alturaNo()) + 1;

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

void ArvAVL::apagaRecursivo(node *p){
    if(p!=nullptr){
        apagaRecursivo(p->folhaEsquerda);
        apagaRecursivo(p->folhaDireita);
        delete p;
    }
}

void ArvAVL::limpa(){
    apagaRecursivo(root);
    root = nullptr;
}