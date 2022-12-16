#include "ArvAVL.hpp"

#include<iostream>

extern "C"{
    #include <msgassert.h>
    #include <memlog.h>
    #include <sys/time.h>
    #include <sys/resource.h>
}

int altura(node *N) { 
    if (N == nullptr) 
        return 0; 
    return N->altura; 
} 

ArvAVL::ArvAVL(){
    root = nullptr;
}

ArvAVL::~ArvAVL(){
    limpa();
}

void ArvAVL::insere(Verbete it){
    insereRecursivo(this->root, it);
}

void ArvAVL::imprime(std::ofstream& output){
    this->emOrdem(this->root, output);
}

void ArvAVL::procuraNaoVazio(node * p, Verbete * a, int * i){
    if(p==nullptr) return;

    procuraNaoVazio(p->folhaEsquerda, a, i);

    
    if(!p->item->vazio()){
        escreveMemLog((long int)(&a[*i]), sizeof(long int), 3);
        a[*i] = *(p->item);
        (*i)++;
    }

    procuraNaoVazio(p->folhaDireita, a, i);
}

void ArvAVL::removeSig(){
    RemoveVetor(root);
}

void ArvAVL::pesquisa(node * p, int * i){
    if(p!= nullptr){
        leMemLog((long int)(p), sizeof(long int), 3);
        if(!p->item->vazio()) (*i)++;
        pesquisa(p->folhaEsquerda, i);
        pesquisa(p->folhaDireita, i);
    } 
}

void ArvAVL::RemoveVetor(node * p){
   
    Verbete * aSeremExcluidos;
    int i = 0; int t =0;

    pesquisa(p, &i);

    aSeremExcluidos = new Verbete[i];
    
    procuraNaoVazio(p, aSeremExcluidos, &t);   

    for(int j = 0; j < i; j++){
        removeRecursivo(root, aSeremExcluidos[j]);
    }

    p = this->balancearArvore(p);
    
}

node* ArvAVL::insereRecursivo(node* &p, Verbete it){
    if(p == nullptr){
        escreveMemLog((long int)(p), sizeof(long int), 1);
        p = new node();
        p->item->palavra = it.palavra;
        p->item->significado = it.significado;
        p->item->tipoPalavra = it.tipoPalavra;

        if(it.significado[0] != "")
            p->item->tam++;
    }
    else{
        if(it.palavra < p->item->palavra){
            leMemLog((long int)(p), sizeof(long int), 1);
            p->folhaEsquerda = insereRecursivo(p->folhaEsquerda, it);
        }
        else if(it.palavra > p->item->palavra){
            leMemLog((long int)(p), sizeof(long int), 1);
            p->folhaDireita = insereRecursivo(p->folhaDireita, it);
        } else{
            escreveMemLog((long int)(p), sizeof(long int), 1);
            try{
                p->insereVerbete(&it);
            } catch(const char* e){
                leMemLog((long int)(p), sizeof(long int), 1);
                insereRecursivo(p->folhaDireita, it);
            }
        }
    }
    leMemLog((long int)(p), sizeof(long int), 1);
    p->altura = this->max(altura(p->folhaEsquerda), altura(p->folhaDireita)) + 1;
    
    leMemLog((long int)(p), sizeof(long int), 1);
    p = this->balancearArvore(p);
    return p;
}

