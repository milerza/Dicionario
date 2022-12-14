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

void ArvAVL::procuraNaoVazio(node * p, Verbete * a, int * i){
    if(p==nullptr) return;

    procuraNaoVazio(p->folhaEsquerda, a, i);

    if(!p->item.vazio()){
        a[*i] = p->item;
        (*i)++;
    }

    procuraNaoVazio(p->folhaDireita, a, i);
}

void ArvAVL::removeSig(){
    RemoveVetor(root);
}

void ArvAVL::pesquisa(node * p, int * i){
    if(p!= nullptr){
        if(!p->item.vazio()) (*i)++;
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
        return p;
    
    } 
    if(it.palavra < p->item.palavra)
            p->folhaEsquerda = removeRecursivo(p->folhaEsquerda, it);
            
    else if(it.palavra > p->item.palavra)
        p->folhaDireita = removeRecursivo(p->folhaDireita, it);
    // procura o nó a remover
    
    else{
        if( (p->folhaDireita == nullptr) || (p->folhaEsquerda == nullptr) ) { 
            node *temp;

            if(p->folhaEsquerda != nullptr) temp = p->folhaEsquerda;
            else temp = p->folhaDireita;
  
            // No folha
            if (temp == nullptr) { 
                std::cout <<"Removido no folha: \n"<< it.palavra <<std::endl;

                temp = p; 
                p = nullptr; 
            } 
            else{ //No com um filho 
                *p = *temp;
                std::cout <<"Removido no com um filho: \n"<< it.palavra <<std::endl;

            }
            
                         
            delete temp; 
        } 
        else{
            // no com dois filhos
            // sucesspr menor da subarvore da direita

            node *temp = p->folhaDireita;

            while(temp->folhaEsquerda != nullptr)
                temp = temp->folhaEsquerda;
  
            // copia o conteudo do menor 
            p->item = temp->item; 
            std::cout <<"Troca no com um filho: \n"<< it.palavra <<std::endl;

  
            // Deleta o menor na posicao folha
            p->folhaDireita = removeRecursivo(p->folhaDireita, temp->item);
        }
    }

    if (p == nullptr) 
        return p; 
        

    // recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    p->altura = max(p->folhaEsquerda->alturaNo(), p->folhaDireita->alturaNo()) + 1;

    return p;
    
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