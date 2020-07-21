**********************************************************
* HY255 - Assignment 1                                   *
* Manos Chatzakis, 4238	                                 *
* csd4238@csd.uoc.gr                                     *
**********************************************************

NOTE: The test files should be saved with ISO 8859-7 in order to run properly.

1. This txt file contains general information about the translate.c file provided for the first assignment.

2. Compilation is done following the site's instructions, etc. for unix:
gcc -Wall -ansi -pedantic -o translate translate.c and then run ./translate < TESTFILE [optional] > OUTPUTFILE
Running the file in a different manner is also possible - as it takes the input from the standard input. Thats means that you can use all the methods described in the site to run the code. 

3. The code follows the instructions given in the lecture.

4. The task completed in about 5 to 6 hours, plus the testing.

5. I also provided some tests saved in ISO 8858-7.

6. The array of pointers to functions bonus completed.

7. English and other symbols supported from the default terminal ISO are not translated. They are just re-printed.

NOTES [about running and compilation]:
I tried the program in multiple systems:
	-> Windows Command Line using gcc commands (and windows terminal(preview mode))
	-> Linux Ubuntu Subsystem on windows computer using gcc
	-> Linux Ubuntu pc using gcc
	-> In csd's computer's ("milo") using their own gcc version.

	In all the cases above, the tests of folder "test" run properly, without problems.
