#include "HashFE.hpp"
#include "Verbete.hpp"

HashFE::HashFE(){
    Tabela = new FilaEncadeada[M];
}

FilaEncadeada * HashFE::Pesquisa(std::string palavra){
    int pos;
    FilaEncadeada * item;

    pos = Hash(palavra);
    item = &Tabela[pos];

    if (item == nullptr) throw "palavra inexistente!";

    return item;
}

void HashFE::inserir(Verbete item){
    int pos;
    std::string sig = item.significado->desenfileira().significado;
    char pro = item.significado->desenfileira().tipoPalavra;
    
    pos = Hash(item.palavra);

    while (!item.significado->vazia()){
        Tabela[pos].enfilera(item.palavra,sig, pro);
    }
}

void HashFE::remover(std::string palavra){
    int pos = Hash(palavra);
    //limpa todos os significados  da palavra
    Tabela[pos].limpa();
}

void HashFE::imprimir(std::string palavra){
    int pos = Hash(palavra);
    Tabela[pos].imprimir(palavra);
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
            Tabela[i].limpa();
        }
    }
}