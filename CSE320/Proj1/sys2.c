/**
  *My first C program
  *@author Spencer D Cassetta
  */
#include <stdio.h>
int factorial(int n)
{
  int f = 1;
  int i;
  for(i=1; i<=n; i++)
  {
    f*=i;
  }
  return f;
}
double square(double x);
int main()
{
  double radius = 7.88;
  double height = 12.231;
  printf("The cylinder has a radius of %f and a height of %f\n", radius,
      height);
  printf("the factorial of 4 is %d\n", factorial(4));
  printf("The square of 22 is %f\n", square(22));
}
double square(double x)
{
    return x * x;
}
