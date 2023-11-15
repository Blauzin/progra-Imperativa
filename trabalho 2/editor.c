#include "editor.h"
#include "lista.h"

// Funções principais do editor
int inicializarEditorData(EditorData *editorData) {
  editorData->cabeca = NULL;
  return 1;
}

void liberarEditorData(EditorData *editorData) {
  liberarLista(editorData->cabeca);
  editorData->cabeca = NULL;
}

int lerArquivoBinario(EditorData *editorData, const char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "rb");
  if (arquivo == NULL) {
    return 0;
  }

  liberarEditorData(editorData);

  Pessoa pessoaTemp;
  while (fread(&pessoaTemp, sizeof(Pessoa), 1, arquivo)) {
    Pessoa *novaPessoa =
        criarPessoa(pessoaTemp.nome, pessoaTemp.cpf, pessoaTemp.dataNascimento);
    adicionarPessoaInicio(&(editorData->cabeca), novaPessoa);
  }

  fclose(arquivo);
  return 1;
}

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

void formatarCPFParaExibicao(const char *cpf, char *cpfFormatado) {
  sprintf(cpfFormatado, "%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3, cpf + 6, cpf + 9);
}

void imprimirDados(EditorData *editorData) {
  Pessoa *atual = editorData->cabeca;
  while (atual != NULL) {
    char cpfFormatado[15];
    formatarCPFParaExibicao(atual->cpf, cpfFormatado);

    printf("Nome: %s\n", atual->nome);
    printf("CPF: %s\n", cpfFormatado);
    printf("Data de Nascimento: %s\n", atual->dataNascimento);
    printf("--------\n");
    atual = atual->prox;
  }
}

void adicionarPessoa(EditorData *editorData, const char *nome, const char *cpf,
                     const char *dataNascimento) {
  Pessoa *novaPessoa = criarPessoa(nome, cpf, dataNascimento);
  adicionarPessoaInicio(&(editorData->cabeca), novaPessoa);
}

Pessoa *encontrarPessoaAnteriorPorCPF(Pessoa *cabeca, const char *cpf) {
  Pessoa *atual = cabeca;
  Pessoa *anterior = NULL;
  while (atual != NULL && strcmp(atual->cpf, cpf) != 0) {
    anterior = atual;
    atual = atual->prox;
  }
  return anterior;
}

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

void menuPrincipal() {
  EditorData editorData;
  inicializarEditorData(&editorData);

  int opcao;
  char nomeArquivo[100];
  char nome[100], cpf[15], dataNascimento[11];

  do {
    printf("\nMenu Principal\n");
    printf("1. Ler Arquivo Binário\n");
    printf("2. Salvar Arquivo Binário\n");
    printf("3. Adicionar Pessoa\n");
    printf("4. Remover Pessoa\n");
    printf("5. Imprimir Dados\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("Digite o nome do arquivo para ler: ");
      scanf("%s", nomeArquivo);
      lerArquivoBinario(&editorData, nomeArquivo);
      break;
    case 2:
      printf("Digite o nome do arquivo para salvar: ");
      scanf("%s", nomeArquivo);
      salvarArquivoBinario(&editorData, nomeArquivo);
      break;
    case 3:
      printf("Digite o nome: ");
      scanf("%s", nome);
      printf("Digite o CPF: ");
      scanf("%s", cpf);
      printf("Digite a data de nascimento (DD/MM/AAAA): ");
      scanf("%s", dataNascimento);
      adicionarPessoa(&editorData, nome, cpf, dataNascimento);
      break;
    case 4:
      printf("Digite o CPF da pessoa a remover: ");
      scanf("%s", cpf);
      removerPessoa(&editorData, cpf);
      break;
    case 5:
      imprimirDados(&editorData);
      break;
    case 6:
      liberarEditorData(&editorData);
      printf("Saindo...\n");
      break;
    default:
      printf("Opção inválida!\n");
    }
  } while (opcao != 6);
}
#include "editor.h"
#include "lista.h"

// Funções principais do editor
int inicializarEditorData(EditorData *editorData) {
  editorData->cabeca = NULL;
  return 1;
}

void liberarEditorData(EditorData *editorData) {
  liberarLista(editorData->cabeca);
  editorData->cabeca = NULL;
}

int lerArquivoBinario(EditorData *editorData, const char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "rb");
  if (arquivo == NULL) {
    return 0;
  }

  liberarEditorData(editorData);

  Pessoa pessoaTemp;
  while (fread(&pessoaTemp, sizeof(Pessoa), 1, arquivo)) {
    Pessoa *novaPessoa =
        criarPessoa(pessoaTemp.nome, pessoaTemp.cpf, pessoaTemp.dataNascimento);
    adicionarPessoaInicio(&(editorData->cabeca), novaPessoa);
  }

  fclose(arquivo);
  return 1;
}

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

