#include <stdio.h>

int first(int);
int second(int, int);
int main() 
{
	int value = 27;
	int result = first(value);
	printf("first(%d) = %d\n", value, result);
  result = second(12, 22);
  printf("second(12, 22) = %d\n", result);
	return 0;
}
