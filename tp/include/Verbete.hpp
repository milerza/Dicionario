#ifndef _VERBETE_
#define _VERBETE_

#include <string>
#include "FilaEncadeada.hpp"

class Verbete{
    public:
        std::string palavra;
        std::string significado;
        void imprime();
        void inserirSignificado(std::string significado);
};

#endif