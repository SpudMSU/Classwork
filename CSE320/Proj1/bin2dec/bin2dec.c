#include "bin2dec.h"
#include <string.h>
/**
 * Convert a binary representation of a 
 * number to an unsigned integer. 
 * 
 * For this function, the values T and F represent 
 * true (1) and false (0). So, the string:
 * 
 * TTFT is equal to 1101 binary, which is equal to 13.
 *
 * Unexpected characters are ignored. Only 1's and 0's are
 * considered to be valid. Stop converting when you get
 * to a space character or the end of the string. The 
 * representation is case-insensitive (both T/F and t/f 
 * are valid true and false values).
 *
 * 'aTFcT TT' should convert to 5
 * 'ftft' should convert to 5
 *
 * @param binary Binary number as a string of 'T's and 'F's. 
 * @returns unsigned int result
 */
unsigned int power(unsigned int x, int exp)
{//function that returns x to the power of exp
  //inspired by example in FAQ
  int num=1;
  for(int i=0; i<exp; i++)
  {
    num*=x;
  }
  return(num);
}
unsigned int bin2dec(const char *binary)
{//loops through string backwards and adds the value of the specific binary
  //number too num
  unsigned int num=0;
  for(int i = strlen(binary) -1, exp=0;i>=0;i--)
  {
    //T or t represents a 1
   // Add its value and increment the number place
    if(binary[i] == 'T'||binary[i]=='t')
    {
      num += power(2, exp);
      exp++;
    }
    //F represents a 0
    //only increment the number place
    else if(binary[i]=='F'||binary[i]=='f')
    {
      exp++;
    }
    //if a space occurs we reset the count
    //You told us to stop if we hit a space, however thats assuming you read the
    //text from left too right and then reverse it. I just read the number
    //backwards and reset count if we reach a space. I think it is easier
    else if(binary[i]==' ')
    {
      num=0;
      exp=0;
    }
  }
  return num;
}

