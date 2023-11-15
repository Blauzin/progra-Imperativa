#include "lista.h"
#include "editor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int resultado = processarDados();

  if (resultado == 0) {
    printf("Processamento concluído com sucesso.\n");
    menuPrincipal();
  } else {
    printf("Ocorreu um erro durante o processamento.\n");
  }

  return resultado;
}
