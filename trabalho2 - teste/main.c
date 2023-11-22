#include "lista.h"
#include "editor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {



  int resultado = processarDados(argc, argv);

  if (resultado == 0) {
    printf("Processamento concluído com sucesso.\n");


    menuPrincipal(argc, argv);

    //exportador 
    exportarDados(argc, argv);
  } else {

    printf("Ocorreu um erro durante o processamento.\n");
  }

  return resultado;
}
