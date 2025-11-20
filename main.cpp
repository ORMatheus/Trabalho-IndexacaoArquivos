#include "index.h"      // ou o nome do seu arquivo .h onde está a classe TextProcessor
#include <iostream>
#include <fstream>
// #include <filesystem>
#include <string>

int main() {
    // 1. Cria o TextProcessor (vai tentar carregar stopwords.txt)
    TextProcessor tp("stopwords.txt");

    // 2. Texto de teste (pode colar direto do exemplo do PDF)
    std::string texto = 
        "O gato está comendo no telhado!!!\n"
        "O cachorro está comendo no quintal.\n"
        "Está um dia lindo, né?";

    std::cout << "=== TEXTO ORIGINAL ===\n";
    std::cout << texto << "\n\n";

    // 3. Processa o texto
    std::vector<std::string> palavras = tp.process(texto);

    // 4. Mostra o resultado
    std::cout << "=== PALAVRAS PROCESSADAS (sem stop words e limpas) ===\n";
    if (palavras.empty()) {
        std::cout << "(nenhuma palavra encontrada - talvez stopwords.txt esteja faltando?)\n";
    } else {
        for (const auto& p : palavras) {
            std::cout << p << "\n";
        }
    }

    // 5. Teste extra: lendo um arquivo .txt real (opcional)
    std::cout << "\n\n=== TESTANDO COM ARQUIVO REAL ===\n";
    std::ifstream arquivo("doc1.txt");  // cria um doc1.txt na pasta do projeto pra testar
    if (arquivo) {
        std::string conteudo((std::istreambuf_iterator<char>(arquivo)),
                              std::istreambuf_iterator<char>());
        auto palavras_arquivo = tp.process(conteudo);
        std::cout << "Palavras encontradas em doc1.txt:\n";
        for (const auto& p : palavras_arquivo) {
            std::cout << p << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "Crie um arquivo 'doc1.txt' na mesma pasta pra testar leitura de arquivo.\n";
    }

    return 0;
}