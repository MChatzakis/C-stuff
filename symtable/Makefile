#########################################################################
# Name : Manos Chatzakis                                                #
# AM   : 4238                                                           #
# eMail: csd4238@csd.uoc.gr                                             #
# This is the makefile. Use this to produce test executables            #
# for the symtable library.                                             #
#########################################################################

#Default compiler
CC = gcc

#Compilation flags for .o and .out files
FLAGS_O = -Wall -ansi -pedantic -c
FLAGS_E = -Wall -ansi -pedantic -o

#Executable names
NAME_L = test_list.out
NAME_H = test_hash.out 

#Link list implementation with the testfile
list: symtable.h symtablelist.o testsymtab.c
	$(CC) $(FLAGS_E) $(NAME_L) symtablelist.o testsymtab.c

#Produce symtablelist.o file
symtablelist.o: symtable.h symtablelist.c
	$(CC) $(FLAGS_O) symtablelist.c

#Link hashtable implementation with the testfile
hash: symtable.h symtablehash.o testsymtab.c
	$(CC) $(FLAGS_E) $(NAME_H) symtablehash.o testsymtab.c

#Produce symtablehash.o file
symtablehash.o: symtable.h symtablehash.c
	$(CC) $(FLAGS_O) symtablehash.c

#Delete every file created
clean:
	rm -f *.o
	rm -f *.out

