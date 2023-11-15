#include "lista.h"
#include <stdlib.h>
#include <string.h>

void ordenarPorCPF(Pessoa **cabeca) {
  Pessoa *sorted = NULL;
  Pessoa *current = *cabeca;
  while (current != NULL) {
    Pessoa *next = current->prox;
    Pessoa *prev = NULL;

    for (Pessoa *it = sorted; it != NULL && strcmp(current->cpf, it->cpf) > 0;
         prev = it, it = it->prox)
      ;

    if (prev == NULL) {
      current->prox = sorted;
      sorted = current;
    } else {
      current->prox = prev->prox;
      prev->prox = current;
    }

    current = next;
  }
  *cabeca = sorted;
}

Pessoa *criarPessoa(const char *nome, const char *cpf,
                    const char *dataNascimento) {
  Pessoa *novaPessoa = (Pessoa *)malloc(sizeof(Pessoa));
  if (novaPessoa != NULL) {
    strcpy(novaPessoa->nome, nome);
    strcpy(novaPessoa->cpf, cpf);
    strcpy(novaPessoa->dataNascimento, dataNascimento);
    novaPessoa->prox = NULL;
  }
  return novaPessoa;
}

void liberarLista(Pessoa *cabeca) {
  Pessoa *atual = cabeca;
  while (atual != NULL) {
    Pessoa *prox = atual->prox;
    free(atual);
    atual = prox;
  }
}

void adicionarPessoaInicio(Pessoa **cabeca, Pessoa *novaPessoa) {
  if (novaPessoa) {
    novaPessoa->prox = *cabeca;
    *cabeca = novaPessoa;
  }
}
