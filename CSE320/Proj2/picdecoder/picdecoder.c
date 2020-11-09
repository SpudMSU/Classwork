
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "picdecoder.h"  
// A structure to represent a stack
void delete_stack(Stack *elem){
  StackNode *a;
  //frees every element in the stack
  for (a = elem->top; a!=NULL;){
    StackNode *nxt = a->next;
    free(a->data);
    free(a);
    a= nxt;//frees stacknode
  }
  elem->top = NULL; //nothing in stack
}
void push(const char *data, Stack *elem){
  //hese will be free'd when stack is free'd
  StackNode *newtop = (StackNode *)calloc(1,sizeof(StackNode));
  newtop->data = (char *)calloc(strlen(data)+1, sizeof(char));
  strncpy(newtop->data, data, strlen(data));//copys data to element 
  newtop->next = elem->top;//current top is next element
  if (elem->top == NULL){
    elem->top = newtop;//puts elem on top
  }else{
    elem->top = newtop;
  }
}
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
    if(newc[i]== '1')break;//cant put condition at begining or do dowhile
    //of the backwards counting i
  }
  return newc;
}

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
char *add(const char *a, const char*b)
{
  int carry =0;
  int i = strlen(a);
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
char *xor(const char *line, char *top)
{//function for exclusive or
  size_t len = strlen(line);//gets length
  //this is freed when res is free'd in main
  char *dest = (char*) calloc(len, sizeof(char*));
  int numa, numb;
  for(int i = len-1; i>=0; i--)
  {//if both 1 or 0 input 0. Otherwise 1
    numa = line[i] - '0';
    numb = top[i]-'0';
    if(numa==numb)
    {
      dest[i] = '0';
    }
    else{
      dest[i] = '1';
    }
  }
  return dest;
}
char *subtract(const char* line, char *top)
{//negates top then adds them
  char *negd = negate(top);
  char *res = add(line, negd);
  free(negd);
  return res;
}