void formatarCPFParaExibicao(const char *cpf, char *cpfFormatado) {
  sprintf(cpfFormatado, "%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3, cpf + 6, cpf + 9);
}

void imprimirDados(EditorData *editorData) {
  Pessoa *atual = editorData->cabeca;
  while (atual != NULL) {
    char cpfFormatado[15];
    formatarCPFParaExibicao(atual->cpf, cpfFormatado);

    printf("Nome: %s\n", atual->nome);
    printf("CPF: %s\n", cpfFormatado);
    printf("Data de Nascimento: %s\n", atual->dataNascimento);
    printf("--------\n");
    atual = atual->prox;
  }
}

void adicionarPessoa(EditorData *editorData, const char *nome, const char *cpf,
                     const char *dataNascimento) {
  Pessoa *novaPessoa = criarPessoa(nome, cpf, dataNascimento);
  adicionarPessoaInicio(&(editorData->cabeca), novaPessoa);
}

Pessoa *encontrarPessoaAnteriorPorCPF(Pessoa *cabeca, const char *cpf) {
  Pessoa *atual = cabeca;
  Pessoa *anterior = NULL;
  while (atual != NULL && strcmp(atual->cpf, cpf) != 0) {
    anterior = atual;
    atual = atual->prox;
  }
  return anterior;
}

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

void menuPrincipal() {
  EditorData editorData;
  inicializarEditorData(&editorData);

  int opcao;
  char nomeArquivo[100];
  char nome[100], cpf[15], dataNascimento[11];

  do {
    printf("\nMenu Principal\n");
    printf("1. Ler Arquivo Binário\n");
    printf("2. Salvar Arquivo Binário\n");
    printf("3. Adicionar Pessoa\n");
    printf("4. Remover Pessoa\n");
    printf("5. Imprimir Dados\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("Digite o nome do arquivo para ler: ");
      scanf("%s", nomeArquivo);
      lerArquivoBinario(&editorData, nomeArquivo);
      break;
    case 2:
      printf("Digite o nome do arquivo para salvar: ");
      scanf("%s", nomeArquivo);
      salvarArquivoBinario(&editorData, nomeArquivo);
      break;
    case 3:
      printf("Digite o nome: ");
      scanf("%s", nome);
      printf("Digite o CPF: ");
      scanf("%s", cpf);
      printf("Digite a data de nascimento (DD/MM/AAAA): ");
      scanf("%s", dataNascimento);
      adicionarPessoa(&editorData, nome, cpf, dataNascimento);
      break;
    case 4:
      printf("Digite o CPF da pessoa a remover: ");
      scanf("%s", cpf);
      removerPessoa(&editorData, cpf);
      break;
    case 5:
      imprimirDados(&editorData);
      break;
    case 6:
      liberarEditorData(&editorData);
      printf("Saindo...\n");
      break;
    default:
      printf("Opção inválida!\n");
    }
  } while (opcao != 6);
}
