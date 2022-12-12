#ifndef _VERBETE_
#define _VERBETE_

#include <string>
#include "FilaEncadeada.hpp"

class Verbete{
    public: 
        FilaEncadeada * significado;
        std::string palavra;
        char tipoPalavra;
        void imprime();
        void inserirSignificado(FilaEncadeada * significado);
};

#endif