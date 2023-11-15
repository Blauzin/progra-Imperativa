#include "lista.h"

#define MAXNome 100

FILE *abrirArquivoTexto(const char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL) {
    fprintf(stderr, "Não foi possível abrir o arquivo.\n");
  }
  return arquivo;
}

void lerDadosPessoas(FILE *arquivo, Pessoa **cabeca) {
  char nome[50], cpf[15], dataNascimento[11];
  while (fscanf(arquivo, " %49[^;];%14[^;];%10[^\n]", nome, cpf,
                dataNascimento) == 3) {
    Pessoa *novaPessoa = criarPessoa(nome, cpf, dataNascimento);
    if (novaPessoa) {
      novaPessoa->prox = *cabeca;
      *cabeca = novaPessoa;
    }
  }
}

void escreverDadosBinario(Pessoa *cabeca) {
  ordenarPorCPF(&cabeca);

  FILE *arquivo = fopen("dados.bin", "wb");
  if (arquivo == NULL) {
    fprintf(stderr, "Não foi possível abrir o arquivo binário.\n");
    return;
  }
  Pessoa *atual = cabeca;
  while (atual != NULL) {
    fwrite(atual, sizeof(Pessoa), 1, arquivo);
    atual = atual->prox;
  }
  fclose(arquivo);
}

void liberarMemoria(Pessoa *cabeca) {
  Pessoa *atual = cabeca;
  while (atual != NULL) {
    Pessoa *prox = atual->prox;
    free(atual);
    atual = prox;
  }
}

int processarDados() {
  char nomeArquivo[MAXNome];
  printf("Digite o nome do arquivo a ser aberto:\n");
  fgets(nomeArquivo, MAXNome, stdin);
  nomeArquivo[strcspn(nomeArquivo, "\n")] = 0;

  FILE *arquivo = abrirArquivoTexto(nomeArquivo);
  if (arquivo == NULL) {
    return 1;
  }

  Pessoa *cabeca = NULL;
  lerDadosPessoas(arquivo, &cabeca);
  fclose(arquivo);

  escreverDadosBinario(cabeca);
  liberarMemoria(cabeca);

  printf("Dados gravados com sucesso no arquivo binário.\n");
  return 0;
}
