#include <iostream>
#include "index.h"

using namespace std;

int main() {
    Indexer indexer;
    Serializer serializer;

    // 1. Tenta carregar dados antigos (Persistência)
    serializer.loadIndex(indexer, "indice.dat");

    // 2. Processa novos arquivos
    // ATENÇÃO: Certifique-se de que esta pasta existe!
    string pastaAlvo = "./arquivos_teste";
    
    // Verifica antes de chamar para evitar crash se a pasta não existir
    if (fs::exists(pastaAlvo)) {
        indexer.lerArquivos(pastaAlvo);
    } else {
        cout << "Aviso: Crie a pasta '" << pastaAlvo << "' e coloque arquivos .txt nela." << endl;
    }

    // 3. Mostra o que temos na memória
    indexer.imprimirEstado();

    // 4. Salva tudo no disco antes de encerrar
    serializer.saveIndex(indexer, "indice.dat");

    return 0;
}
