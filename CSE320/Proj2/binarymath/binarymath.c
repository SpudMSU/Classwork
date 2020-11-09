#include <stdlib.h>
#include <string.h>
#include "binarymath.h"



/**
 * Increment a BINARY_SIZE binary number expressed as a 
 * character string.
 * @param number The number we are passed
 * @returns Incremented version of the number
 */

char *inc(const char *number)
{
  size_t i = strlen(number);
  char *newc = (char*)calloc(i, sizeof(char*));
  strncpy(newc, number, i);
  //string array with 1 at index 0 and 0 at index 1
  char const flip[] = "10";
  for(i-=1; i>=0; i--)
  {
    // if newc[i]=0 then it will = flip[0] which is 1
    newc[i] = flip[newc[i] -'0']; // -'0' to convert to int
    //if it turned a 0 into a 1 then we are done
    if(newc[i]== '1')break;//cant put condition at begining or do dowhile because
    //of the backwards counting i
  }
  return newc;
}


/**
 * Negate a BINARY_SIZE binary number expressed as a character string
 * @param number The number we are passed
 * @returns Incremented version of the number
 */
char *negate(const char *number)
{
  size_t len=strlen(number);
  char *reversed = (char*)calloc(len, sizeof(char*));
  strncpy(reversed, number, len);
  //array with a 1 in the 0 index and a 0 in the 1 index
  char const flip[] = "10";
  int i=0;
  while(reversed[i] !='\0')
  {//until we reach the end, it turns a 0 into a 1 and a 1 into a 0
    //if reversed[i] = 1, set it = to flip[1] which is 0
    //same goes for otherway around
    reversed[i] = flip[reversed[i] - '0'];
    i++;
  }
  
    //increment the binary string and return it
  char *incd = inc(reversed);
  free(reversed);
  return incd;
}

/**
 * Add two BINARY_SIZE binary numbers expressed as
 * a character string. 
 * @param a First number to add
 * @param b Second number to add
 * @return a + b
 */
char*add(const char *a, const char*b)
{
  int carry =0;
  int i = strlen(a);//overrun protection
  char *dest=(char*)calloc(i, sizeof(char*));
  char result;
  int numa, numb;
  for(i=i-1;i>=0;i--)
  {//goes through each string and calculates the binary addition
    numa=a[i]-'0';//char to int
    numb=b[i]-'0';
    carry=numa+numb+carry;
    result=carry%2+'0';//turns the result into a char
    carry=carry/2;//carry is equal to result beforehand. 
    //^If result is 3 or 2 carry a 1. if 1, then carry is 0
    dest[i]=result; //add it to the destination string
  }
  return dest;
}
/* a character string.
 * @param a First number
 * @param b Second number 
 * @return a - b
 */
char *sub(const char *a, const char *b)
{//as we learned in system2, too subtract a-b just negate b then add them
  char *negd = negate(b);
  char *res = add(a, negd);
  free(negd);  
  return res;
}

