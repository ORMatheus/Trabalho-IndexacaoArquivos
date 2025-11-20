#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>
// #include <filesystem>
#include <unordered_map>
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
class TextProcessor {
public:
    explicit TextProcessor(const std::string& stopwords_path = "stopwords.txt") {
        std::ifstream file(stopwords_path);
        if (!file.is_open()) return;

        std::string word;
        while (std::getline(file, word)) {
            word.erase(std::remove_if(word.begin(), word.end(), ::isspace), word.end());
            if (!word.empty()) {
                stopwords.insert(word);
            }
        }
    }

    std::vector<std::string> process(const std::string& text) const {
        std::string cleaned = to_lowercase(text);
        cleaned = remove_punctuation(cleaned);
        std::vector<std::string> words = split_into_words(cleaned);

        std::vector<std::string> result;
        result.reserve(words.size());
        for (const auto& w : words) {
            if (!w.empty() && stopwords.find(w) == stopwords.end()) {
                result.push_back(w);
            }
        }
        return result;
    }

private:
    std::unordered_set<std::string> stopwords;

    static std::string to_lowercase(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return s;
    }

    static std::string remove_punctuation(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
            return std::ispunct(c) ? ' ' : c;
        });
        return s;
    }

    static std::vector<std::string> split_into_words(const std::string& s) {
        std::vector<std::string> words;
        std::stringstream ss(s);
        std::string word;
        while (ss >> word) {
            words.push_back(word);
        }
        return words;
    }
};


//Matheus
class indexer{

    void lerArquivos(); // catalogar arquivo por arquivo 
    void processarTexto(); //realizar a normalização do texto dentro do arquivo.
    int getId(); // pegar o id do index
    void saveOnHash(); //salvar o arquivo ja tratado e salva-lo na hash.

};

class serializer{
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