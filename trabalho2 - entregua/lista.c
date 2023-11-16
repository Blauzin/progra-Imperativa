#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Função para ordenar a lista encadeada por CPF.
void ordenarPorCPF(Pessoa **cabeca) {
  Pessoa *sorted = NULL;  // Ponteiro para a lista ordenada.
  Pessoa *current = *cabeca;  // Ponteiro para percorrer a lista original.
  while (current != NULL) {
    Pessoa *next = current->prox;  // Armazena o próximo elemento da lista original.
    Pessoa *prev = NULL;  // Ponteiro para o elemento anterior na lista ordenada.

    // Encontra a posição de inserção na lista ordenada.
    for (Pessoa *it = sorted; it != NULL && strcmp(current->cpf, it->cpf) > 0;
         prev = it, it = it->prox);

    // Insere o elemento na posição correta na lista ordenada.
    if (prev == NULL) {
      current->prox = sorted;
      sorted = current;
    } else {
      current->prox = prev->prox;
      prev->prox = current;
    }

    current = next;  // Move para o próximo elemento na lista original.
  }
  *cabeca = sorted;  // Atualiza a cabeça da lista para apontar para a lista ordenada.
}

// Função para criar uma nova pessoa.
Pessoa *criarPessoa(const char *nome, const char *cpf, const char *dataNascimento) {
  Pessoa *novaPessoa = (Pessoa *)malloc(sizeof(Pessoa));  // Aloca memória para a nova pessoa.
  if (novaPessoa != NULL) {
    // Copia os dados para a nova pessoa.
    strcpy(novaPessoa->nome, nome);
    strcpy(novaPessoa->cpf, cpf);
    strcpy(novaPessoa->dataNascimento, dataNascimento);
    novaPessoa->prox = NULL;  // Define o próximo elemento como NULL.
  }
  return novaPessoa;  // Retorna a nova pessoa criada.
}

// Função para liberar a memória alocada pela lista encadeada.
void liberarLista(Pessoa *cabeca) {
  Pessoa *atual = cabeca;  // Ponteiro para percorrer a lista.
  while (atual != NULL) {
    Pessoa *prox = atual->prox;  // Armazena o próximo elemento.
    free(atual);  // Libera a memória do elemento atual.
    atual = prox;  // Move para o próximo elemento.
  }
}

// Função para adicionar uma pessoa no início da lista.
void adicionarPessoaInicio(Pessoa **cabeca, Pessoa *novaPessoa) {
  if (novaPessoa) {
    novaPessoa->prox = *cabeca;  // Define o próximo da nova pessoa como a cabeça atual da lista.
    *cabeca = novaPessoa;  // Atualiza a cabeça da lista para a nova pessoa.
  }
}

// Função para liberar a memória alocada pela lista encadeada.
void liberarMemoria(Pessoa *cabeca) {
  Pessoa *atual = cabeca;  // Ponteiro para percorrer a lista.
  while (atual != NULL) {
    Pessoa *prox = atual->prox;  // Armazena o próximo elemento.
    free(atual);  // Libera a memória do elemento atual.
    atual = prox;  // Move para o próximo elemento.
  }
}
