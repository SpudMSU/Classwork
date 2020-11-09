@ 
@ Simple program that adds four numbers
@
 
.text
.global add

add:
	add r2, r2, r3	@ r2 = r2 + r3
	add r0, r0, r1	@ r0 = r0 + r1
	add r0, r0, r2	@ r0 = r0 + r2
  add r0, r0, r0
	bx lr		@ return
    
