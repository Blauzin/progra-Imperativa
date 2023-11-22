#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

// Função para abrir um arquivo binário para leitura.
FILE *abrirArquivoBinario(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo binário.\n");
    }
    return arquivo;
}

// Função para ler dados do arquivo binário e adicionar à lista encadeada.
void lerDadosBinario(FILE *arquivo, Pessoa **cabeca) {
    Pessoa temp;
    while (fread(&temp, sizeof(Pessoa), 1, arquivo)) {
        Pessoa *novaPessoa = criarPessoa(temp.nome, temp.cpf, temp.dataNascimento);
        if (novaPessoa) {
            novaPessoa->prox = *cabeca;
            *cabeca = novaPessoa;
        }
    }
}

// Função para escrever os dados da lista encadeada em um arquivo de texto.
void escreverDadosTexto(Pessoa *cabeca, const char *nomeArquivoTexto) {
    FILE *arquivo = fopen(nomeArquivoTexto, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo de texto.\n");
        return;
    }
    Pessoa *atual = cabeca;
    while (atual != NULL) {
        fprintf(arquivo, "%s;%s;%s\n", atual->nome, atual->cpf, atual->dataNascimento);
        atual = atual->prox;
    }
    fclose(arquivo);
}

// Função principal para processar os dados.
int exportarDados() {

    char nomeArquivo[100];

    printf("Digite o nome do arquivo binrio para ler: ");
    scanf("%s", nomeArquivo);
    FILE *arquivoBinario = abrirArquivoBinario(nomeArquivo);
    if (arquivoBinario == NULL) {
        return 1;
    }

    Pessoa *cabeca = NULL;
    lerDadosBinario(arquivoBinario, &cabeca);
    fclose(arquivoBinario);

    printf("Digite o nome do arquivo para salvar: ");
      scanf("%s", nomeArquivo);
    
    escreverDadosTexto(cabeca, nomeArquivo);

    printf("Dados exportados com sucesso para o arquivo de texto.\n");
    return 0;
}
