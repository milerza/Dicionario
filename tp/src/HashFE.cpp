#include "HashFE.hpp"
#include "QuickSort.hpp"

extern "C"{
    #include <msgassert.h>
    #include <memlog.h>
    #include <sys/time.h>
    #include <sys/resource.h>
}
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
    
    leMemLog((long int)(Tabela), sizeof(long int), 1);
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
    TipoItem *listaItens;
    int t = 0;
    int l = 0;
    for(int i = 0; i < M; i++){
        t += Tabela[i].getTamanho();
    }   
    listaItens = new TipoItem[t]; 

    for(int i = 0; i < M; i++){
        if(!Tabela[i].vazia()){
            Tabela[i].preencheLista(listaItens, &l);
        }
    }
    leMemLog((long int)(listaItens), sizeof(long int), 2);
    quickSortRecursivo(listaItens, 0, t - 1);

    for(int i = 0; i < t; i++){
        listaItens[i].imprimir(outFile);
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
            leMemLog((long int)(&Tabela[i]), sizeof(long int), 3);
            Tabela[i].pecorreERemove();
        }
    }
}