#ifndef _NODE_
#define _NODE_

#include <string>
#include <fstream>

class Verbete{
    public: 
        int tam = 0, max = 10;
        std::string significado[10];
        std::string palavra;
        char tipoPalavra;

        bool vazio(){return tam == 0;}
        bool cheio(){return tam == max;}
};

//--- tam :
// serve para contar a quantidade de 
// significados que o verbete tem
// --- max : é o maximo de significados por nó
class node {
    public:
        Verbete item;
        int altura;
        node *folhaEsquerda;
        node *folhaDireita;

        node();
        int alturaNo();
        
        int insereVerbete(Verbete * verbete);
        void imprimirNo(std::ofstream& outFile);

};

#endif