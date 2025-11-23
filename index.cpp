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


Indexer::Indexer()
    : proximoId(1),               // Começa IDs no número 1
      processador("stopwords.txt")   // Carrega stopwords automaticamente
{
}

// Retorna ID do arquivo. Se não existir, cria um novo.
int Indexer::pegarId(const string& nomeArq) {
    if (nomeParaId.count(nomeArq) == 0) {
        nomeParaId[nomeArq] = proximoId++;
    }
    return nomeParaId[nomeArq];
}

// Lê todos os arquivos do diretório
void Indexer::lerPasta(const string& caminhoPasta) {
    for (const auto& item : fs::directory_iterator(caminhoPasta)) {
        if (!item.is_regular_file()) continue;

        string nomeArquivo = item.path().filename().string();
        int id = pegarId(nomeArquivo);

        std::ifstream arquivo(item.path());
        string linha;

        while (std::getline(arquivo, linha)) {
            // Processa cada linha usando TextProcessor
            vector<string> palavras = processador.processarLinha(linha);

            // Adiciona as palavras ao id
            for (const string& p : palavras) {
                palavrasPorId[id].push_back(p);
            }
        }

        std::cout << "Arquivo indexado: " << nomeArquivo << "\n";
    }
}

//  INVERTED INDEX

// Realiza busca simples com soma de frequências
void InvertedIndex::buscar(const vector<string>& termos,
                           const Indexer& idx) {
    unordered_map<int, int> score;

    // Para cada termo digitado pelo usuário
    for (const string& t : termos) {
        if (indice.count(t) == 0) continue;

        // Para cada arquivo onde o termo aparece
        for (const auto& par : indice[t]) {
            score[par.first] += par.second;
        }
    }

    // Exibe os resultados encontrados
    std::cout << "\nResultados da busca:\n";
    for (const auto& par : score) {
        // Par é: (id, score)
        for (const auto& idNome : idx.nomeParaId) {
            if (idNome.second == par.first) {
                std::cout << "- " << idNome.first
                          << " (score: " << par.second << ")\n";
            }
        }
    }
}
