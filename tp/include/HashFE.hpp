#ifndef _HASH_FE_
#define _HASH_FE_

#include "FilaEncadeada.hpp"
#include "Verbete.hpp"

class HashFE{
    public:
        HashFE();
        FilaEncadeada * Pesquisa(std::string palavra);
        void inserir(Verbete it);
        void remover(std::string palavra);
        void imprimir(std::string palavra);
        void removerPreenchidos();
    private:
        static const int M = 1000;
        int Hash(std::string palavra);
        FilaEncadeada * Tabela;
};

#endif