#ifndef _VERBETE_
#define _VERBETE_

#include <string>
#include "FilaEncadeada.hpp"

class Verbete{
    public: 
        std::string significado;
        std::string palavra;
        char tipoPalavra;
        void imprime(std::string output);
};

#endif