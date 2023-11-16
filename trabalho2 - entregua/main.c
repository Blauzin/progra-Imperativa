#include "lista.h"
#include "editor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

   if (argc != 3) {
    printf("Uso: %s <arquivo_entrada> <arquivo_bin>\n", argv[0]);
    return 1;
  }

  int resultado = processarDados(argc, argv);

  if (resultado == 0) {
    printf("Processamento concluído com sucesso.\n");


    menuPrincipal();

    //exportador 
    exportarDados(argc, argv);
  } else {

    printf("Ocorreu um erro durante o processamento.\n");
  }

  return resultado;
}
