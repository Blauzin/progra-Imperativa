#include <stdio.h>

float faturamento[] = {100.50, 200.25, 50.75, 300.00, 150.50, 75.25, 80.00};

int main(){
  
  int numeroItems = sizeof(faturamento) / sizeof(faturamento[0]);
  float faturamentoTotal = 0;
  float menorFaturamento = faturamento[0];
  float maiorFaturamento = faturamento[0];
  for(int i = 0; i < numeroItems; i++ )
  {
    faturamentoTotal = faturamentoTotal +  faturamento[i];

    if (faturamento[i] > maiorFaturamento)
    {
      maiorFaturamento = faturamento[i];
    }
    if (faturamento[i] < menorFaturamento)
    {
      menorFaturamento = faturamento[i];
    }
  }
  float faturamentoMedio = faturamentoTotal / numeroItems;

  printf("Faturamento total: %.2f,\nfaturamento medio: %.2f,\nmenor faturamento: %.2f,\nmaior faturamento: %.2f.", faturamentoTotal, faturamentoMedio, menorFaturamento, maiorFaturamento);

  return 0;

}