# Manos Chatzakis
# csd4238@csd.uoc.gr

#Default Compiler
CC = gcc

#Flags and args
FL = -o

#Shell Name
LIB = -pthread
NAME = take_away
S_NAME = take_away.c

all: $(S_NAME)
	$(CC) $(LIB) $(FL) $(NAME) $(S_NAME)

clean:
	rm -f $(NAME)

run: $(S_NAME)
	$(CC) $(LIB) $(FL) $(NAME) $(S_NAME)
	./$(NAME)
