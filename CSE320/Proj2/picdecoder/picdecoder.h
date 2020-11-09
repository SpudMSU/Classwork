#ifndef PIC_DECODER
#define PIC_DECODER
#define BINARY_SIZE 100
typedef struct StackNode
{
  char *data;
  struct StackNode *next;
}StackNode;
typedef struct Stack
{
  StackNode *top;
}Stack;
void push(const char *line, Stack *st);
void delete_stack(Stack *elem);
char *inc(const char *number);
char *pull(StackNode *elem);
char *negate(const char *number);
char *add(const char *a, const char *b);
char *xor(const char *line, char *top);
char *subtract(const char* line, char *top);


#endif
