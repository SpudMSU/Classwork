@ 
@ Functions to determine first and last minor 
@ boarding a cruise ship.
@
 
.text
.global first_minor
.global last_minor
@
@ Determine the first minor (<18) in an array of numbers
@ r0 - Pointer to the array
@ r1 - Number of items in the array
@
@as seen in tutorial

first_minor:
  movs r1, r1     @ set flags
  beq none        @ if r1 == 0
            
  ldr r2, [r0]    @ r2 <= *data
  cmp r2, #18     @ r2 < 18?
  blt gotit       @ If so...
                        
  add r0, r0, #4  @ data++
                                
  sub r1, r1, #1  @ r1 <- r1 - 1
  b first_minor
                                    
gotit:
  mov r0, r2
  bx lr
                                            
none:
  mov r0,#0
  bx lr           @ return

@code was copy and pasted from tutorial
last_minor:
    mov r2, r1      @ size
    sub r2, r2, #1  @ size-1
    lsl r2, r2, #2  @ (size-1) * 4
    add r0, r0, r2  @ &data[size-1]

last_minor_loop:
  movs r1, r1     @ set flags
  beq none_last
                            
  ldr r2, [r0]
  cmp r2, #18
  blt last_gotit
                                        
  sub r0, r0, #4
  sub r1, r1, #1
  b last_minor_loop

last_gotit:
  mov r0, r2
  bx lr
none_last:
  mov r0, #0
  bx lr
