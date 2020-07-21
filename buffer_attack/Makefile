########################################################
# Name: Manos Chatzakis                                #
# AM  : 4238                                           #
# Mail: csd4238@csd.uoc.gr                             #
# Makefile -Use to produce the input files.            #
########################################################

#Default compiler
CC = gcc

#Flags
FL = -Wall -ansi -pedantic -o

#Produce all three input files
all: data3 data6 data9

#Produce data3 executable
data3ex: createdata3.c
	$(CC) $(FL) data3ex createdata3.c

#Run hello with data3 as input
run3: data3 hello
	hello < data3

#Run hello with data6 as input
run6: data6 hello
	hello < data6

#Run hello with data9 as input
run9: data9 hello
	hello < data9

#Produce data3 file
data3: data3ex
	data3ex > data3

#Produce data6 executable
data6ex: createdata6.c
	$(CC) $(FL) data6ex createdata6.c

#Produce data6 file
data6: data6ex
	data6ex > data6

#Produce data9 executable
data9ex: createdata9.c
	$(CC) $(FL) data9ex createdata9.c

#Produce data9 file
data9: data9ex
	data9ex > data9

#Delete every file created
clean:
	rm -f data3
	rm -f data6
	rm -f data9
	rm -f data3ex
	rm -f data6ex
	rm -f data9ex
