#ifndef EDITOR_H
#define EDITOR_H

#include "lista.h"

typedef struct {
  Pessoa *pessoas;
  int numPessoas;
  Pessoa *cabeca;
} EditorData;

void menuPrincipal(int argc, char *argv[]);

#endif
