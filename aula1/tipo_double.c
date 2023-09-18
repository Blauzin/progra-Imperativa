#include <stdio.h>

int main()
{
    double PI = 3.14;
    double raio = 10.0;
    double area = PI * raio * raio;
    printf("%f\n", area); // %f seria de float

    printf("%zu\n", sizeof(double)); // %zu significa unsigned (sem sinal de negativo) integer (numero natural)
    // ou seja %zu seria o modulo de um numero inteiro, pois não guarda seu sinal

    return 0;
}