# -----------------------------------
# Program x86asm.s
# Compute and print the sum 0+...+N
# -----------------------------------

# -----------------------------------
# Comments added by Manos Chatzakis
# HY255 - Assignment 5
# -----------------------------------

	.section .data	   #Stores the following variables to data segment
N:	.long 1000	   #Stores the constant 1000 to data segment
S:	.long 0		   #Stores the constant 0 to data segment
Msg:	.ascii "The sum from 0 to %d is %d\n\0"


	.section .text	   #The following program instructions are stored in text segment
.globl main
main:
	pushl %ebp	   #Save old ebp(base pointer) value to stack
	movl %esp, %ebp    #Copy esp(stack pointer) to ebp(base pointer) to point at main's activation frame after saving its old value

 	# initialize
   	 movl N, %ebx	   #Copy N to ebx

 	# compute sum
L1:
	addl %ebx, S	   #Add ebx to S
	decl %ebx          #Decrease ebx value by 1(ebx = ebx-1)
	cmpl $0, %ebx      #Compare 0 to ebx
	jng  L2	    	   #Goto L2 if ebx <= 0
        movl $L1, %eax	   #Store L1 address to eax
        jmp *%eax          #Goto L1

L2:
	# print result
	pushl S	    	   #Push S to top of the stack(to call printf)
	pushl N	           #Push N to top of the stack(to call printf)
	pushl $Msg  	   #Push Msg to top of the stack(to call printf)
	call printf        #Print the output of the computation(printf call)
	popl %eax   	   #Pop Msg from top of the stack(and save it to a register we dont need)
	popl %eax   	   #Pop N from top of the stack(and save it to a register we dont need)
	popl %eax   	   #Pop S from top of the stack(and save it to a register we dont need)

	# exit
	movl $0, %eax  	   #Copy 0 to eax
        leave	    	   #Exit current procedure
 	ret                #Return from main

