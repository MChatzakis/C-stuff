*************************************************
* Name: Manos Chatzakis                         *
* Mail: csd4238@csd.uoc.gr                      *
*************************************************

This README file describes the implementation of the c linux shell for assignment 1.

To use it, try "make all" and then "./sh345", or "make run". 

The shell supports:
	- Simple command execution, for the commands of /usr/bin/ and /bin/. 
	- Hardcoded commands: "cd" and "exit".
	- Pipelined commands execution.
	- Redirection to and from files.
	- CTRL H, CTRL C shortcuts (The code for CTRL S and Q is in comments).

Information:
	- Max supported input is 1024, max command size is 100 and max arguments are also 100. All those can be easily changed.
	- For redirection: Multiple redirection is supported, but input(output) file is the last one entered. (Cannot write output to many files).
	- Shortcuts CTRL S and Q are already implemented using the default terminal shortcuts, use stty -ixon.
