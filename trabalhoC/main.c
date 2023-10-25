#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int codigo_produto;
  double preco;
  char descricao[50];
} Produto;

typedef struct {
  int codigo;
  char nome[50];
} Vendedor;

typedef struct {
  int codigoVendedor;
  int codigoProduto;
  int unidadesVendidas;
} Venda;

int main() {

  FILE *vendasArquivo =
      fopen("vendas.txt", "r"); // abrir o arquivo de vendas no modo de leitura
  if (vendasArquivo == NULL) {
    printf("Erro ao abrir o arquivo de vendas.\n");
    return 1;
  }

  int numVendas;
  fscanf(vendasArquivo, "%d", &numVendas);

  Venda *vendas = malloc(numVendas * sizeof(Venda));

  if (vendas == NULL) {
    printf("Erro ao alocar memória para as vendas.\n");
    return 1;
  }

  for (int i = 0; i < numVendas; i++) {
    fscanf(vendasArquivo, "%d %d %d", &vendas[i].codigoVendedor,
           &vendas[i].codigoProduto, &vendas[i].unidadesVendidas);
  }

  fclose(vendasArquivo);

  // Abrir e ler o arquivo de produtos
  FILE *produtosFile = fopen("produtos.txt", "r");
  if (produtosFile == NULL) {
    printf("Erro ao abrir o arquivo de produtos.\n");
    return 1;
  }

  int numProdutos;
  fscanf(produtosFile, "%d", &numProdutos);

  Produto *produtos = malloc(numProdutos * sizeof(Produto));
  if (produtos == NULL) {
    printf("Erro ao alocar memória para os produtos.\n");
    return 1;
  }

  for (int i = 0; i < numProdutos; i++) {
    fscanf(produtosFile, "%d %lf %s", &produtos[i].codigo_produto,
           &produtos[i].preco, produtos[i].descricao);
  }

  fclose(produtosFile);

  // Abrir e ler o arquivo de vendedores
  FILE *vendedoresFile = fopen("vendedores.txt", "r");
  if (vendedoresFile == NULL) {
    printf("Erro ao abrir o arquivo de vendedores.\n");
    return 1;
  }

  int numVendedores;
  fscanf(vendedoresFile, "%d", &numVendedores);

  Vendedor *vendedores = malloc(numVendedores * sizeof(Vendedor));
  if (vendedores == NULL) {
    printf("Erro ao alocar memória para os vendedores.\n");
    return 1;
  }

  for (int i = 0; i < numVendedores; i++) {
    fscanf(vendedoresFile, "%d %s", &vendedores[i].codigo, vendedores[i].nome);
  }

  fclose(vendedoresFile);

  // Calcular os totais
  double totalGeral = 0;
  double *totalPorProduto = calloc(numProdutos, sizeof(double));
  double *totalPorVendedor = calloc(numVendedores, sizeof(double));

  for (int i = 0; i < numVendas; i++) {
    int codigoProduto = vendas[i].codigoProduto;
    int codigoVendedor = vendas[i].codigoVendedor;
    int unidadesVendidas = vendas[i].unidadesVendidas;

    totalGeral += produtos[codigoProduto - 1].preco * unidadesVendidas;
    totalPorProduto[codigoProduto - 1] +=
        produtos[codigoProduto - 1].preco * unidadesVendidas;
    totalPorVendedor[codigoVendedor - 1] +=
        produtos[codigoProduto - 1].preco * unidadesVendidas;
  }

  // Gravar os resultados em totais.txt
  FILE *totaisFile = fopen("totais.txt", "w");
  if (totaisFile == NULL) {
    printf("Erro ao criar o arquivo de totais.\n");
    return 1;
  }

  fprintf(totaisFile, "Total geral de vendas: %.2lf\n\n", totalGeral);
  fprintf(totaisFile, "Total vendido por produto:\n");
  for (int i = 0; i < numProdutos; i++) {
    fprintf(totaisFile, "Produto %d: %.2lf\n", produtos[i].codigo_produto,
            totalPorProduto[i]);
  }
  fprintf(totaisFile, "\nTotal vendido por vendedor:\n");
  for (int i = 0; i < numVendedores; i++) {
    fprintf(totaisFile, "Vendedor %d (%s): %.2lf\n", vendedores[i].codigo,
            vendedores[i].nome, totalPorVendedor[i]);
  }

  fclose(totaisFile);

  // Liberar a memória alocada
  free(vendas);
  free(produtos);
  free(vendedores);
  free(totalPorProduto);
  free(totalPorVendedor);

  return 0;
}
