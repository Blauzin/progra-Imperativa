#include "lista.h"
#include <stdlib.h>
#include <string.h>

#define MAXNome 100

// Função para abrir um arquivo de texto para leitura.
FILE *abrirArquivoTexto(const char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL) {
    // Imprime uma mensagem de erro se não conseguir abrir o arquivo.
    fprintf(stderr, "Não foi possível abrir o arquivo.\n");
  }
  return arquivo;
}

// Função para ler os dados das pessoas de um arquivo e adicionar à lista
// encadeada.
void lerDadosPessoas(FILE *arquivo, Pessoa **cabeca) {
  char nome[100], cpf[15], dataNascimento[11];
  // Lê os dados no formato nome;cpf;data de nascimento.
  while (fscanf(arquivo, " %99[^;];%14[^;];%10[^\n]", nome, cpf,
                dataNascimento) == 3) {
    // Cria uma nova pessoa e adiciona ao início da lista encadeada.
    Pessoa *novaPessoa = criarPessoa(nome, cpf, dataNascimento);
    if (novaPessoa) {
      novaPessoa->prox = *cabeca;
      *cabeca = novaPessoa;
    }
  }
}

// Função para escrever os dados da lista encadeada em um arquivo binário.
void escreverDadosBinario(Pessoa *cabeca, const char *nomeArquivoBinario) {
  // Ordena a lista por CPF antes de escrever.
  ordenarPorCPF(&cabeca);

  FILE *arquivo = fopen(nomeArquivoBinario, "wb");
  if (arquivo == NULL) {
    // Imprime uma mensagem de erro se não conseguir abrir o arquivo binário.
    fprintf(stderr, "Não foi possível abrir o arquivo binário.\n");
    return;
  }
  Pessoa *atual = cabeca;
  // Escreve cada pessoa da lista no arquivo binário.
  while (atual != NULL) {
    fwrite(atual, sizeof(Pessoa), 1, arquivo);
    atual = atual->prox;
  }
  fclose(arquivo);
}

// Função para liberar a memória alocada pela lista encadeada.
void liberarMemoria(Pessoa *cabeca) {
  Pessoa *atual = cabeca;
  while (atual != NULL) {
    // Libera cada nó da lista e avança para o próximo.
    Pessoa *prox = atual->prox;
    free(atual);
    atual = prox;
  }
}

// Função principal para processar os dados.
int processarDados(int argc, char *argv[]) {

  const char *nomeArquivoTexto = argv[1];
  FILE *arquivoTexto = abrirArquivoTexto(nomeArquivoTexto);

  if (arquivoTexto == NULL) {
    return 1;
  }

  Pessoa *cabeca = NULL;
  lerDadosPessoas(arquivoTexto, &cabeca);
  fclose(arquivoTexto);

  escreverDadosBinario(cabeca, argv[2]);
  liberarMemoria(cabeca);

  printf("Dados gravados com sucesso no arquivo binário.\n");
  return 0;
}
