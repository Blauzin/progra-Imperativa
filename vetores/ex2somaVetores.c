#include <stdio.h>  
  
  int vetor1[5];
  int vetor2[5];
  int vetorResultado[5];

int main()
{

  for (int i = 0; i < 5; i++)
  {
    printf("Digite o valor do elemento %d do vetor 1: ", i + 1);
    scanf("%d", &vetor1[i]);

    printf("Digite o valor do elemento %d do vetor 2: ", i + 1);
    scanf("%d", &vetor2[i]);
  }

  for (int i = 0; i < 5; i++)
  {
    vetorResultado[i] = vetor1[i] + vetor2[i];
  }

  printf("Vetor 1:\n");
  for (int i = 0; i < 5; i++)
  {
    printf("%d\n", vetor1[i]);
  }

  printf("Vetor 2:\n");
  for (int i = 0; i < 5; i++)
  {
    printf("%d\n", vetor2[i]);
  }

  printf("Vetor Resultado:\n");
  for (int i = 0; i < 5; i++)
  {
    printf("%d\n", vetorResultado[i]);
  }

}