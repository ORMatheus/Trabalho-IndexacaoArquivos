#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>

// Alias para facilitar o uso
namespace fs = std::filesystem;

using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_set;


 //TEXT PROCESSOR
//  Classe responsável por:
//   - Transformar texto em minúsculas
//   - Remover pontuação
//   - Separar em palavras
//   - Remover stopwords
//   Isso garante que todas as palavras sejam tratadas de maneira igual.

class TextProcessor{
    private:
    unordered_set<string> stopwords ; //conjunto de palavras para ser ignoradas

    public:
    TextProcessor(const string & stopwordsFile); //construtor recebe o nome do arquivo stopwords

    //funções auxiliares
    string minuscula(const string&s);
    string removerPontuacao(const string&s);
    vector <string> separarPalavras(const string &s);

    //função principal para fazer o pre processamento
    vector<string > processarLinha(const string& linha);


};

//indexe
//atribuir os ids numericos para cada arquivo 
//ler o conteudo dos arquivos da pasta
//processar as palavras utilizando o textProcessor
//guardar na memoria
class Indexer{
    public:
    unordered_map<string,int> nomeParaId;//armazenar na hash o conteudo chave valor que vai de uma string para um int(id)

    unordered_map<int,vector<string> > palavrasPorId; //id para a lista de palavras que esta no arquivo

    //fazer um contador para os id no arquivo 
    int proximoId;

    TextProcessor processador; //fazer a instanciação do text processor como processador para tratar as strings

    Indexer(); //chamada recursiva da propia classe

    //verificar se o arquivo tem id depois ler todos os arquivos presentes na pasta

    int pegarId(const string&nomeArquivo); //se o arquivo nao tiver id , criar

    void lerPasta(const string& caminhoPasta);



};


#endif