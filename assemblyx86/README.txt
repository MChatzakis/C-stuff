########################################################
# Course: HY255 - Programming Lab - Exercise 5         #
# Name  : Manos Chatzakis                              #
# AM    : 4238                                         #
# eMail : csd4238@csd.uoc.gr                           #
# File  : README.txt                                   #
########################################################

--Assignment 1-- 
  (a) Output is: "The sum from 0 to 1000 is 500500".
  (b) Comments will be found in file "x86asm_comments.s".
  (c) Use "gcc -g -o x86asm x86asm.s" to use gdb
  (d) Programm has a total of 19 instructions (main,L1,L2).
	> First gdb command should be "x/19i *main"
	> Using "x/19i *main" we have the following results:
		-Address of first instruction is: 0x80483fb (main +  0)
		-Address of last instruction is : 0x8048436 (L2   + 31) and is instruction ret, which occupies just 1 byte.(I found it out by adding another ret instruction to the program).
	  Thats means that the whole memory needed is (0x8048436 - 0x80483fb) + 1 [Byte] = 0x3B + 1 = [decimal] 60 Bytes
	  Using the same method, offset should be [address of L2] 0x8048417 - [address of the first insruction] 0x80483fb = 0x1C = [decimal] 28 Bytes => offset = 28.
	  To add the breakpoint, we use "b *main+28" 
  (e) -"p (int )S"      => S    = 500500 (value of S).
      -"p (int *)&S"    => &S   = 0x80496a0(address of S).
      -"p (char *)&Msg" => &Msg = 0x80496a4 "The sum from 0 to %d is %d\n" (address of Msg).
      -"*(int *)&S = 99". After this, program output is "The sum from 0 to 1000 is 99".

--Assignment 2--
  (a) Output is: "The sum from 0 to 1000 is 500500". 
  (b) Use "gcc -Wall -pedantic -ansi -O2 -S sum.c" and "vim(nano) sum.s". The .s file contains assembly 28 instructions.
  (c) Use "gcc -Wall -pedantic -ansi -g -O2 -o sum sum.c" and "gdb sum" to use gdb.
  (d) Same as Assignment 1:
	Programm has a total of 28 instructions. (.xx instructions are dirs for the assembler, so they need to be skipped)
	> First gdb command should be "x/28i *main"
	> Using "x/28i *main" we have the following results:
		-Address of first instruction is: 0x8048300 (main +  0)
		-Address of last instruction is : 0x8048359 (main + 89)
	  Sol1:Thats means that the whole memory needed is (0x8048359 - 0x8048300) + 1 [Byte, for ret, as above] = 0x59 + 1 = [decimal] 90 Bytes
	  Sol2:[main+89] - [main + 0] + 1 = 90 Bytes
          For .c files, to put breakpoints we shall use "b ??" where ?? is the line of the file to put the breakpoint. Looking at the .c file, to put a breakpoint before printf, we should put a bp at line 13, so we use "b 13" , so offset = 13. 
  (e) -"p Sum"  => Sum  = 500500 (value of Sum)
      -"p &Sum" => &Sum = (int *) 0x8049704 <Sum> (address of Sum)
      -"p n"    => n  = -1 (value of n)
      -"p &n"   => &n = (int *) 0x80496fc <n> (address of n)
      -"set Sum = 98". Program output is "The sum from 0 to 1000 is 500500".
      -"set *(int *)[address of Sum above] = 99". Program output is "The sum from 0 to 1000 is 500500".
  (f) Program output is "The sum from 0 to 1000 is 495450". 

--Assignment 3--
  (a) Program output is "The sum from 0 to 1000 is 500500".
  (b) The program has 25 assembly instructions.
  (c) Program output is "The sum from 0 to 1000 is 500500".


--Some comments--
  1.Exercise took about 4 hours to complete.
  2.GDB manuals where used.
