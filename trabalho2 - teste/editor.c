#include "editor.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Inicializa os dados do editor, definindo a cabeça da lista como NULL.
int inicializarEditorData(EditorData *editorData) {
  editorData->cabeca = NULL;
  return 1;
}

// Libera todos os dados associados ao editor, incluindo a lista encadeada.
void liberarEditorData(EditorData *editorData) {
  liberarLista(editorData->cabeca);
  editorData->cabeca = NULL;
}

// Adiciona uma nova pessoa ao final da lista encadeada.
void adicionarPessoaFinal(Pessoa **cabeca, Pessoa *novaPessoa) {
  if (*cabeca == NULL) {
    *cabeca = novaPessoa;
  } else {
    Pessoa *atual = *cabeca;
    while (atual->prox != NULL) {
      atual = atual->prox;
    }
    atual->prox = novaPessoa;
  }
}

// Lê os dados de um arquivo binário e os carrega na lista encadeada.
int lerArquivoBinario(EditorData *editorData, const char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "rb");
  if (arquivo == NULL) {
    return 0;
  }

  liberarEditorData(editorData);

  Pessoa pessoaTemp;
  while (fread(&pessoaTemp, sizeof(Pessoa), 1, arquivo)) {
    Pessoa *novaPessoa = criarPessoa(pessoaTemp.nome, pessoaTemp.cpf, pessoaTemp.dataNascimento);
    adicionarPessoaFinal(&(editorData->cabeca), novaPessoa);
  }

  fclose(arquivo);
  return 1;
}

// Salva os dados da lista encadeada em um arquivo binário.
int salvarArquivoBinario(EditorData *editorData, const char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "wb");
  if (arquivo == NULL) {
    return 0;
  }

  Pessoa *atual = editorData->cabeca;
  while (atual != NULL) {
    fwrite(atual, sizeof(Pessoa), 1, arquivo);
    atual = atual->prox;
  }

  fclose(arquivo);
  return 1;
}

