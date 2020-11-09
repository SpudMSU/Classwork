/**
 * @file main.c
 * Simple program to test the assembly multiplication functions.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned int dumb_multiply(unsigned int a, unsigned int b);
unsigned int dumb_sqrt(unsigned int num);
unsigned int efficient_sqrt(unsigned int num);

void test_dumb(unsigned int a, unsigned int b);
void test_dumb_sqrt(unsigned int a);
void test_sqrt(unsigned int a);
unsigned int isqrt(unsigned int num);

int main()
{
	test_dumb(23, 37);
  test_dumb(0, 0);
  test_dumb(12,13);
  test_dumb(14, 0);
	
	return 0;
}

void test_dumb(unsigned int a, unsigned int b)
{
	unsigned int product = dumb_multiply(a, b);
	printf("Dumb: %u x %u = %u / should be %u\n", a, b, product, a * b);
}



void test_dumb_sqrt(unsigned int a)
{
	unsigned int s = dumb_sqrt(a);
	printf("sqrt(%u) = %u / should be %u\n", a, s, isqrt(a));
}


void test_sqrt(unsigned int a)
{
	unsigned int s = efficient_sqrt(a);
	printf("sqrt(%u) = %u / should be %u\n", a, s, isqrt(a));
}


/**
 * This is the function we are testing against.
 * The assembly solution should yield the same result
 */
unsigned int isqrt(unsigned int num) {
    unsigned int  res = 0;
    unsigned int  bit = 1 << 30;
 
    // "bit" starts at the highest power of four <= the argument.
    while (bit > num) {
        bit >>= 2;
	}
	
    while (bit != 0) {
        if (num >= res + bit) {
            num -= res + bit;
            res += bit << 1;
        }
        
        res >>= 1;
        bit >>= 2;
    }
    
    return res;
}
