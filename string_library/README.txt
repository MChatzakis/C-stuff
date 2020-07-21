**********************************************************
* HY255 - Assignment 2                                   *
* Manos Chatzakis, 4238	                                 *
* csd4238@csd.uoc.gr                                     *
**********************************************************

Answer 1:
	These functions could use sizeof and ms_length
	(and assertions)to check if the dest pointer
	has enough memory to store the updated string.
	However, as the	classic "string.h" functions 
	do not do protect the user from these mistakes,
	there is no reason for our library to do so.

Answer 2:
	These function could use assertions to
	check if the bytes to copy is a positive 
	number, but n is an unsigned(type size_t).
	This means that even if the input is "negative"
	the system will take it's unsigned value
	depending on 2's complement.

All in all, we could include every possible error check to
protect the user from getting runtime errors and seg faults.

But when the user uses the library, he may know how the 
functions work and their specifications, in order
to use them properly.

However, our own defined "mystring.h" functions 
protect the user from some mistakes (check the code).

The work of every function is the same as described in
the manual page of unix.(man string)

The exercise took around 4 hours to complete.
