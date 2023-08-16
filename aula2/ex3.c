#include <stdio.h>


int main()
{
  float PI = 3.1416;
  int R = 0;
  double VOLUME = 0;

  while (R <= 6){
    VOLUME = (4.0/3) * PI * (R*R*R);
    printf("Raio: %d , Volume: %f\n", R, VOLUME);
    R = R + 2;}


return 0;

}