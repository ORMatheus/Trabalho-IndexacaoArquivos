#include "index.h"

//construtor do textProcessor :le o arquivo stopwords primeiro e insere no conjuto 

TextProcessor::TextProcessor(const string& stopwordsFile) {
    std::ifstream arq(stopwordsFile);
    string palavra;

    while (std::getline(arq, palavra)) {
        stopwords.insert(palavra);
    }
}

//converter a string inteira para minuscula
string TextProcessor::minuscula(const string& s) {
    string out = s;
    for (char& c : out) {
        c = std::tolower(c);
    }
    return out;
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

// Processa uma linha completa: limpa, divide e remove stopwords
vector<string> TextProcessor::processarLinha(const string& linha) {
    string limpa = removerPontuacao(minuscula(linha));
    vector<string> palavras = separarPalavras(limpa);

    vector<string> resultado;

    // Remove stopwords
    for (const string& p : palavras) {
        if (stopwords.count(p) == 0) {
            resultado.push_back(p);
        }
    }
    return resultado;
}

//indexer
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
void InvertedIndex::construir(const Indexer& idx) {
    for (const auto& par : idx.palavrasPorId) {
        int id = par.first;

        // "par.second" é o vector de palavras do arquivo
        for (const string& termo : par.second) {
            indice[termo][id]++;  // soma 1 à frequência
        }
    }

    std::cout << "Índice invertido construído.\n";
}

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
//  SERIALIZADOR

// Escreve string em binário
void Serializer::writeString(std::ofstream& out, const string& s) {
    size_t len = s.size();
    out.write((char*)&len, sizeof(len));
    out.write(s.c_str(), len);
}

// Lê string em binário
string Serializer::readString(std::ifstream& in) {
    size_t len;
    in.read((char*)&len, sizeof(len));

    string s(len, '\0');
    in.read(&s[0], len);

    return s;
}

// Salva todo o conteúdo do Indexer em arquivo binário
void Serializer::salvar(const Indexer& idx, const string& nomeArq) {
    std::ofstream out(nomeArq, std::ios::binary);

    // 1) Salva nomeParaId
    size_t size1 = idx.nomeParaId.size();
    out.write((char*)&size1, sizeof(size1));

    for (const auto& par : idx.nomeParaId) {
        writeString(out, par.first);
        out.write((char*)&par.second, sizeof(int));
    }

    // 2) Salva palavrasPorId
    size_t size2 = idx.palavrasPorId.size();
    out.write((char*)&size2, sizeof(size2));

    for (const auto& par : idx.palavrasPorId) {
        out.write((char*)&par.first, sizeof(int));

        size_t qtd = par.second.size();
        out.write((char*)&qtd, sizeof(qtd));

        for (const string& p : par.second) {
            writeString(out, p);
        }
    }
}

// Carrega o Indexer salvo anteriormente
void Serializer::carregar(Indexer& idx, const string& nomeArq) {
    std::ifstream in(nomeArq, std::ios::binary);

    if (!in.is_open()) {
        std::cout << "Nenhum índice encontrado.\n";
        return;
    }

    idx.nomeParaId.clear();
    idx.palavrasPorId.clear();

    // 1) Lê nomeParaId
    size_t size1;
    in.read((char*)&size1, sizeof(size1));

    for (size_t i = 0; i < size1; i++) {
        string nome = readString(in);
        int id;
        in.read((char*)&id, sizeof(int));
        idx.nomeParaId[nome] = id;
    }

    // 2) Lê palavrasPorId
    size_t size2;
    in.read((char*)&size2, sizeof(size2));

    for (size_t i = 0; i < size2; i++) {
        int id;
        in.read((char*)&id, sizeof(id));

        size_t qtd;
        in.read((char*)&qtd, sizeof(qtd));

        vector<string> lista;
        for (size_t j = 0; j < qtd; j++) {
            lista.push_back(readString(in));
        }

        idx.palavrasPorId[id] = lista;
    }
}