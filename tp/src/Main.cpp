#include "ArvAVL.hpp"
#include "HashFE.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

extern "C"{
    #include <msgassert.h>
}

void executarArv(std::string input, std::string output){
    Verbete verbete;
    std::string aux;

    //cria dic
    ArvAVL * arvore = new ArvAVL;

    //insere verbetes e sig
    std::ifstream inFile;

    int * valores;
    
    inFile.open(input.c_str());
    
    //------ Verificando validade se o arquivo existe
    avisoAssert(!inFile.fail(), "Arquivo inexistente!");

    while (std::getline(inFile, aux, '[')){
        //recebe Tipo Palavra
        verbete.tipoPalavra = aux[0];

        std::getline(inFile, verbete.palavra, ']');
        std::getline(inFile, aux);
        
        //enfilera o siginifiado caso exista 
        if(aux != "")
            verbete.significado->
                enfilera(verbete.palavra, aux, verbete.tipoPalavra);
    }

    inFile.close();

    //imprimir dic 
    arvore->imprime();

    // remover verbetes com pelo menos um significado

    //imprimir dic

    //chamar destrutor;
}

void executarHash(std::string input, std::string output){
    
}

int main(int argc, char* argv[]) {
    std::string caminhoEntrada, caminhoSaida, tipoDic;
    //------ Ler valores passados 

    for (int i = 0; i < argc; i++){
        if (std::string(argv[i]) == "-i"){ //arquivo de input
            caminhoEntrada = std::string(argv[i + 1]);
        }
        else if (std::string(argv[i]) == "-o"){ //arquivo de saida
            caminhoSaida = std::string(argv[i + 1]);
        }
        else if (std::string(argv[i]) == "-t"){ //indica o tipo de dicionario: arvore avl ou hash
            tipoDic = std::stoi(std::string(argv[i + 1]));
        }
    }

    // ------ Cria Dicionario

    //verificando se o tipo do dicionario especificado está correto
    avisoAssert(tipoDic == "arv" ||tipoDic == "hash" , "Tipo de dicionário inválido! Você quis dizer: `arv` ou `hash`?");

    if(tipoDic == "arv"){
        executarArv(caminhoEntrada, caminhoSaida);
    } else if(tipoDic =="hash"){
        executarHash(caminhoEntrada, caminhoSaida);
    }

    return 0;
}