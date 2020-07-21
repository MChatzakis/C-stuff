# ################################################################## #
# Name: Manos Chatzakis                                              #
# AM  : 4238                                                         #
# Mail: csd4238@csd.uoc.gr                                           #
# File: traces.s                                                     #
# This file contains answers to the first part of Exercise 6.        #
# ################################################################## #

Assignment a
   # Assembly file contains the following commands:

   # ReadString function
   0x8048aac <readString>:      push   %ebp                         # Save old base pointer value
   0x8048aad <readString+1>:    mov    %esp,%ebp                    # ebp = esp
   0x8048aaf <readString+3>:    sub    $0x34,%esp                   # Allocate stack memory for local variables (buf,c,i)

   # First loop begins
   0x8048ab2 <readString+6>:    movl   $0x0,-0x4(%ebp)              # i = 0
   0x8048ab9 <readString+13>:   mov    0x80d4b44,%eax               # eax = return address
   0x8048abe <readString+18>:   push   %eax                         # Push return address to stack to return from function
   0x8048abf <readString+19>:   call   0x8050850 <getc>             # Call fgetc function
   0x8048ac4 <readString+24>:   add    $0x4,%esp
   0x8048ac7 <readString+27>:   mov    %eax,-0x8(%ebp)              # Saves input character to c
   0x8048aca <readString+30>:   cmpl   $0xffffffff,-0x8(%ebp)       # Compare c with EOF (EOF = -1)
   0x8048ace <readString+34>:   je     0x8048ae8 <readString+60>    # Skip while isntructions if c = EOF (break)
   0x8048ad0 <readString+36>:   cmpl   $0xa,-0x8(%ebp)              # Compare c with \n
   0x8048ad4 <readString+40>:   je     0x8048ae8 <readString+60>    # Skip while instructions if c = \n (break)

   # The following lines are for buf[i++] = c
   0x8048ad6 <readString+42>:   mov    -0x4(%ebp),%eax
   0x8048ad9 <readString+45>:   lea    0x1(%eax),%edx
   0x8048adc <readString+48>:   mov    %edx,-0x4(%ebp)              # eax <- i
   0x8048adf <readString+51>:   mov    -0x8(%ebp),%edx              # edx <- c
   0x8048ae2 <readString+54>:   mov    %dl,-0x34(%ebp,%eax,1)       # Save character to buf ( buf[i] = c )

   0x8048ae6 <readString+58>:   jmp    0x8048ab9 <readString+13>    # Go back to get new input character
   # First loop ends

   0x8048ae8 <readString+60>:   lea    -0x34(%ebp),%edx
   0x8048aeb <readString+63>:   mov    -0x4(%ebp),%eax              # eax <- i
   0x8048aee <readString+66>:   add    %edx,%eax                    # go to buf[i] address (in eax)
   0x8048af0 <readString+68>:   movb   $0x0,(%eax)                  # buf[i] = 0

   # Second loop begins
   0x8048af3 <readString+71>:   movl   $0x0,-0x4(%ebp)              # i = 0
   0x8048afa <readString+78>:   jmp    0x8048b15 <readString+105>   # Go to rS+105 to compare

   # Following lines are for s[i] = buf[i], i++
   0x8048afc <readString+80>:   mov    -0x4(%ebp),%edx
   0x8048aff <readString+83>:   mov    0x8(%ebp),%eax
   0x8048b02 <readString+86>:   add    %eax,%edx
   0x8048b04 <readString+88>:   lea    -0x34(%ebp),%ecx
   0x8048b07 <readString+91>:   mov    -0x4(%ebp),%eax
   0x8048b0a <readString+94>:   add    %ecx,%eax
   0x8048b0c <readString+96>:   movzbl (%eax),%eax                  # Assign buf[i] to s[i]
   0x8048b0f <readString+99>:   mov    %al,(%edx)
   0x8048b11 <readString+101>:  addl   $0x1,-0x4(%ebp)              # i++

   0x8048b15 <readString+105>:  cmpl   $0x2b,-0x4(%ebp)             # For comparison (0x2b = 43)
   0x8048b19 <readString+109>:  jle    0x8048afc <readString+80>    # Go back to copy next character if i<=43
   # Second loop ends

   # Returning
   0x8048b1b <readString+111>:  nop
   0x8048b1c <readString+112>:  leave
   0x8048b1d <readString+113>:  ret

   # Main function
   0x8048b1e <main>:    push   %ebp				# Save old ebp value
   0x8048b1f <main+1>:  mov    %esp,%ebp
   0x8048b21 <main+3>:  mov    $0x80d65e0,%eax
   0x8048b26 <main+8>:  and    $0xfffff000,%eax
   0x8048b2b <main+13>: push   $0x7
   0x8048b2d <main+15>: push   $0x1
   0x8048b2f <main+17>: push   %eax
   0x8048b30 <main+18>: call   0x805e180 <mprotect> 		# Call mprotect function
   0x8048b35 <main+23>: add    $0xc,%esp
   0x8048b38 <main+26>: push   $0x80ab0a8
   0x8048b3d <main+31>: call   0x804f070 <puts>			# Call puts function
   0x8048b42 <main+36>: add    $0x4,%esp
   0x8048b45 <main+39>: push   $0x80d65e0
   0x8048b4a <main+44>: call   0x8048aac <readString>		# Call readString
   0x8048b4f <main+49>: add    $0x4,%esp
   0x8048b52 <main+52>: push   $0x80ab0bb
   0x8048b57 <main+57>: push   $0x80d65e0
   0x8048b5c <main+62>: call   0x805af90 <strcmp>		# Compare the name given to "Angelos Bilas"
   0x8048b61 <main+67>: add    $0x8,%esp
   0x8048b64 <main+70>: test   %eax,%eax
   0x8048b66 <main+72>: jne    0x8048b6f <main+81>		# If the names differ, go to print the name and grade 3
   0x8048b68 <main+74>: movb   $0x36,0x80d46e8
   0x8048b6f <main+81>: push   $0x80d65e0
   0x8048b74 <main+86>: push   $0x80ab0c9
   0x8048b79 <main+91>: call   0x804eaf0 <printf>		# Print the first message
   0x8048b7e <main+96>: add    $0x8,%esp
   0x8048b81 <main+99>: movzbl 0x80d46e8,%eax
   0x8048b88 <main+106>:        movsbl %al,%eax
   0x8048b8b <main+109>:        push   %eax
   0x8048b8c <main+110>:        push   $0x80ab0dc
   0x8048b91 <main+115>:        call   0x804eaf0 <printf>	# Print the second message
   0x8048b96 <main+120>:        add    $0x8,%esp
   0x8048b99 <main+123>:        push   $0x0
   0x8048b9b <main+125>:        call   0x804e110 <exit>		# Program termination

   # Termination
   0x8048ba0 <__libc_start_main>:       push   %ebp
   0x8048ba1 <__libc_start_main+1>:     mov    $0x0,%eax
   0x8048ba6 <__libc_start_main+6>:     push   %edi
   0x8048ba7 <__libc_start_main+7>:     push   %esi
   0x8048ba8 <__libc_start_main+8>:     push   %ebx
   0x8048ba9 <__libc_start_main+9>:     sub    $0x4c,%esp

