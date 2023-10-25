#include <stdio.h>
#include <string.h>


int main(){

  char str1[10];
    printf("Enter str1: ");
    scanf("%s", str1);
  char str2[10];
    printf("Enter str2: ");
    scanf("%s", str2);



  strcat(str1, str2);
  printf("%s\n", str1);

  return 0;

}