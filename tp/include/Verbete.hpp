#ifndef _VERBETE_
#define _VERBETE_

#include <string>
#include "FilaEncadeada.hpp"

class Verbete{
    public: 
        FilaEncadeada * significado;
        std::string palavra;
        void imprime();
        void inserirSignificado(FilaEncadeada * significado);
};

#endif