
#include "decoder.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void addToIt(int *bit, int *byte, int val, char *decoded)
{//sets the bit at index bit to val within the specified byte
  decoded[*byte] |= val << *bit;
  //we count backwards from 7 with bits
  (*bit)--;
  //if it goes below 0, start a new byte
  if(*bit < 0)
  {
    //move byte by 1 and set bit back too 0
    (*byte)++;
    *bit=7;
  }
}
void addBit(const char *bins, int *bit, int *byte, char *decoded)
{//loops through the char passed by the array bikey, converts each bit to an int
  //and adds the bit at the specified byte in decoded
  int length = strlen(bins);
  for(int i=0; i<length; i++)
  {
    addToIt(bit, byte, ((int)(bins[i] - '0')), decoded);
  }
}
void decoder(const char *encoded, char *decoded, int maxLen)
{
  int bit = 7, byte=0;
  for(int i=0; i<maxLen; i++)
  {
    decoded[i]=0;
  }
  //keys are paired together by sharing index value
  const char *key = "e*PQY!@R^hal";
  const char *const binkey[] = {"000", "001", "010", "011", "100", "101", "110",
    "111", "00", "01", "10", "11"};
  //loops through entire text, matches each char with the bits using arrays
  //runs until encoded has reached end of file or untill 1000 chars has been
  //added to decoded
  for(int i=0, x=0; (x/8) < maxLen && encoded[i] != '\0';i++)
  {
    for(int j=0; j<12; j++)
    {//loop to find matchinc chars/bits in arrays
      if(encoded[i] == key[j])
        //if it finds match, it will add bits 
        //in bikey at same directory and break ouf of loop
      {
        addBit(binkey[j], &bit, &byte, decoded);
        //to track number of bits added
        x = x + strlen(binkey[j]);
        break;
      }
    }
  }
}
