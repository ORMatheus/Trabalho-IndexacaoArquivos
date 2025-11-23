#include "index.h"

//construtor do textProcessor :le o arquivo stopwords primeiro e insere no conjuto 

TextProcessor::TextProcessor(const string& stopwordsFile){
    std::ifstream arq(stopwordsFile); //pega a lista de palavras que estão em stop stods
    string palavra;

    while(std::getline(arq,palavra)){
        stopwords.insert(palavra);
    }
}


//converter a string inteira para minuscula
string TextProcessor::minuscula(const string& s){
    string out=s;
    for(char &c: out ){
        c=std::tolower(c);
    }
    return out ;
}

//trocar qualquer pontuação por um espaço

string TextProcessor::removerPontuacao(const string& s) {
    string out = s;
    for (char& c : out) {
        if (std::ispunct(c)) c = ' ';
    }
    return out;
}

//separa a frase em palavras usando stringstream

vector<string> TextProcessor::separarPalavras(const string& s) {
    vector<string> result;
    std::stringstream ss(s);
    string palavra;

    while (ss >> palavra) {
        result.push_back(palavra);
    }
    return result;
}



