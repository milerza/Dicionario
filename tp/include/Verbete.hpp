#ifndef _VERBETE_
#define _VERBETE_

#include <string>
#include "FilaEncadeada.hpp"

class Verbete{
    public:
        std::string palavra;
        FilaEncadeada * significado;
        void Imprime();
};

#endif