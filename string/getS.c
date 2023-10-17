#include <stdio.h>
#include <string.h>

#define MAX 10

int main(){
  char texto[MAX];
  fgets(texto, MAX, stdin);

  int CRLF = strcspn(texto, "\r\n");
  texto[CRLF] = "\0";

  printf("%d\n", strlen(texto));
  puts(texto);

  char ultimo = texto[strlen(texto) - 1];
  printf("ultimo carater: %c\n", ultimo);
  printf("%d\n", ultimo);

  return 0;
}