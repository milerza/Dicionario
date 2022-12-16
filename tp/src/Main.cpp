#include "ArvAVL.hpp"
#include "HashFE.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

extern "C"{
    #include <msgassert.h>
    #include <memlog.h>
    #include <sys/time.h>
    #include <sys/resource.h>
}

void executarArv(std::string input, std::string output){
    Verbete verbete ;
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
        std::getline(inFile, aux);

        if(aux!= "\r"|| aux!= ""){
            verbete.significado[0] =  aux;
        } 
         
        //enfilera o siginifiado caso exista
        arvore->insere(verbete);
    }

    inFile.close();

    //imprimir dic 
    std::ofstream outFile;
    outFile.open(output.c_str());
    
    arvore->imprime(outFile);

    // remover verbetes com pelo menos um significado
    arvore->removeSig();

    //imprimir dic
    
    arvore->imprime(outFile);

    //chamar destrutor;
    arvore->~ArvAVL();
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
        std::getline(inFile, aux);

        if(aux!= "\r"|| aux!= ""){
            verbete.significado[0] =  aux;
        } 
        
                
        hash->inserir(verbete);
    }

    inFile.close();

    //criando Arquivo de saída
    std::ofstream outFile;
    outFile.open(output.c_str());
    
    //imprimir dic 
    hash->imprimir(outFile);
    // remover verbetes com pelo menos um significado
    hash->removerPreenchidos();

    //imprimir dic
    hash->imprimir(outFile);    

    //chamar destrutor;
    hash->~HashFE();

    outFile.close();
}

int main(int argc, char* argv[]) {
    std::string caminhoEntrada, tipoDic;
    std::string  caminhoSaida = "out.txt";
    std::ofstream inFile;
    float tempo_total = 0.0;

    bool ativar_memlog = 0;
    // configuração do memlog
    std::string logdir = "run.log";
    std::ofstream logfile(logdir);
    logfile.close();

    char *logdir_name = new char[logdir.length() + 1];
    std::strcpy(logdir_name, logdir.c_str());

    iniciaMemLog(logdir_name);


    inFile.open("analiseTempo.txt");

    //------ Ler valores passados 
    
    for (int i = 0; i < argc; i++){
        if (std::string(argv[i]) == "-i"){ //arquivo de input
            caminhoEntrada = std::string(argv[i + 1]);
        }
        else if (std::string(argv[i]) == "-o"){ //arquivo de saida
            caminhoSaida = std::string(argv[i + 1]);
        }
        else if (std::string(argv[i]) == "-t"){ //indica o tipo de dicionario: arvore avl ou hash
            tipoDic = std::string(argv[i + 1]);
        }
        else if (std::string(argv[i]) == "-l"){ //ativa ou desativa memlog
            ativar_memlog = std::stoi(std::string(argv[i + 1]));
        }
    }
    
    caminhoEntrada = "dict.clean.txt";
    //caminhoEntrada = "teste.txt";

    caminhoSaida = "saida.txt";
    ativar_memlog = 1;
    tipoDic = "arv";


     if (ativar_memlog) {
        ativaMemLog();
    } else {
        desativaMemLog();
    }

    // ------ Ver qual estrutura usar
    //verificando se o tipo do dicionario especificado está correto
    avisoAssert(tipoDic == "arv" ||tipoDic == "hash" , "Tipo de dicionário inválido! Você quis dizer: `arv` ou `hash`?");
    
    if(caminhoSaida=="out.txt"){
        std::cout <<"Caminho saida não especificado. Caminho padrão `out.txt`";
    }

    // declarações para medir o tempo
    struct rusage usage;
    struct timeval start_user, end_user, start_system, end_system;

    // ---------------------------------------------------------------------------------------
    
    // start reading u_time
        getrusage(RUSAGE_SELF, &usage);
        start_user = usage.ru_utime;
        start_system = usage.ru_stime;

    if(tipoDic == "arv"){
        executarArv(caminhoEntrada, caminhoSaida);
    } else if(tipoDic =="hash"){
        executarHash(caminhoEntrada, caminhoSaida);
    }

    finalizaMemLog();
     // ---------------------------------------------------------------------------------------
        // end reading u_time
        getrusage(RUSAGE_SELF, &usage);
        end_user = usage.ru_utime;
        end_system = usage.ru_stime;

        // tv_sec: seconds; tv_usec: microseconds
        // ru_utime: total amount of time spent executing in usermode,
        // expressed in a timeval structure (seconds plus microseconds)
        float utime = (end_user.tv_sec - start_user.tv_sec) + 1e-6 * (end_user.tv_usec - start_user.tv_usec);
        float stime = (end_system.tv_sec - start_system.tv_sec) + 1e-6 * (end_system.tv_usec - start_system.tv_usec);
        tempo_total = tempo_total + (utime + stime);
        inFile << std::fixed << "Tempo total: " << utime + stime  
        << "      Tipo Dicionario: "<< tipoDic << std::endl;

    return 0;
}