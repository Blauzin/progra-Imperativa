#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>

typedef struct Pessoa {
  char nome[100];
  char cpf[15];
  char dataNascimento[11];
  struct Pessoa *prox;
} Pessoa;

// Declarações de funções
Pessoa *criarPessoa(const char *nome, const char *cpf,
                    const char *dataNascimento);
void liberarLista(Pessoa *cabeca);
void adicionarPessoaInicio(Pessoa **cabeca, Pessoa *novaPessoa);
int processarDados();
void ordenarPorCPF(Pessoa **cabeca);

#endif // LISTA_H
