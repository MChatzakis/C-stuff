/*  File : symtablelist.c
    Name : Manos Chatzakis
    AM   : 4238
    eMail: csd4238@csd.uoc.gr
    This file contains the implementation of library "symtable.h"
    using linked list.
*/

#include "symtable.h"
#include <stdio.h>

/*  Bindings are represented as pairs of keys and values.  */
typedef struct Pair{
    void* value;
    char* key;
    struct Pair *next;
}Pair;

/*  Setting the pointers to pairs to be declared as Pair_T.  */
typedef struct Pair *Pair_T;

/*  Symtables contain the head of the list holding the pairs
    and the number of total bindings.  */
typedef struct SymTable{
    Pair* head;     /*Like a stack*/
    unsigned int length;
}SymTable;

/*  Returns a new empty symtable.  */
SymTable_T SymTable_new(void){

    SymTable_T newTable = NULL;

    /*Allocate memory for the fields of Symtable.*/
    newTable = malloc(sizeof(SymTable));

    /*Make sure allocation made*/
    if(newTable == NULL){
        printf("ERROR\n");
        exit(1);
    }

    /*Initialize the fields.*/
    newTable->head = NULL;
    newTable->length = 0U;

    return newTable;
}

/*  Deallocates the memory allocated for oSymTable.
    If the oSymTable is NULL, the function does nothing.  */
void SymTable_free(SymTable_T oSymTable){

    /*Pointer to iterate the list.*/
    Pair_T P;

    /*Previous pointer to free the nodes.*/
    Pair_T Prev = NULL;

    /*Return if Symtable is NULL.*/
    if(oSymTable == NULL){
        return;
    }

    P = oSymTable->head;

    /*Iterate the list to free the nodes.*/
    while(P!=NULL){

        /*Keep the previous node and proceed.*/
        Prev = P;
        P = P->next;

        /*Free the space allocated for the string key.*/
        free(Prev->key);
        Prev->key = NULL;

        /*Free the space allocated for the node.*/
        free(Prev);
        Prev = NULL;
    }

    /*Free The space allocated for the Symtable struct.*/
    oSymTable->length = 0;
    oSymTable->head = NULL;

    free(oSymTable);
    oSymTable = NULL;

    return;
}

/*  Returns the number of bindings the oSymTable contains.
    It is a checked runtime exception for oSymTable to be NULL.  */
unsigned int SymTable_getLength(SymTable_T oSymTable){

    /*Runtime error if Symtable is NULL*/
    assert(oSymTable!=NULL);

    return oSymTable->length;
}

/*  Inserts a new binding with key pcKey and value pvValue.
    If the key does not exist, the function returns 1(TRUE).
    If the key already exists, the function returns 0(FALSE).
    It is a checked runtime error for oSymTable or pcKey to be NULL.  */
int SymTable_put(SymTable_T oSymTable,const char *pcKey,const void *pvValue){

    /*Pointer to iterate the list.*/
    Pair_T P;

    /*Previous node pointer.*/
    Pair_T Prev = NULL;

    /*Pointer to the new node*/
    Pair_T newPair;

    /*Runtime error if input is NULL*/
    assert(pcKey != NULL);
    assert(oSymTable != NULL);

    P = oSymTable->head;

    /*Iterate the list to find the right place to
      insert the new binding sorted.*/
    while(P!=NULL && strcmp(pcKey,P->key)>0){
        Prev = P;
        P = P->next;
    }

    /*Check for duplicate keys.*/
    if(P!=NULL && strcmp(pcKey,P->key)==0){
        return 0;
    }

    /*Allocate memory for the new node.*/
    newPair = malloc(sizeof(Pair));

    /*Allocate memomory to store the key.*/
    newPair->key = malloc(strlen(pcKey)+1);
    strcpy(newPair->key,pcKey);

    /*Initialize the fields of the new node.*/
    newPair->value = (void *)pvValue;
    newPair->next = P;

    /*Connect the new node to the list.*/
    if(Prev == NULL){
        oSymTable->head = newPair;
    }
    else{
        Prev->next = newPair;
    }

    /*Increment the number of pairs the list holds.*/
    oSymTable->length = oSymTable->length + 1;

    return 1;
}

