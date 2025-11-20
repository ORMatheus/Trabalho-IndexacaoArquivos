#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <sstream>
namespace fs = std::filesystem;
using namespace std;

class helper{
    
    public:
    void lerArquivo();
    string processarTexto(){
        string removerPonto();
        string ConvertMinusculo();
        string stopWords();
    }

    string Buscar();
    string multiplaBusca();
    
    int txtToId(); 

    private:
    string removerPonto();
    string ConvertMinusculo();
    string stopWords();
    
};

class index{
    int convertToId();//manter o indice principal (Converter o nome"texto" para o ID "int")
    void includeID(); //inclui o id na tabela
    string convertToName(); //converter o id para o nome do arquivo 
    
}; 

//Fernando
class textProcessor{
    string processarTexto(){
        string removerPonto();
        string ConvertMinusculo();
        string stopWords();
    }
};


//Matheus
class indexer{
    private:
    //A tabela hashprincipal que esta guardando o arquivo ID e trazendo para palavras
    unordered_map<int, vector<string>> tabelaHash;
    //tabela hash auxiliar para guardar o nome do arquivo vs ID (Simulando a classe Index)
    unordered_map<string,int> nomeParaId;
    int contadorId=1;
    //tabela hash para guardar as stopwords
    unordered_set<string> stopwords = {"a", "o", "de", "para", "com", "um", "uma", "os", "as", "e", "do", "da"};

    public:
    //metodo para obter o Id
    int getId(string nomedoArquivo){
        if(nomeParaId.find(nomedoArquivo)== nomeParaId.end() ){ //significa que o arquivo ainda nao tem um id e precisa ser criado
            nomeParaId[nomedoArquivo]=contadorId++;
        }
        return nomeParaId[nomedoArquivo];
    }

    //salvar na hash 
    
    
};

//void lerArquivos(); // catalogar arquivo por arquivo 
//void processarTexto(); //realizar a normalização do texto dentro do arquivo.
//int getId(); // pegar o id do index
//void saveOnHash(); //salvar o arquivo ja tratado e salva-lo na hash.
class Serializer{
    void saveIndece();
    void loadIndice();
};

class queryProcessor{
    string Buscar(string palavra); //retorna os nomes dos arquivos que possuem a palavra buscada
    string multiplaBusca(string palavra1,string palavra2); //retorna os nomes dos arquivos que possuem a palavra buscada
    
};

class comandLineInterface{
    void funcoesDaMain(); // funções da main Dependendo dos argumentos, ele deve criar e utilizar os objetos Indexer, Serializer e QueryProcessor para realizar as operações de indexação ou busca
};