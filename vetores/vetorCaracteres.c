#include <stdio.h>
#include <stdlib.h>

int main()
{
printf("Digite o comprimento da string: ");

int comprimento;

scanf("%d", &comprimento);

char cadeia[comprimento];

printf("Digite a string: ");

setbuf(stdin, NULL); // limpa o buffer do teclado

for (int i = 0; i < comprimento; i++)
{
  cadeia[i] = getchar();
  putchar(cadeia[i]);
}

}