Assignment b
    DATA SEGMENT:

	Using the following instructions:
	(gdb) print grade
	$1 = 51 '3'
	(gdb) print &grade
	$2 = 0x80d46e8 <grade> "3"

	Variable	Value		Address
	  grade		  3            0x80d46e8

Assignment c
    BSS SEGMENT:

	Using the following instructions:
	(gdb) print &Name
	$3 = (char (*)[44]) 0x80d65e0 <Name>
	(print name = 0)

	Array		Address
	Name           0x80d65e0

Assignment d

	We can put the breakpoint wherever we want inside readString function.
	I used command "b 24" but we can use "b 27" or even "break readString + 71"

	Using the following instructions:
	(gdb)print $esp
	$4 = (void *) 0xbffff588
	(gdb)print $ebp
	$5 = (void *) 0xbffff5bc

	(gdb) x/64x $esp
	0xbffff588:[buf]0x4d    0x61    0x6e    0x6f    0x73    0x00    0x0a    0x08
	0xbffff590:     0x7f    0xf1    0x04    0x08    0x80    0x48    0x0d    0x08
	0xbffff598:     0x0a    0x00    0x00    0x00    0x12    0x00    0x00    0x00
	0xbffff5a0:     0x01    0x00    0x00    0x00    0x54    0xf6    0xff    0xbf
	0xbffff5a8:     0x5c    0xf6    0xff    0xbf    0x01    0x00    0x00    0x00
	0xbffff5b0:     0x34    0x80    0x04    0x08 [c]0x0a    0x00    0x00    0x00
	0xbffff5b8: [i] 0x05    0x00    0x00    0x00[ebp]0xc8    0xf5    0xff    0xbf
	0xbffff5c0: [ra]0x4f    0x8b    0x04    0x08[arg s]0xe0    0x65    0x0d    0x08
