#include <stdio.h>
#include <stdlib.h>


int tamanho = 0;

void inverterVetor(char* vetor, int tamanho) {
    int inicio = 0;
    int fim = tamanho - 1;
    while (inicio < fim) {
        int temp = vetor[inicio];
        vetor[inicio] = vetor[fim];
        vetor[fim] = temp;
        inicio++;
        fim--;
    }
}

int main()
{   
    int tamanho;
    printf("Digite o tamanho do vetor:");
    scanf("%d", &tamanho);

    char vetor[tamanho];

    printf("Digite a string: ");

    setbuf(stdin, NULL); 

    for(int i = 0; i < tamanho; i++)
    {
        vetor[i] = getchar();
    }


    inverterVetor(vetor, tamanho);

    for(int i = 0; i < tamanho; i++)
    {
        putchar(vetor[i]);
    }

}
