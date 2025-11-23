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


#endif