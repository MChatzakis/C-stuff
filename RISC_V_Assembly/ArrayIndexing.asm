							#CS225 - Assignment 3.4.
							#This program takes 8 integers as input, it saves them into an array
							#and then calculates and prints the 6*a[i] number, for every integer of the array.
							#Author: Manos Chatzakis
							#AM: 4238
							#eMail: csd4238@csd.uoc.gr

							#Data segment modifications
			.data

 a: 			.space 32 			#An array of 8 integers. Its size is 32 bytes as 8*4bytes = 32 bytes
 
 input_message: 	.asciz "Enter 8 separate integers to fill the array:\n"
 enter_integer_message: .asciz "Enter integer\n"
 separetion_message: 	.asciz "----------------------------\n"
 new_line: 		.asciz "\n"
 space:			.asciz " "


			.text				
main:							#Program execution starts here
	la x1 a 					#Load the address of array a using the la pseudo-instruction
	
							#Printing an information message for the output demand
	addi x17, x0, 4					#Load the "print string" command to the register x17
	la x10, input_message				#Load the string to the register x10
	ecall						#Print the string
							#Print ends
	
	addi x2, x0, 0					#Initialize a register with 0 to simulate a counter
	addi x4,x0,8					#Initialize a register to be the constant for the branch instruction inside loop(here is 8 as the array will have 8 integers)
	
	
fill_loop:						#Loop to fill the array with 8 integers (***optional, put in comments if you dont want to print this***)
							#Printing information message to get user's input, for every loop
	addi x17, x0, 4					#Load the "print string" command to register x17
	la x10, enter_integer_message			#Load the string to register x10
	ecall						#Print the string
							#Print ends here
							
	addi x17, x0, 5					#Load the "read integer" command to register x17
	ecall						#Get the integer from user
	sw x10, 0(x1)					#Copy the value of the integer to the proper cell of the array(proper address), in data segment
	
	addi x2, x2, 1					#Increment the counter
	addi x1, x1, 4					#Increment the adress by 4(every integer is equal to 4 bytes) to get the next array cell's adress for the next loop
	
	bne x2,x4,fill_loop 				#Do this while the counter reaches value 8. Notice that if the counter has value 8 the loop body has been executed exaclty 8 times
							#Loop ends

							#Printing a seperation message to indicate that the input is taken and the second part of the program commence
	addi x17, x0, 4					#Load the "print string" command to register x17
	la x10, separetion_message			#Load the string to register x10	
	ecall						#Print the string
							#Separetion message printed.
														
	addi x1, x1, -4					#Get the address back to the last item of the array(In the last loop incrementation, the address was incremented too)
	addi x2, x0, 0					#Re-initialize the counter

print_loop:						#Loop to calculate and print the demanded output.
	
	lw x10, 0(x1)					#Load the current's array index (cell's) value(a[i])
	
							#Calculate the 6*a[i] value, using the 3 additions method.
	add x15, x10, x10				#etc. x15 = 5 + 5 = 10
	add x10, x15, x10				#etc. x10 = 10 + 5 = 15	
	add x10, x10, x10				#etc. x10 = 15 + 15 = 30 = 6*5
							#Calculation done
							
							#Printing the calculation value(output)
	addi x17, x0, 1					#Load the "print integer" command/instruction
	ecall						#Value of register x10 printed				
							#Value printed
	
							#Printing a space for the next loop.
	addi x17, x0, 4					#Load the "print string" command to register x17
	la x10, space					#Load the string to register x10
	ecall						#Print the string
							#Space printed
							
	addi x2, x2, 1					#Increment the counter
	addi x1, x1, -4					#Decrease the address by 4 bytes(array is indexed backwards)
	
	bne x2,x4,print_loop				#Do this while all the array is indexed (x2 == 8)
							#Loop ends here
							
							#Printing a new line for the next procedure.
	addi x17, x0, 4					#Load the "print string" command to register x17
	la x10, new_line				#Load the string to register x10
	ecall						#Print the string
							#New line printed						
							
	j main						#Jump back to main. Suggestion: put a breakpoint here when testing the program