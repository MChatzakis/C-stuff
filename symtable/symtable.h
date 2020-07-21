/*  File : symtable.h
    Name : Manos Chatzakis
    AM   : 4238
    eMail: csd4238@csd.uoc.gr
    This file is the interface of a Symtable ADT.
    It contains pairs of keys and values.
*/

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*Setting the pointers to SymTables to be declared as SymTable_T.*/
typedef struct SymTable *SymTable_T; 

/*  Returns a new empty symtable.  */
SymTable_T SymTable_new(void); 

/*  Deallocates the memory allocated for oSymTable.
    If the oSymTable is NULL, the function does nothing.  */
void SymTable_free(SymTable_T oSymTable); 

/*  Returns the number of bindings the oSymTable contains.  
    It is a checked runtime exception for oSymTable to be NULL.  */
unsigned int SymTable_getLength(SymTable_T oSymTable);

/*  Inserts a new binding with key pcKey and value pvValue.
    If the key does not exist, the function returns 1(TRUE).
    If the key already exists, the function returns 0(FALSE).
    It is a checked runtime error for oSymTable or pcKey to be NULL.  */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue); 

/*  Removes the binding with key pcKey from oSymTable.
    If the binding with key pcKey exists, the function deletes it and
    returns 1(TRUE).
    If the binding with key pcKey does not exist, the function
    does nothing and returns 0.
    It is a checked runtime error for oSymTable or pcKey to be NULL.  */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey);

/*  Returns 1(TRUE) if the binding with key pcKey exists in oSymTable.
    If it does not exist returns 0(FALSE).
    It is a checked runtime error for oSymTable or pcKey to be NULL.  */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey);

/*  Returns the value of binding with key pcKey.
    If the binding exists in oSymTable it returns its value.
    If the binding does not exist in oSymTable returns NULL. 
    It is a checked runtime error for oSymTable or pcKey to be NULL.  */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

/*  Applies pfApply to all bindings of oSymTable.
    It is a checked runtime error for oSymTable or pfApply to be NULL.  */
void SymTable_map(SymTable_T oSymTable,
                    void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
                    const void *pvExtra);

/*  Prints the whole SymTable.
    This is mostly used for debugging.
    It is a checked runtime error for oSymtable to be NULL.
    This is an optional function.  */
void SymTable_print(SymTable_T oSymTable);    
