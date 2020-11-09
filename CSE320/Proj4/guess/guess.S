
@
@ Data section
@
.data

@
@ Messages
@
usagemsg:
    .asciz "Usage: guess [number]\n"
splash:
    .asciz "We are guessing the number %d\n"
toolo:
    .asciz "You guessed too low\n"
toohi:
    .asciz "You guessed too high\n"
rit:
    .asciz "You guessed the number correctly \n"

@
@
@ Input buffer
@
.set BUFFERSIZE,100

buffer:
    .space BUFFERSIZE,0
.text
.global main
@ main(argc, argv)
  @ r0: The number of arguments
  @ r1: Pointer to an array of string pointers
  @
main:
  stmfd sp!,{r4,lr}  @ Save r4, lr on the stack       
  @ Did the user provide an argument?
  cmp r0,#2
  blt usage

  @ Determine the number to guess
  add r1,#4       @ Move to the second string
  ldr r0,[r1]     @ Get the pointer to the actual string
  bl atoi         @ Convert to an integer
  mov r4, r0
  @
  @ Splash
  @

  mov r1, r0
  ldr r0,=splash
  bl printf 

loop:
  @ fgets(buffer, sizeof(buffer), stdin)
  ldr r0,=buffer      @ Argument 1: buffer address
  ldr r1,=BUFFERSIZE  @ Argument 2: size of the buffer
  ldr r2,=stdin       @ Address of stdin variable in memory
  ldr r2,[r2]         @ Argument 3: value of stdin
  bl fgets

  @
  @ Convert to an integer
  @
  bl atoi
  @ Test it
  cmp r0,r4
  blt toolow
  bgt toohigh
  beq right
  mov r0, #0

right:
  ldr r0, =rit
  bl printf
  mov r0, #0
  b main_return
main_return:
  ldmfd sp!,{r4,lr}  @ Restore r4, lr from the stack
  bx lr

usage:
  ldr r0, =usagemsg
  bl printf

  mov r0,#1
  b main_return

@ Guess was too low
toolow:
  ldr r0, =toolo
  bl printf
  b loop
        
@ Guess was too high
toohigh:
  ldr r0, =toohi
  bl printf
  b loop
