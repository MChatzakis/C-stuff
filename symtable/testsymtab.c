/*  File : testsymtab.c
    Name : Manos Chatzakis
    AM   : 4238
    eMail: csd4238@csd.uoc.gr
    This is a testfile.
*/

#include "symtable.h"
#include <stdio.h>

/*  pfApply version to test that map is working.  */
void defTest(const char *pcKey, void *pvValue, void *pvExtra){
    printf("    Function Applied.\n");

    return;
}

/*  pfApply version to print a structure with int values.  */
void printAsLUInt(const char *pcKey, void *pvValue, void *pvExtra){
    long unsigned int intVal =((long unsigned int) ((long unsigned int *)pvValue));
    printf("    (%s,%lu)\n",pcKey,intVal);

    return;
}

/*  pfApply age meter version.  */
void ageMeter(const char *pcKey, void *pvValue, void *pvExtra){

    long unsigned int v1 = ((long unsigned int) ((long unsigned int *)pvExtra));
    long unsigned int v2 = ((long unsigned int) ((long unsigned int *)pvValue));
    long unsigned int tod = v1 - v2;

    printf("    %s was born %lu years ago!\n",pcKey,tod);

    return;
}

int main(void){

    SymTable_T people; /*Holds pairs of scientists and their birth year*/

    /*Allocate memory for the symtables*/
    people = SymTable_new();

    /*Insert pairs to the first symtable*/
    printf("Inserting pairs of scientists and their birst year(1 success 0 failure):...\n");
    printf("    (%d ",      SymTable_put(people,"Alan Turing",      (void*)1912));
    printf("%d ",           SymTable_put(people,"John von Neumann", (void*)1903));
    printf("%d ",           SymTable_put(people,"Kurt Godel",       (void*)1906));
    printf("%d ",           SymTable_put(people,"Bertrand Russell", (void*)1872));
    printf("%d ",           SymTable_put(people,"Albert Einstein",  (void*)1879));
    printf("%d ",           SymTable_put(people,"Stephen Hawking",  (void*)1942));
    printf("%d ",           SymTable_put(people,"Nikola Tesla",     (void*)1856));
    printf("%d(Duplicate) ",SymTable_put(people,"Kurt Godel",       (void*)1856));
    printf("%d ",           SymTable_put(people,"Galileo Galilei",  (void*)1564));
    printf("%d ",           SymTable_put(people,"Charles Darwin",   (void*)1809));
    printf("%d ",           SymTable_put(people,"Dennis Ritchie",   (void*)1941));
    printf("%d ",           SymTable_put(people,"Marie Curie",      (void*)1867));
    printf("%d ",           SymTable_put(people,"Rosalind Franklin",(void*)1920));
    printf("%d(Duplicate) ",SymTable_put(people,"Galileo Galilei",  (void*)9000));
    printf("%d)\n",         SymTable_put(people,"Margaret Hamilton",(void*)1936));

    /*Print the symtable for debug. Comment this if you want*/
    printf("--PRINTING THE STRUCTURE WITH VOID POINTER VALUES--\n");
    SymTable_print(people);
    printf("--PRINTING ENDED--\n");

    /*Testing for the work of contain function*/
    printf("Searching pairs(1 yes 0 no):...\n");
    printf("    Is Stephen Hawking inside the structure?  -> %d\n",SymTable_contains(people,"Stephen Hawking"));
    printf("    Is Manos inside the structure?            -> %d\n",SymTable_contains(people,"Manos"));
    printf("    Is Alan Turing inside the structure?      -> %d\n",SymTable_contains(people,"Alan Turing"));
    printf("    Is Dennis Ritchie inside the structure?   -> %d\n",SymTable_contains(people,"Dennis Ritchie"));
    printf("    Is Yiannis inside the structure?          -> %d\n",SymTable_contains(people,"Yiannis"));
    printf("    Is Rosalind Franklin inside the structure?-> %d\n",SymTable_contains(people,"Rosalind Franklin"));

    /*Test remove function by deleting all non computer scientists*/
    printf("Deleting pairs(1 success 0 failure):...\n");
    printf("    (%d ",      SymTable_remove(people,"Albert Einstein"));
    printf("%d ",           SymTable_remove(people,"Stephen Hawking"));
    printf("%d ",           SymTable_remove(people,"Nikola Tesla"));
    printf("%d ",           SymTable_remove(people,"Galileo Galilei"));
    printf("%d(de) ",       SymTable_remove(people,"Galileo Galilei"));
    printf("%d ",           SymTable_remove(people,"Marie Curie"));
    printf("%d ",           SymTable_remove(people,"Rosalind Franklin"));
    printf("%d)\n",         SymTable_remove(people,"Charles Darwin"));

    /*Print the symtable for debug. Comment this if you want*/
    printf("--PRINTING THE STRUCTURE WITH VOID POINTER VALUES--\n");
    SymTable_print(people);
    printf("--PRINTING ENDED--\n");

    /*Printing the values.
      Notice that the print must be casted to lu
      to make sure that the sizes are the same(64bits).
    */
    printf("Seeking births...\n");
    printf("    Alan Turing was born in: %lu\n",        (long unsigned int) ((long unsigned int*) SymTable_get(people,"Alan Turing")));
    printf("    Dennis Ritchie was born in: %lu\n",     (long unsigned int) ((long unsigned int*) SymTable_get(people,"Dennis Ritchie")));
    printf("    Margaret Hamilton was born in: %lu\n",  (long unsigned int) ((long unsigned int*) SymTable_get(people,"Margaret Hamilton")));
    printf("    Galileo Galilei was born in: %lu\n",    (long unsigned int) ((long unsigned int*) SymTable_get(people,"Alan Turing")));

    /* Applying functions*/
    printf("Applying test function...\n");
    SymTable_map(people,defTest,(void *)1010);
    printf("Applying age meter function...\n");
    SymTable_map(people,ageMeter,(void *)2020);
    printf("Applying print as lu function...\n");
    SymTable_map(people,printAsLUInt,NULL);

    /*Free the memory*/
    SymTable_free(people);

    printf("Symtable freed. Testfile ended--\n");

    return 0;
}
