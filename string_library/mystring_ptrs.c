/*  File : mystring_ptr.c (Exercise 2)
    Name : Manos Chatzakis
    AM   : 4238
    eMail: csd4238@csd.uoc.gr
    This file implements library "mystring.h" using pointers.  */

#include "mystring.h"

/*  Return the length of the string str.
    It is a checked runtime error if str is NULL.  */
size_t ms_length(const char *str){

    const char *curr_str = str;

    assert(str != NULL);

    while(*curr_str){ /*Checks if *curr_str = '\0;*/
        curr_str++;
    }

    return curr_str - str; /*The size is the difference of mem cells*/
}

/*  Compare strings s1 and s2, return 0 if they are equal
    or a positive or negative value based on their code.
    It is a checked runtime error if s1 or s2 are NULL.  */
int ms_compare(const char *s1, const char *s2){

    const char *ptr_s1 = s1;
    const char *ptr_s2 = s2;

    /*Runtime error for NULL input*/
    assert(s1 != NULL);
    assert(s2 != NULL);

    /*Find the first different character if exists*/
    while(*ptr_s1 == *ptr_s2){
        if((! *ptr_s1)||(! *ptr_s2)){
            break;
        }
        ptr_s1++;
        ptr_s2++;
    }

    /*Return the difference between the characters*/
    return (*ptr_s1) - (*ptr_s2);
}

/*  Compare at most n characters from strings s1 and s2
    return 0 if they are equal or a positive or negative
    value based on they ASCII code.
    It is a checked runtinme error if s1 or s2 are NULL.  */
int ms_ncompare(const char *s1, const char *s2,size_t n){

    const char *ptr_s1 = s1;
    const char *ptr_s2 = s2;

    size_t bytes = 0U; /*byte counter*/

    /*Runtime error for NULL input*/
    assert(s1 != NULL);
    assert(s2 != NULL);

    /*Compare the first n bytes of the strings*/
    while(*ptr_s1 == *ptr_s2 && bytes < n-1){
        if((! *ptr_s1)||(! *ptr_s2)){
            break;
        }
        ptr_s1++;
        ptr_s2++;
        bytes++;
    }

     /*Return the difference between the characters*/
    return (*ptr_s1) - (*ptr_s2);
}

/*  Copy the string src to dest, returning a pointer to dest.
    It is a checked runtime error for dest or src to be NULL.  */
char *ms_copy(char *dest, const char *src){

    const char *ptr_src = src;

    /*Runtime error for NULL input*/
    assert(dest != NULL);
    assert(src != NULL);

    /*Copy the whole src string to dest*/
    while(*ptr_src){
        *dest = *ptr_src;
        ptr_src++;
        dest++;
    }

    *dest = '\0'; /*Add the NULL character*/

    return dest;
}

/*  Copy at most n characters from the string src to dest,
    returning a pointer to dest. without adding the terminating
    character at the end.
    It is a checked runtime error for dest or src to be NULL.  */
char *ms_ncopy(char *dest, const char *src,size_t n){

    const char *ptr_src = src;

    size_t bytes = 0U;

    /*Runtime error for NULL input*/
    assert(dest != NULL);
    assert(src != NULL);

    /*Copy the first n bytes of src string to dest*/
    while(*ptr_src && bytes<n){
        *(dest+bytes) = *(ptr_src+bytes);
        bytes++;
    }

    /*If the n input is bigger than the size of src
      the NULL character should be added*/
    if(bytes<n && *(src+bytes) == '\0'){
        *(dest+bytes) = '\0';
    }

    return dest;
}

/*  Append whole string src to dest returning a pointer to dest.
    It is a checked runtime error for src or dest to be NULL.  */
char *ms_concat(char *dest, const char *src){

    const char *ptr_src = src;

    size_t dest_letters = ms_length(dest);

    /*Runtime error for NULL input*/
    assert(dest != NULL);
    assert(src != NULL);

    /*Collide src to dest*/
    while(*ptr_src){
        *(dest+dest_letters) = *ptr_src;
        dest++;
        ptr_src++;
    }

    *(dest+dest_letters) = '\0';

    return dest;
}

/*  Append atmost n characters from string src to dest
    returning a pointer to dest.
    It is a checked runtime error for src or dest to be NULL.  */
char *ms_nconcat(char *dest, const char *src, size_t n){

    const char *ptr_src = src;

    size_t bytes = 0U;
    size_t dest_letters = ms_length(dest);

    /*Runtime error for NULL input*/
    assert(dest != NULL);
    assert(src != NULL);

    /*Collide the first n characters of src to dest*/
    while(*(ptr_src+bytes) && bytes<n){
        *(dest+dest_letters+bytes)= *(ptr_src+bytes);
        bytes++;
    }

    *(dest+bytes+dest_letters)= '\0';

    return dest;
}

/*  Find the first occurence of substring needle in the string
    haystack, returning a pointer to the beggining of the
    located substring or NULL if the substring in not found.
    It is a checked runtime error for haystack or needle to be NULL.  */
char *ms_search(const char haystack[],const char needle[]){

    size_t counter = 0;
    size_t size_needle = ms_length(needle);
    size_t size_hay = ms_length(haystack);

    /*Runtime error for NULL input*/
    assert(haystack != NULL); 
    assert(needle != NULL); 

    while(*(haystack+counter) && (size_needle+counter<=size_hay)){
        int j = 0;
        if((*(haystack+counter) == *(needle+j))){
            int i;
            for(i=counter; i<size_needle+counter; i++){
                if(*(needle+j) != *(haystack+i)){
                    break;
                }
                j++;
            }

            if(j == size_needle){
                return (char *)(haystack+counter);
            }

        }
        counter++;
    }
    return NULL;
}