/*  Removes the binding with key pcKey from oSymTable.
    If the binding with key pcKey exists, the function deletes it and
    returns 1(TRUE).
    If the binding with key pcKey does not exist, the function
    does nothing and returns 0.
    It is a checked runtime error for oSymTable or pcKey to be NULL.  */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey){

    /*Pointer to iterate the list*/
    Pair_T P;

    /*Pointer to the previous node.*/
    Pair_T Prev = NULL;

    /*Runtime error if the input is NULL*/
    assert(pcKey != NULL);
    assert(oSymTable != NULL);

    P = oSymTable->head;

    /*Iterate the sorted linked list to find the pair*/
    while(P!=NULL && strcmp(pcKey,P->key)>0){
        Prev = P;
        P = P->next;
    }

    /*If the pair does not exist return*/
    if(P == NULL || strcmp(pcKey,P->key) != 0){
        return 0;
    }

    /*Remove the node from the list*/
    if(Prev == NULL){
        oSymTable->head = P->next;
    }
    else{
        Prev->next = P->next;
    }

    /*Free the memory allocated for the removed pair*/
    free(P->key);
    P->key = NULL;

    P->value = NULL;
    P->next = NULL;

    free(P);
    P = NULL;

    oSymTable->length = oSymTable->length - 1;

    return 1;
}

/*  Returns 1(TRUE) if the binding with key pcKey exists in oSymTable.
    If it does not exist returns 0(FALSE).
    It is a checked runtime error for oSymTable or pcKey to be NULL.  */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey){

    /*Pointer to iterate the list.*/
    Pair_T P;

    /*Runtime error for NULL input.*/
    assert(pcKey != NULL);
    assert(oSymTable != NULL);

    P =  oSymTable->head;

    /*Search for the pair with given key.*/
    while(P!=NULL && strcmp(pcKey,P->key)>0){
        P = P->next;
    }

    /*Return 0 if the pair is not found.*/
    if(P == NULL || strcmp(pcKey,P->key) != 0){
        return 0;
    }

    return 1;
}

/*  Returns the value of binding with key pcKey.
    If the binding exists in oSymTable it returns its value.
    If the binding does not exist in oSymTable returns NULL.
    It is a checked runtime error for oSymTable or pcKey to be NULL.  */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey){

    /*Pointer to iterate the list.*/
    Pair_T P;

    /*Runtime error for NULL input.*/
    assert(pcKey != NULL);
    assert(oSymTable != NULL);

    P = oSymTable->head;

    /*Search for the pair with given key.*/
    while(P!=NULL && strcmp(pcKey,P->key)>0){
        P = P->next;
    }

    /*Return NULL if the pair is not found.*/
    if(P == NULL || strcmp(pcKey,P->key) != 0){
        return NULL;
    }

    return (P->value);
}

/*  Applies pfApply to all bindings of oSymTable.
    It is a checked runtime error for oSymTable or pfApply to be NULL.  */
void SymTable_map(SymTable_T oSymTable,
                    void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
                    const void *pvExtra){

    /*Pointer to iterate the list*/
    Pair_T P;

    /*Cast pcExtra because pvExtra is const*/
    void *extra = (void *)pvExtra;

    /*Runtime error for NULL input*/
    assert(pfApply != NULL);
    assert(oSymTable != NULL);

    P = oSymTable->head;


    /*Iterate the whole list*/
    while(P!=NULL){

        /*Aplly this function to every pair*/
        pfApply(P->key,P->value,extra);
        P = P->next;
    }

    return;
}

/*  Prints the whole SymTable.
    This is mostly used for debugging.
    It is a checked runtime error for oSymtable to be NULL.
    Values are displayed as void pointers (%p).  */
void SymTable_print(SymTable_T oSymTable){

    /*Pointer to iterate the list.*/
    Pair_T P;

    /*Runtime error for NULL input.*/
    assert(oSymTable != NULL);

    P = oSymTable->head;

    /*Print the SymTable*/
    printf("Symtable with size %u:\n",SymTable_getLength(oSymTable));

    while(P!=NULL){
        printf("    (%s,%p)\n",P->key,P->value);
        P = P->next;
    }

    return;
}
