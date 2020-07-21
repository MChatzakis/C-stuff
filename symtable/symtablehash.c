/*  File : symtablehash.c
    Name : Manos Chatzakis
    AM   : 4238
    eMail: csd4238@csd.uoc.gr
    This file contains the implementation of library "symtable.h"
    using hashtable.
*/

#include "symtable.h"
#include <stdio.h>

/*  The default number of buckets the hashtable can hold.  */
#define BUCKETS 509

/*  A default constant for hashfunction*/
#define HASH_MULTIPLIER 65599

/*  Bindings are represented as pairs of keys and values.  */
typedef struct Pair{
    void* value;
    char* key;
    struct Pair *next;
}Pair;

/*  Setting the pointers to pairs to be declared as Pair_T.  */
typedef struct Pair *Pair_T;

/*  Every cell of the hash table is a struct containing a pointer to the
    head of the sublist of bindings and the size of that list.  */
typedef struct HashInfo{
    Pair_T head;
    unsigned int length;
}HashInfo;

/*  Setting the pointers to HashInfo to be declared as Hash_T.  */
typedef struct HashInfo *Hash_T;

/*  Symtables contain the hashtable array and the number
    of total pairs that they have.  */
typedef struct SymTable{
    Hash_T* hashtable; /*Array of pointers to HashInfo structures*/
    unsigned int pairs;
    unsigned int buckets;
}SymTable;

/* Return a hash code for pcKey. */
static unsigned int SymTable_hash(const char *pcKey){

    size_t ui;

    unsigned int uiHash = 0U;

    for (ui = 0U; pcKey[ui] != '\0'; ui++){
        uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
    }

    return uiHash;
}

/*  Returns a new empty symtable.  */
SymTable_T SymTable_new(void){

    SymTable_T newTable;

    size_t hashIndex;

    newTable = malloc(sizeof(SymTable));

    /*Access hashtable[i]*/
    newTable->hashtable = malloc(BUCKETS*sizeof(HashInfo));

    /*Create the hashtable*/
    for(hashIndex = 0U; hashIndex<BUCKETS; hashIndex++){

        /*Allocate memory for every cell of the hashtable. */
        newTable->hashtable[hashIndex] = malloc(sizeof(HashInfo));
        (newTable->hashtable[hashIndex])->length = 0U;
        (newTable->hashtable[hashIndex])->head = NULL;
    }

    newTable->buckets = BUCKETS;
    newTable->pairs = 0U;

    return newTable;
}

/*  Deallocates the memory allocated for oSymTable.
    If the oSymTable is NULL, the function does nothing.  */
void SymTable_free(SymTable_T oSymTable){

    /*Iteration pointers*/
    Hash_T R;

    Pair_T P;
    Pair_T Q;
    Pair_T tmp;

    /*Array indexing*/
    unsigned int index;

    /*Error check*/
    if(oSymTable == NULL){
        return;
    }

    /*Iterate hashtable and free every node of every sublist*/
    for(index = 0U; index<(oSymTable->buckets); index++){

        R = oSymTable->hashtable[index];
        P = R->head;
        Q = P;

        while(Q!=NULL){

            tmp = Q;

            Q = Q->next;

            free(tmp->key);
            tmp->key = NULL;

            free(tmp);
            tmp=NULL;
        }

        /*After the sublist is freed,
          the cell is freed too*/
        free(R);
        R = NULL;

    }

    /*Free the rest fields allocated with malloc*/
    free(oSymTable->hashtable);
    oSymTable->hashtable = NULL;

    free(oSymTable);

    return;
}

/*  Returns the number of bindings the oSymTable contains.
    It is a checked runtime exception for oSymTable to be NULL.  */
unsigned int SymTable_getLength(SymTable_T oSymTable){

    /*Runtime error for NULL input*/
    assert(oSymTable != NULL);

    return oSymTable->pairs;
}

/*  Inserts a new binding with key pcKey and value pvValue.
    If the key does not exist, the function returns 1(TRUE).
    If the key already exists, the function returns 0(FALSE).
    It is a checked runtime error for oSymTable or pcKey to be NULL.  */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){

    /*Array indexing variable*/
    unsigned int index;

    /*Iteration pointers*/
    Pair_T P;
    Pair_T Prev = NULL;

    /*Pointer to the new pair*/
    Pair_T newPair;

    /*Runtime error for NULL input*/
    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    /*Get the index of sublist*/
    index = SymTable_hash(pcKey)%(oSymTable->buckets);

    P = (oSymTable->hashtable[index])->head;

    /*Iterate the sorted sublist*/
    while(P!=NULL && strcmp(pcKey,P->key)>0){
        Prev = P;
        P = P->next;
    }

    /*Check for duplicate pairs*/
    if(P!=NULL && strcmp(pcKey,P->key)==0){
        return 0;
    }

    /*Allocate memory for the new pair*/
    newPair = malloc(sizeof(Pair));
    newPair->key = malloc(strlen(pcKey)+1);

    /*Initialize the fields*/
    strcpy(newPair->key,pcKey);
    newPair->value = (void *)pvValue;
    newPair->next = P;

    /*Connect the new pair to the list*/
    if(Prev == NULL){
       (oSymTable->hashtable[index])->head = newPair;
    }
    else{
        Prev->next = newPair;
    }

    /*Increment the pair counters*/
    (oSymTable->hashtable[index])->length = (oSymTable->hashtable[index])->length + 1;
    oSymTable->pairs = oSymTable->pairs + 1;

    /*version 1 of expand*/
    /*if((oSymTable->hashtable[index])->length == oSymTable->buckets){
        BONUS
    }*/

    /*Expand if the following if evaluates to true
    if(oSymTable->pairs == oSymTable->buckets && oSymTable->buckets < MAX_BUCKETS){
       BONUS
    }*/

    return 1;
}

