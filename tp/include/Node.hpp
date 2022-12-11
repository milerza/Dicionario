#ifndef _NODE_
#define _NODE_

#include "Verbete.hpp"

class node {
    public:
        Verbete *item;
        int altura;
        node *folhaEsquerda;
        node *folhaDireita;
        node *pai;

        node();
        ~node();
        int alturaNo();
};

#endif