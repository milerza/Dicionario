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
    
    inFile.open(input.c_str());
    
    //------ Verificando validade se o arquivo existe
    avisoAssert(!inFile.fail(), "Arquivo inexistente!");

    while (std::getline(inFile, aux, '[')){
        //recebe Tipo Palavra
        verbete.tipoPalavra = aux[0];

        std::getline(inFile, verbete.palavra, ']');
        std::getline(inFile, verbete.significado[0]);
         
        //enfilera o siginifiado caso exista
        arvore->insere(verbete);
    }

    inFile.close();

    //imprimir dic 
    std::ofstream outFile;
    outFile.open(output.c_str());
    outFile << "Palavras adicionadas" << std::endl;
    arvore->imprime(outFile);

    // remover verbetes com pelo menos um significado
    arvore->removeSig();

    //imprimir dic
    arvore->imprime(outFile);

    //chamar destrutor;
    //arvore->~ArvAVL();
    outFile.close();

}

void executarHash(std::string input, std::string output){
    TipoItem verbete;
    std::string aux;
    std::ifstream inFile;

    //cria dic
    HashFE * hash = new HashFE;

    //insere verbetes e sig
    
    inFile.open(input.c_str());
    
    //------ Verificando validade se o arquivo existe
    avisoAssert(!inFile.fail(), "Arquivo inexistente!");

    while (std::getline(inFile, aux, '[')){
        //recebe Tipo Palavra
        verbete.tipoPalavra = aux[0];

        std::getline(inFile, verbete.palavra, ']');
        std::getline(inFile, verbete.significado);
                
        hash->inserir(verbete);
    }

    inFile.close();

    //criando Arquivo de saída
    std::ofstream outFile;
    outFile.open(output.c_str());
    
    //imprimir dic 
    //    hash->imprimir(outFile);

    // remover verbetes com pelo menos um significado
    //hash->removerPreenchidos();

    //imprimir dic
    //hash->imprimir(outFile);    

    //chamar destrutor;
    //hash->~HashFE();

    outFile.close();
}

int main(int argc, char* argv[]) {
    std::string caminhoEntrada, caminhoSaida, tipoDic;
    //------ Ler valores passados 

    /*for (int i = 0; i < argc; i++){
        if (std::string(argv[i]) == "-i"){ //arquivo de input
            caminhoEntrada = std::string(argv[i + 1]);
        }
        else if (std::string(argv[i]) == "-o"){ //arquivo de saida
            caminhoSaida = std::string(argv[i + 1]);
        }
        else if (std::string(argv[i]) == "-t"){ //indica o tipo de dicionario: arvore avl ou hash
            tipoDic = std::string(argv[i + 1]);
        }
    }*/

    // ------ Cria Dicionario
    tipoDic= "hash"; caminhoEntrada = "teste.txt"; caminhoSaida = "saida.txt";
    //verificando se o tipo do dicionario especificado está correto
    avisoAssert(tipoDic == "arv" ||tipoDic == "void ArvAVL::pesquisa()" , "Tipo de dicionário inválido! Você quis dizer: `arv` ou `hash`?");

    if(tipoDic == "arv"){
        executarArv(caminhoEntrada, caminhoSaida);
    } else if(tipoDic =="hash"){
        executarHash(caminhoEntrada, caminhoSaida);
    }

    return 0;
}