#include "index.h"

int main() {

    // Cria indexador
    Indexer indexador;

    // Carrega do disco caso exista
    Serializer::carregar(indexador, "index.bin");

    // Pergunta pasta ao usuário
    std::cout << "Digite a pasta dos arquivos (enter = ./docs): ";
    string pasta;
    std::getline(std::cin, pasta);
    if (pasta.empty()) pasta = "./docs";

    // Lê arquivos da pasta e processa tudo
    indexador.lerPasta(pasta);

    // Salva para não precisar reindexar depois
    Serializer::salvar(indexador, "index.bin");

    // Constrói índice invertido
    InvertedIndex inv;
    inv.construir(indexador);

    // Loop de consultas
    while (true) {
        std::cout << "\nConsulta (ou 'sair'): ";
        string linha;
        std::getline(std::cin, linha);

        if (linha == "sair") break;

        // Normaliza a consulta
        vector<string> termos =
            indexador.processador.processarLinha(linha);

        // Exibe documentos encontrados
        inv.buscar(termos, indexador);
    }

    return 0;
}
