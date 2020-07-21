#########################################################################
# Name : Manos Chatzakis                                                #
# AM   : 4238                                                           #
# eMail: csd4238@csd.uoc.gr                                             #
# Use this Makefile to produce the executable program for               #
# sudoku of assignment 4.                                               #
#########################################################################

#Default compiler
CC = gcc

#Compilation flags for .o and .out files
FLAGS_O = -Wall -ansi -pedantic -c
FLAGS_E = -Wall -ansi -pedantic -o

#Executable name
NAME = sudoku

#Produce the sudoku executable
sudoku: sudoku.h sudoku.c grid.h grid.o
	$(CC) $(FLAGS_E) $(NAME) grid.o sudoku.c

#Produce the .o file for linking
grid.o: grid.h grid.c
	$(CC) $(FLAGS_O) grid.c

#Delete every file created
clean:
	rm -f *.o
	rm -f sudoku