// Formata o CPF para o formato xxx.xxx.xxx-xx.
void formatarCPF(const char *cpf, char *cpfFormatado) {
  sprintf(cpfFormatado, "%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3, cpf + 6, cpf + 9);
}

// Imprime todos os dados da lista encadeada.
void imprimirDados(EditorData *editorData) {
  Pessoa *atual = editorData->cabeca;
  while (atual != NULL) {
    char cpfFormatado[15];
    formatarCPF(atual->cpf, cpfFormatado);

    printf("Nome: %s\n", atual->nome);
    printf("CPF: %s\n", cpfFormatado);
    printf("Data de Nascimento: %s\n", atual->dataNascimento);
    printf("--------\n");
    atual = atual->prox;
  }
}

// Adiciona uma nova pessoa na lista encadeada de forma ordenada com base no CPF.
void adicionarPessoaOrdenado(EditorData *editorData, const char *nome, const char *cpf, const char *dataNascimento) {
  Pessoa *novaPessoa = criarPessoa(nome, cpf, dataNascimento);
  if (!novaPessoa)
    return;

  if (editorData->cabeca == NULL || strcmp(editorData->cabeca->cpf, novaPessoa->cpf) > 0) {
    novaPessoa->prox = editorData->cabeca;
    editorData->cabeca = novaPessoa;
  } else {
    Pessoa *atual = editorData->cabeca;
    while (atual->prox != NULL && strcmp(atual->prox->cpf, novaPessoa->cpf) < 0) {
      atual = atual->prox;
    }
    novaPessoa->prox = atual->prox;
    atual->prox = novaPessoa;
  }
}

// Encontra a pessoa anterior com base no CPF na lista encadeada.
Pessoa *encontrarPessoaAnteriorPorCPF(Pessoa *cabeca, const char *cpf) {
  Pessoa *atual = cabeca;
  Pessoa *anterior = NULL;
  while (atual != NULL && strcmp(atual->cpf, cpf) != 0) {
    anterior = atual;
    atual = atual->prox;
  }
  return anterior;
}

// Remove uma pessoa da lista encadeada com base no CPF.
int removerPessoa(EditorData *editorData, const char *cpf) {
  if (editorData->cabeca == NULL)
    return 0;

  if (strcmp(editorData->cabeca->cpf, cpf) == 0) {
    Pessoa *remover = editorData->cabeca;
    editorData->cabeca = editorData->cabeca->prox;
    free(remover);
    return 1;
  }

  Pessoa *anterior = encontrarPessoaAnteriorPorCPF(editorData->cabeca, cpf);
  if (anterior == NULL || anterior->prox == NULL)
    return 0;

  Pessoa *remover = anterior->prox;
  anterior->prox = remover->prox;
  free(remover);
  return 1;
}

// Busca uma pessoa na lista encadeada com base no CPF.
Pessoa *buscarPorCpf(Pessoa *cabeca, const char *cpf) {
  if (cabeca == NULL) {
    return NULL;
  } else if (strcmp(cabeca->cpf, cpf) == 0) {
    return cabeca;
  } else {
    return buscarPorCpf(cabeca->prox, cpf);
  }
}

// Menu principal do editor que permite interação com o usuário.
void menuPrincipal(int argc, char *argv[]) {

  const char *nomeArquivoLeitura = argv[2];
  const char *nomeArquivoEscrita = argv[2];


  EditorData editorData;
  inicializarEditorData(&editorData);

  lerArquivoBinario(&editorData, nomeArquivoLeitura);

  int opcao;
  char nome[100], cpf[15], dataNascimento[11];

  do {
    // Exibe as opções do menu.
    printf("\nMenu Principal\n");
    printf("1. Ler Arquivo Binário\n");
    printf("2. Salvar Arquivo Binário\n");
    printf("3. Adicionar Pessoa\n");
    printf("4. Remover Pessoa\n");
    printf("5. Imprimir Dados\n");
    printf("6. Pesquisar por CPF\n");
    printf("7. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    // Processa a opção escolhida pelo usuário.
    switch (opcao) {
    case 1:
      // Opção para ler dados de um arquivo binário.
      printf("Deprecated");
      break;
    case 2:
      // Opção para salvar dados em um arquivo binário.
      printf("Arquivo Salvo.");
      salvarArquivoBinario(&editorData, nomeArquivoEscrita);
      break;
    case 3:
      // Opção para adicionar uma nova pessoa na lista.
      printf("Digite o nome: ");
      scanf("%s", nome);
      printf("Digite o CPF: ");
      scanf("%s", cpf);
      printf("Digite a data de nascimento (DD/MM/AAAA): ");
      scanf("%s", dataNascimento);
      adicionarPessoaOrdenado(&editorData, nome, cpf, dataNascimento);
      break;
    case 4:
      // Opção para remover uma pessoa da lista com base no CPF.
      printf("Digite o CPF da pessoa a remover: ");
      scanf("%s", cpf);
      removerPessoa(&editorData, cpf);
      break;
    case 5:
      // Opção para imprimir todos os dados da lista.
      imprimirDados(&editorData);
      break;
    case 6:
      // Opção para pesquisar uma pessoa na lista por CPF.
      printf("Digite o CPF para buscar: ");
      scanf("%s", cpf);
      Pessoa *pessoaEncontrada = buscarPorCpf(editorData.cabeca, cpf);
      if (pessoaEncontrada != NULL) {
        printf("Nome: %s Data de Nascimento: %s\n", pessoaEncontrada->nome,
               pessoaEncontrada->dataNascimento);
      } else {
        printf("CPF não encontrado.\n");
      }
      break;
    case 7:
      // Opção para sair do programa.
      liberarEditorData(&editorData);
      printf("Saindo...\n");
      break;
    default:
      // Mensagem para opção inválida.
      printf("Opção inválida!\n");
    }
  } while (opcao != 7);  // O loop continua até que a opção de saída seja escolhida.
}
