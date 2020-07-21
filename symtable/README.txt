**********************************************************
* HY255 - Assignment 3                                   *
* Manos Chatzakis, 4238	                                 *
* csd4238@csd.uoc.gr                                     *
**********************************************************

For testing reasons, a "SymTable_print" function has been added, and its used in the test file to show that both versions are working properly, saving all the bindings.

Also, lists (for list implementation) and sublists (for hash implementation) are sorted, to reduce put/remove/search procedures(however, complexity is still O(N)). 

Assignment took about 6 hours to complete.

Notes for the bonus part:
	Bonus part was working fine, expanding the table without causing any problems at execution. However, it had a minor memory leak when resising the table, thus I decided to remove it.
	The code for it its attached below (you may ignore this).
	

--IGNORE BELOW---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Code Bonus---:

/*  Creates a new symtable containing a hashtable of size buckets.
    Returns a pointer to the new symtable.  */
SymTable_T SymTable_size(unsigned int size){

    /*Works exactly as SymTable_new but with non fixed size*/
    SymTable_T newTable;
    
    unsigned int hashIndex;
    
    newTable = malloc(sizeof(SymTable));

    newTable->hashtable = malloc(size*sizeof(HashInfo));

    for(hashIndex = 0U; hashIndex<size; hashIndex++){
        newTable->hashtable[hashIndex] = malloc(sizeof(HashInfo));
        (newTable->hashtable[hashIndex])->length = 0U;
    }

    newTable->buckets = size;
    newTable->pairs = 0U;

    return newTable;
}

/*  Inserts pairs to a temporary list.  */
void temp_list_insert(Pair_T* head,void* val,char* key){

    Pair_T newPair = malloc(sizeof(Pair));
    
    newPair->value = val;
    newPair->key = malloc(strlen(key)+1);
    
    strcpy(newPair->key,key);
    
    newPair->next = *head; 
    
    *head = newPair;
    
    return;
}

/*  Frees the memory allocated for the temporary list.  */
void temp_list_free(Pair_T head){
   
    Pair_T tmp;

    while(head!=NULL){
        
        tmp = head;
        head = head->next;
    

        free(tmp->key);
        tmp->key = NULL;

        tmp->value = NULL;

        free(tmp);

        head = head->next;
    } 
}

/*  Expands the size of symtable to a specific new size.  */
void SymTable_expand(SymTable_T oSymTable){

    Pair_T P;
    Pair_T tmpHead;
    Pair_T tmp = NULL;

    unsigned int i;

    unsigned int newSize = SymTable_getNewSize(oSymTable);

    for(i=0; i<(oSymTable->buckets); i++){
        if((oSymTable->hashtable[i])->length>0){
            P = (oSymTable->hashtable[i])->head;
            while(P!=NULL){
                temp_list_insert(&tmpHead,P->value,P->key);
                P = P->next;
            }
        }
    }
  
    for(i=0; i<oSymTable->buckets; i++){

        P = (oSymTable->hashtable[i])->head;

        while(P!=NULL){
            
            tmp = P;
            P = P->next;

            free(tmp->key);
            free(tmp);
        }

        free(oSymTable->hashtable[i]);
    }

    free(oSymTable->hashtable);

    oSymTable->hashtable = malloc(newSize*sizeof(HashInfo));
    oSymTable->buckets = newSize;
    oSymTable->pairs = 0U;

    for(i = 0; i<newSize; i++){
        oSymTable->hashtable[i] = malloc(sizeof(HashInfo));
        (oSymTable->hashtable[i])->length = 0U;
        (oSymTable->hashtable[i])->head = NULL;
    }

    tmp = tmpHead;
    while(tmp!=NULL){
       // SymTable_put(oSymTable,tmp->key,tmp->value);
        tmp = tmp->next;
    }

    temp_list_free(tmpHead);
}
