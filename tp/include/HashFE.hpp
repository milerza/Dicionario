#ifndef _HASH_FE_
#define _HASH_FE_

#include "FilaEncadeada.hpp"

#include <fstream>

class HashFE{
    public:
        HashFE();
        ~HashFE();
        FilaEncadeada * Pesquisa(std::string palavra);
        void inserir(TipoItem item);
        void remover();
        void imprimir(std::ofstream& outFile);
        void removerPreenchidos();
    private:
        static const int M = 1000;
        int Hash(std::string palavra);
        FilaEncadeada Tabela[M];
};

#endif