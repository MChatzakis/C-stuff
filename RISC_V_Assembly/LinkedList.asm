						#Assignment 7
						#Manos Chatzakis
						#csd4238@csd.uoc.gr
						#NOTE: All procedures can work using temporary registers, and the cases when
						#we need to store a temporary register do not appear here.
						#That means that there is no need to store variables to stack.
	.data
input_message: 	.asciz "Insert integer:\n"
part_message: 	.asciz "\nGive input to compare (or exit):\n"
space_message:	.asciz " "

	.text
main:
	jal ra, node_alloc 			#Returns the address to a0.
	
	add s0, x0, a0 				#s0 is the head pointer.
	add s1, x0, a0 				#s1 is the tail pointer.
	
	sw x0, 0(s0)				#Initialize dummy node with 0.
	sw x0, 4(s0)				#Initialize dummy node with 0.
			
	jal ra, read_int 			#Returns first input to a0.				
	
	add s2, x0, a0		 		#Save the current input in a saved register.
	
fill_loop: 					#Fill loop is actually the first part of the assignment.
	bge x0, s2, cont			#Branch if input is negative or zero.
				
	jal ra, node_alloc 			#Returns the address to a0.
	
	add t0, x0, a0				#Save the current's node address to a temptorary register.
	
	sw s2, 0(t0)				#Save the node data.
	sw x0, 4(t0)				#Make the next NULL.
	
	sw t0, 4(s1)				#Connect the new node.
	
	add s1, x0, t0				#Change the tail to point to the new last node.
	
	jal ra, read_int 			#Take the next input. Returns the number read to a0.				
	
	add s2, x0, a0				#Save the current input in a saved register.
	
	j fill_loop				#Begin the next loop, to evaluate the branch instruction..
cont:						#This part of the code is the second part of the exercise.
	addi x17, x0, 4				#Print a message.			
	la x10, part_message			
	ecall
	
	jal ra, read_int 			#Returns the comparison input to a0.
	
	add s1, x0, a0				#Apo ekfwnisi. 
	
	add a1, x0, s1				#Initialize a1 to be the second argument(input) for the search list procedure.
	add a0, x0, s0				#Initialize a0 to be the first argument(head address) for the search list procedure.
	
	bge a1, x0, search_list		#Branch if the input is positive or zero.
	
	addi x17, x0, 10			#No branch made.
	ecall					#Execution ends.
	
	j main					#Jump back to main(just to indicate that main ends here.
	
search_list: 					#a0 is the pointer to the head, a1 is the value to compare.
	
	#I want to store somthing into a saved register, so I need to save the reg to stack first.
	addi sp, sp, -4				#Allocate 4 bytes to store s2.
	#add t6, x0, sp				#Keep s2 memmory address.
	sw s2, 0(sp)				#Store s2 to stack.
	
	add s2, x0, a0				#Save the head pointer to a saved register(s2 apo ekfwnisi).
	jal ra, print_node			#Compare and print the current node.
	
	#The ra value is changed. But there is no need to save the previous value to stack as search list jums back to the second part of the programm.
	
	add a0, x0, s2				#Get the address again.
	lw a0, 4(a0)				#Proceed to next node.
	
	bne a0, x0, search_list		#Branch if the next node is not NULL.
	
	lw s2, 0(sp)				#Restore s2.
	addi sp, sp, 4				#Free memory allocated.
	
	j cont					#Jump back to ask for comparison input again.
	
read_int:
	addi x17, x0, 4				#Print a message.	
	la x10, input_message		
	ecall
	
	addi x17, x0, 5				#Load the function code.
	ecall					#Take the input.
	
	add a0, x0, x10				#Return the read value (register a0).
	
	jr ra					#Return to the normal flow.

node_alloc:
	addi x17, x0, 9 			#Load the function code.
	addi x10, x0, 8				#Allocate 8 bytes.
	ecall					#Return a pointer to the struct to x10.
	
	add a0, x0, x10				#Return the pointer.
	
	jr ra					#Jump back to PC next address.
	 	 	 
print_node: 					#a0 is the address of the node, a1 the number to compare.
	lw t0, 0(a0)
	
	bge a1, t0, return_back		#If a1>=t0 return to main.
	
	addi x17, x0, 1				#Load the print function code.
	add x10, x0, t0				#Load the integer to print.
	ecall					#Print the node's data.
	
	addi x17, x0, 4				#Print a space.	
	la x10, space_message		
	ecall
	
	add a0, x0, t0				#Restore the old value of a0.
return_back:
	jr ra					#Jump back to main.
