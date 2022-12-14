#include "HashFE.hpp"

HashFE::HashFE(){
}

HashFE::~HashFE(){
    remover();
}

FilaEncadeada * HashFE::Pesquisa(std::string palavra){
    int pos;
    FilaEncadeada * item;

    pos = Hash(palavra);
    item = &Tabela[pos];

    if (item == nullptr) throw "palavra inexistente!";

    return item;
}

void HashFE::inserir(TipoItem item){
    int pos, x;
    
    pos = Hash(item.palavra);
    x = Tabela[pos].PesquisaPosicao(item.palavra);

    if(x == -1)
        Tabela[pos].enfilera(item);

    else Tabela[pos].AtualizaPosicao(item, x);
}

void HashFE::remover(){
    for(int i = 0; i < M; i++){
        Tabela[i].limpa();
    }
}

void HashFE::imprimir(std::ofstream& outFile){
    for(int i = 0; i < M; i++){
        if(!Tabela[i].vazia()){
            Tabela[i].imprimir(outFile);
        }
    }    
}

int HashFE::Hash(std::string palavra){
    int pos, tam;
    tam = palavra.length();

    // Cria posicao na tabela para a palavra 
    // (i+1) é o peso caso tenhamos anagramas
    for(int i = 0; i<tam; i++) 
        pos += (i+1) * palavra[i];

    // retorna um numero entre 0 e M
    return pos % M;
}

void HashFE::removerPreenchidos(){
    for(int i =0; i<M; i++){
        if(!Tabela[i].vazia()){
            Tabela[i].pecorreERemove();
        }
    }
}