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

//fazer a indexação invertida como foi descrito no arquivo
//  Índice invertido = palavra → lista de (idArquivo, frequência)
//  Permite encontrar arquivos rapidamente a partir de uma palavra.

class InvertedText{
    public:
    unordered_map<string, unordered_map<int,int>> indice; //uma tabela hash de chave e valor que possui uma string e outra tabela hash de int,int
    
    void construir (const Indexer& indexador); //constroi o indice invertido usando os dados do indexador

    void buscar(const vector<string> &termos, const Indexer& indexador);
};

//fazer o serializer 
// método responsável por carregar o indexer e salvar em um arquivo binario
//Isso permite que o programa seja fechado e aberto sem perder o índice.

class Serializer {
    public:
    static void salvar(const Indexer& idx, const string& nomeArq);
    static void carregar(Indexer&idx , const string& nomeArq);

    private:
    static void writeString(std::ofstream& out, const string& s);
    static string readString(std::ifstream& in);
};

#endif