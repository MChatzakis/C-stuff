# Manos Chatzakis
# csd4238@csd.uoc.gr

#Default Compiler
CC = gcc

#Flags and args
FL = -o

#Shell Name
NAME = shell

all: shell.c
	$(CC) $(FL) $(NAME) shell.c

clean:
	rm -f $(NAME)

run: shell.c
	$(CC) $(FL) $(NAME) shell.c
	./$(NAME)