/*  Returns 1(TRUE) if the binding with key pcKey exists in oSymTable.
    If it does not exist returns 0(FALSE).
    It is a checked runtime error for oSymTable or pcKey to be NULL.  */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey){

    /*Variable to index the hashtable*/
    unsigned int index;

    /*Iteration pointer*/
    Pair_T P;

    /*Runtime error for NULL input*/
    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    /*Get the index of sublist*/
    index = SymTable_hash(pcKey)%(oSymTable->buckets);

    P = (oSymTable->hashtable[index])->head;

    /*Iterate the list to find the pair with the desired key*/
    while(P!=NULL && strcmp(pcKey,P->key)>0){
        P = P->next;
    }

    /*Return whether the key exist or not*/
    if(P==NULL || strcmp(pcKey,P->key)!=0){
        return 0;
    }

    return 1;
}

/*  Returns the value of binding with key pcKey.
    If the binding exists in oSymTable it returns its value.
    If the binding does not exist in oSymTable returns NULL.
    It is a checked runtime error for oSymTable or pcKey to be NULL.  */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey){

    /*Variable to index the hashtable*/
    unsigned int index;

    /*Iteration pointer*/
    Pair_T P;

    /*Runtime error for NULL input*/
    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    /*Get the index of sublist*/
    index = SymTable_hash(pcKey)%(oSymTable->buckets);

    P = (oSymTable->hashtable[index])->head;

    /*Iterate the list to find the pair with the desired key*/
    while(P!=NULL && strcmp(pcKey,P->key)>0){
        P = P->next;
    }

    /*Return NULL if the pair does not exist*/
    if(P==NULL || strcmp(pcKey,P->key)!=0){
        return NULL;
    }

    return P->value;
}

/*  Removes the binding with key pcKey from oSymTable.
    If the binding with key pcKey exists, the function deletes it and
    returns 1(TRUE).
    If the binding with key pcKey does not exist, the function
    does nothing and returns 0.
    It is a checked runtime error for oSymTable or pcKey to be NULL.  */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey){

    /*Variable to index the hashtable*/
    unsigned int index;

    /*Iteration pointers*/
    Pair_T P;
    Pair_T Prev = NULL;

    /*Runtime error for NULL input*/
    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    /*Get the index of sublist*/
    index = SymTable_hash(pcKey)%(oSymTable->buckets);

    P = (oSymTable->hashtable[index])->head;

    /*Iterate the list to find the pair with pcKey*/
    while(P!=NULL && strcmp(pcKey,P->key)>0){
        Prev = P;
        P = P->next;
    }

    /*Check if the pair is found*/
    if(P == NULL || strcmp(pcKey,P->key) != 0){
        return 0;
    }

    /*Delete the pair from the sublist*/
    if(Prev == NULL){
        (oSymTable->hashtable[index])->head = P->next;
    }
    else{
        Prev->next = P->next;
    }

    /*Free the memory allocated for the pair*/
    free(P->key);
    P->key = NULL;

    free(P);
    P = NULL;

    /*Decrease the pair counters*/
    (oSymTable->hashtable[index])->length--;
    oSymTable->pairs--;

    return 1;
}

/*  Applies pfApply to all bindings of oSymTable.
    It is a checked runtime error for oSymTable or pfApply to be NULL.  */
void SymTable_map(SymTable_T oSymTable,
                    void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
                    const void *pvExtra){

    /*Iteration pointer*/
    Pair_T P;

    /*Variable to index the hashtable*/
    size_t index;

    /*Cast is needed as pvExtra is a constant*/
    void *extra = (void *)pvExtra;

    /*Runtime error for NULL input*/
    assert(oSymTable != NULL);
    assert(pfApply != NULL);

    /*Iterate and apply the function to every pair*/
    for(index = 0U; index<(oSymTable->buckets); index++){

        P = (oSymTable->hashtable[index])->head;

        while(P!=NULL){
            pfApply(P->key,P->value,extra); /*Applying the function*/
            P = P->next;
        }

    }

    return;
}

/*  Prints the whole SymTable.
    This is mostly used for debugging.
    It is a checked runtime error for oSymtable to be NULL.  */
void SymTable_print(SymTable_T tab){

    /*Variable to index the hashtable*/
    unsigned int i;

    /*Iteration pointer*/
    Pair_T P;

    /*Runtime error for NULL input*/
    assert(tab != NULL);

    /*Printing the symtable*/
    printf("Hashtable with buckets %u holding %u pairs:\n",tab->buckets,SymTable_getLength(tab));
    for(i = 0; i<(tab->buckets); i++){

        /*Print only the non-empty sublists*/
        if((tab->hashtable[i])->length>0) {

            printf("[%u].Sublist with size: %u contains:\n",i,(tab->hashtable[i])->length);

            P = (tab->hashtable[i])->head;

            /*Iterate and print the sublist*/
            while(P!=NULL){
                printf("    (%s,%p)\n",P->key,P->value);
                P = P->next;
            }

        }
    }
    return;
}

