#include "ArvAVL.hpp"

#include<iostream>

node * ArvAVL::pesquisaDic(Verbete it){
    node * p = pesquisaRecursivo(root, it);
   return p;
}

int ArvAVL::insereDic(Verbete it){
    insereRecursivo(this->root, &it);
}

void ArvAVL::imprimeDic(){
    this->emOrdem(this->root);
}

int ArvAVL::atualizaDic(Verbete it){
    
}

int ArvAVL::removeDic(Verbete it){

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
            p->item->inserirSignificado(it->significado);
        }
    }
    p->altura = this->max(p->folhaEsquerda->alturaNo(), p->folhaDireita->alturaNo()) + 1; //mexer aquiii

    p = this->balancearArvore(p);
}

node *ArvAVL::balancearArvore(node *p){
    short fb = fatorBalanceamento(p);

    // Rotação esquerda
    if(fb < minFB && fatorBalanceamento(p->folhaDireita) <= 0)
        p = rotacaoEsquerda(p);

    // Rotação direita
    else if(fb > maxFB && fatorBalanceamento(p->folhaEsquerda) >= 0)
        p = rotacaoDireita(p);

    // Rotação dupla: corrige quebra à direta 
    // com rotação à esquerda e rotaciona pra direita
    else if(fb > maxFB && fatorBalanceamento(p->folhaEsquerda) < 0)
        p = rotacaoEsquerdaDireita(p);

    // Rotação dupla: corrige quebra à esquerda 
    // com rotação à direita e rotaciona pra esquerda
    else if(fb < minFB && fatorBalanceamento(p->folhaDireita) > 0)
        p = rotacaoDireitaEsquerda(p);

    return p;
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

node * ArvAVL::removeRecursivo(node* &p, Verbete it){
    if(p == nullptr){
        printf("Valor nao encontrado!\n");
        return nullptr;
    } else { // procura o nó a remover
        if(p->item->palavra == it.palavra) {
            // remove nós folhas (nós sem filhos)
            if(p->folhaEsquerda == nullptr && p->folhaDireita == nullptr) {
                delete p;
                printf("Elemento folha removido: %d !\n", it.palavra);
                return p;
            }
            else{
                // remover nós que possuem 2 filhos
                if(p->folhaEsquerda != nullptr && p->folhaDireita != nullptr){
                    node *aux = p->folhaEsquerda;
                    while(aux->folhaDireita != nullptr)
                        aux = aux->folhaDireita;
                    p->item = aux->item;
                    aux->item = &it;
                    printf("Elemento trocado: %d !\n", it.palavra);
                    p->folhaEsquerda = removeRecursivo(p->folhaEsquerda, it);
                    return p;
                }
                else{
                    // remover nós que possuem apenas 1 filho
                    node *aux;
                    if(p->folhaEsquerda != nullptr)
                        aux = p->folhaEsquerda;
                    else
                        aux = p->folhaDireita;
                    delete p;
                    printf("Elemento com 1 filho removido: %d !\n", it.palavra);
                    return aux;
                }
            }
        } else {
            if(it.palavra < p->item->palavra)
                p->folhaEsquerda = removeRecursivo(p->folhaEsquerda, it);
            else
                p->folhaDireita = removeRecursivo(p->folhaDireita, it);
        }

        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        p->altura = max(p->folhaEsquerda->alturaNo(), p->folhaDireita->alturaNo()) + 1;

        // verifica a necessidade de rebalancear a árvore
        p = balancearArvore(p);

        return p;
    }
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

    //corrigindo pais
    y->pai = x->pai;
    x->pai = y;
    t->pai = x;

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

    //corrigindo pais
    y->pai = x->pai;
    x->pai = y;
    t->pai = x;

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
