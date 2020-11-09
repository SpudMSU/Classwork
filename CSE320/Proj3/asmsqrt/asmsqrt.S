

.text
.global dumb_multiply
.global dumb_sqrt
.global efficient_sqrt


@
@ Multiply two numbers together by brute force
@ r0 - First unsigned value
@ r1 - Second unsigned value
@ Returns r0 * r1
@
dumb_multiply:
  @initializes variables
  mov r3, #0
  mov r2, #0
  b forloop @enters main loop

forloop:
  subs r2, r2, r0 @i-a. Sets flag
  add r2, r2, r0 @i-a+a=i
  beq loopend @end loop if sub resulted in 0
  add r3, r3, r1 @sum+=b
  add r2, r2, #1 @i++
  b forloop @continue the loop

loopend:
  mov r0, r3 @moves sum into r0
  bx lr
@ Dumb, inefficient square root computation
@ r0 - Passed in value: num
@ Returns sqrt(r0)
@
dumb_sqrt:
@initializes variables
  mov r1, #1 @variable n
  mov r2, #1 @variable n_sqr
  mov r3, #0 @used for storage
  b findsqr @goes into first loop

findsqr:
  cmp r0, r2 @sets flag for num-n_sqr
  beq found @if n_sqr==num then end
  bmi isbigger @if n_sqr>num subtract 1 and return
  add r3, r1, r1 @stores n+n (n*2) in r3
  add r3, r3, #1 @(n*2)+1
  add r2, r2, r3 @ n_sqr += (n*2)+1
  add r1, r1, #1 @n++
  b findsqr @continue loop

found:
  mov r0, r1 @move n to r0 and return
  bx lr

isbigger:
  sub r1, r1, #1 @n--
  b found @return
@ Efficient integer square root computation
@ r0 - Passed in value: num
@ Returns sqrt(r0)
@
efficient_sqrt:
  mov r1, #0 @ res = 0
  mov r2, #1 @ bit = 1
  lsl r2, r2, #30 @ bit = 1 << 30
  b whilenum

whilenum:
  cmp r2, r0 @sets flag for bit-num
  beq bitnotzip @break to next if bit==num
  bmi bitnotzip @break to next if num > bit
  lsr r2, r2, #2 @bit >>=2
  b whilenum

bitnotzip:
  subs r2, r2, #0 @seeing if bit==0
  beq donesqr @if so, we are done
  add r3, r1, r2 @ r3 = res+bit
  cmp r3, r0 @(res+bit) - num sets flag
  bmi ifnum @if num > (res+bit)
  beq ifnum @if num = (res+bit)
  b zipend @continue on in loop
zipend:
  lsr r1, r1, #1 @res >>=1
  lsr r2, r2, #2 @bit >>=2
  b bitnotzip

ifnum:
  sub r0, r0, r3 @num-=res+bit (still in r3
  lsl r3, r2, #1 @ stores bit << 1 in r3
  add r1, r1, r3 @ res += bit <<1
  b zipend @finish the half completed while loop

donesqr:
  mov r0, r1 @return res
  bx lr