node *ArvAVL::balancearArvore(node *p){
    short fb = fatorBalanceamento(p);

    // Rotação direita
    if(fb < minFB && fatorBalanceamento(p->folhaDireita) <= 0)
        p = rotacaoEsquerda(p);

    // Rotação esquerda
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

node * ArvAVL::removeRecursivo(node* &p, Verbete it){
    if(p == nullptr){
        std::cout <<"Valor nao encontrado!\n"<< it.palavra<<std::endl;
        return p;
    
    } 
    if(it.palavra < p->item->palavra){
        leMemLog((long int)(p), sizeof(long int), 3);
        p->folhaEsquerda = removeRecursivo(p->folhaEsquerda, it);
    }            
    else if(it.palavra > p->item->palavra){
        leMemLog((long int)(p), sizeof(long int), 0);
        p->folhaDireita = removeRecursivo(p->folhaDireita, it);
    // procura o nó a remover
    }
    else{
        if( (p->folhaDireita == nullptr) || (p->folhaEsquerda == nullptr) ) { 
            node *temp;

            if(p->folhaEsquerda != nullptr) temp = p->folhaEsquerda;
            else temp = p->folhaDireita;
  
            // No folha
            if (temp == nullptr) { 
                std::cout <<"Removido no folha: \n"<< it.palavra <<std::endl;
                escreveMemLog((long int)(p), sizeof(long int), 3);
                temp = p; 
                p = nullptr; 
            } 
            else{ //No com um filho 
                escreveMemLog((long int)(p), sizeof(long int), 3);
                *p = *temp;
                std::cout <<"Removido no com um filho: \n"<< it.palavra <<std::endl;
            }                         
            delete temp; 
        } 
        else{
            // no com dois filhos
            // sucesspr menor da subarvore da direita

            node * temp = p->folhaDireita;

            while(temp->folhaEsquerda != nullptr){
                leMemLog((long int)(p), sizeof(long int), 3);
                temp = temp->folhaEsquerda;
            }
  
            // copia o conteudo do menor 
            escreveMemLog((long int)(p), sizeof(long int), 3);
            p->item = temp->item; 
            std::cout <<"Troca no com um filho: \n"<< it.palavra <<std::endl;

            leMemLog((long int)(p), sizeof(long int), 3);
            // Deleta o menor na posicao folha
            p->folhaDireita = removeRecursivo(p->folhaDireita, *(temp->item));
        }
    }

    if (p == nullptr) 
        return p; 
        

    // recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    p->altura = max(altura(p->folhaEsquerda), altura(p->folhaDireita)) + 1;

    return p;
    
}

void ArvAVL::emOrdem(node *p, std::ofstream& outFile){
    if(p != nullptr){
        leMemLog((long int)(p), sizeof(long int), 2);
        emOrdem(p->folhaEsquerda, outFile);
        p->imprimirNo(outFile);
        emOrdem(p->folhaDireita, outFile);
    }
}

int ArvAVL::fatorBalanceamento(node *p){
    if (p == nullptr) return 0;

    return   altura(p->folhaEsquerda) - altura(p->folhaDireita);
}

node * ArvAVL::rotacaoEsquerda(node *x){
    node *y, *t;

    leMemLog((long int)(x), sizeof(long int), 1);
    leMemLog((long int)(x), sizeof(long int), 2); 
    leMemLog((long int)(x), sizeof(long int), 3);
    //guardando ponteiros
    y = x->folhaDireita; 
    t = y->folhaEsquerda; 

    //rotacao
    y->folhaEsquerda = x;
    x->folhaDireita = t;

    // recalcula a altura dos nós que foram movimentados
    x->altura = max(altura(x->folhaEsquerda), altura(x->folhaDireita)) + 1;
    y->altura = max(altura(y->folhaEsquerda), altura(y->folhaDireita)) + 1;

    return y;
}

node * ArvAVL::rotacaoDireita(node *x){
    node *y, *t;
    leMemLog((long int)(x), sizeof(long int), 1);
    leMemLog((long int)(x), sizeof(long int), 2);
    leMemLog((long int)(x), sizeof(long int), 3);

    //guardando ponteiros
    y = x->folhaEsquerda; 
    t = y->folhaDireita; 

    //rotacao 
    y->folhaDireita = x;
    x->folhaEsquerda = t; 

    // recalcula a altura dos nós que foram movimentados
    x->altura = max(altura(x->folhaEsquerda), altura(x->folhaDireita)) + 1;
    y->altura = max(altura(y->folhaEsquerda), altura(y->folhaDireita)) + 1;

    return y;
}

node* ArvAVL::rotacaoEsquerdaDireita(node* x){ 
    x->folhaEsquerda = this->rotacaoEsquerda(x->folhaEsquerda);
    return this->rotacaoDireita(x);
}

node* ArvAVL::rotacaoDireitaEsquerda(node* x){
    x->folhaDireita = this->rotacaoDireita(x->folhaDireita);
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