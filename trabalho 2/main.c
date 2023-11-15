#include "lista.h"
#include "editor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Verifica se os argumentos necessários foram fornecidos
  if (argc != 4) {
    printf("Uso: %s <arquivo_entrada> <arquivo_bin> <arquivo_final>\n", argv[0]);
    return 1;
  }

  // Chama a função do gerador com os argumentos fornecidos
  int resultado = processarDados(argc, argv);

  if (resultado == 0) {
    printf("Processamento concluído com sucesso.\n");

    // Abre o editor
    menuPrincipal(argc, argv);

    // Chama as funções do exportador (placeholders por enquanto)
    // exportarDados(); // Substitua por funções reais do exportador conforme necessário

    printf("Exportação concluída com sucesso.\n");
  } else {
    printf("Ocorreu um erro durante o processamento.\n");
  }

  return resultado;
}
