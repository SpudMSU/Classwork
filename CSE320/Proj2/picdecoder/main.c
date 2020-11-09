#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "picdecoder.h"
int main(int argc, char *argv[]) 
{ 
  if (argc < 2) 
  { 
    printf("Usage: rpn file\n"); 
    return 1; 
  } 
  FILE *fp = fopen(argv[1], "r"); 
  if (fp == NULL) 
  { 
    printf("Unable to open input file\n"); 
    return 1; 
  }
  int BUFFER_SIZE = 1000;//Dont know of how to determine buffersize 
  //befor fgets)
  Stack elem; 
  StackNode* root = NULL; 
  elem.top = NULL; //initialize the element in stack
  char c; 
  char buffer[BUFFER_SIZE]; 
  //free these
  char *binc = (char*)calloc(BUFFER_SIZE-1,sizeof(char*)); 
  char *res =(char*)calloc(BUFFER_SIZE-1,sizeof(char*));  
  while(fgets(buffer, sizeof(buffer), fp) != NULL) 
  {
    int len = strlen(buffer);
    BUFFER_SIZE = len; //to decrease mem usage once buffesize is known
    c = buffer[0]; 
    //turn \n into \o
    if(buffer[len-1] == '\n'){ 
      buffer[len-1]='\0'; 
    } 
    //put remaining buffer into binc
    for(int i=1; i < BUFFER_SIZE; i++) 
    { 
      binc[i-1] = buffer[i]; 
    } 
    //chooses which command
    switch(c){ 
      case 'P': 
        res = binc; 
        break; 
      case 'X': 
        res = xor(binc, elem.top->data); 
        break; 
      case 'A': 
        res = add(binc, elem.top->data); 
        break; 
      case 'S': 
        res = subtract(binc, elem.top->data); 
        break; 
    } 
    //pushes result from command to stack
    push(res, &elem);
  }
  //free variables and close file
  free(binc);
  free(res);
  fclose(fp);
  //free this
  char *line = (char*)calloc(BUFFER_SIZE-1, sizeof(char));
  for(root = elem.top; root !=NULL;root = root ->next)
  {//itterate through stack and turn 0 to spaces and 1 to X's
    for(int i=0; i<BUFFER_SIZE-1; i++){
      switch(root->data[i]){
        case '0':
          line[i]=' ';
          break;
        case '1':
          line[i] = 'X';
          break;
      }
    }
    //prints after every line
    printf("%s\n",line);
  }
  //freeing stack and variable
  delete_stack(&elem);
  free(line);
  return 0;
}
