/*  File : mystring_ars.c (Exercice 2)
    Name : Manos Chatzakis
    AM   : 4238
    eMail: csd4238@csd.uoc.gr
    This file implements library "mystring.h" using arrays.  */

#include "mystring.h"

/*  Return the length of the string str.
    It is a checked runtime error if str is NULL.  */
size_t ms_length(const char str[]){

    size_t str_size = 0U;  /*The size of the string*/

    assert(str != NULL); /*Runtime error for NULL input*/

    /*Count the size of the string*/
    while(str[str_size]!='\0'){ /*Count only the normal characters*/
        str_size++;
    }

    return str_size; /*Return the string's size*/
}

/*  Compare strings s1 and s2, return 0 if they are equal
    or a positive or negative value based on their code.
    It is a checked runtime error if s1 or s2 are NULL.  */
int ms_compare(const char s1[], const char s2[]){

    size_t counter = 0; /*The index of the current characters*/

    /*Runtime error for NULL input*/
    assert(s1 != NULL);
    assert(s2 != NULL);

    /*Find the first different character or the null character*/
    while(s1[counter] == s2[counter]){

        /*Quit the loop if at least of one strings are over*/
        if(s1[counter] == '\0'|| s2[counter] == '\0'){
            break;
        }

        counter++;
    }

    return s1[counter] - s2[counter]; /*Return the difference of characters*/
}

/*  Compare at most n characters from strings s1 and s2
    return 0 if they are equal or a positive or negative
    value based on they ASCII code.
    It is a checked runtinme error if s1 or s2 are NULL.  */
int ms_ncompare(const char s1[], const char s2[], size_t n){

    size_t bytes = 0U; /*The byte counter*/

    /*Runtime error for NULL input*/
    assert(s1 != NULL);
    assert(s2 != NULL);

    /*Iterate the strings till the n-1 character is found*/
    while(s1[bytes] == s2[bytes] && bytes < n-1){

        /*Quit the loop if at least of one strings are over*/
        if(s1[bytes] == '\0'|| s2[bytes] == '\0'){
            break;
        }

        bytes++;
    }

    return s1[bytes] - s2[bytes]; /*Return the difference of characters*/
}

/*  Copy the string src to dest, returning a pointer to dest.
    It is a checked runtime error for dest or src to be NULL.  */
char *ms_copy(char dest[],const char src[]){

    size_t counter = 0U; /*The index of the current characters*/

    /*Runtime error for NULL input*/
    assert(dest != NULL);
    assert(src != NULL);

    /*Iterate the src string and copy it to dest*/
    while(src[counter]!= '\0'){
        dest[counter] = src[counter];
        counter++;
    }

    dest[counter] = '\0'; /*Add the NULL character as it is a string*/

    return dest;
}

/*  Copy at most n characters from the string src to dest,
    returning a pointer to dest. without adding the terminating
    character at the end.
    It is a checked runtime error for dest or src to be NULL.  */
char *ms_ncopy(char dest[],const char src[],size_t n){

    size_t bytes = 0U; /*The byte counter*/

    /*Runtime error for NULL input*/
    assert(dest != NULL);
    assert(src != NULL);

    /*Iterate the src string copy the n bytes to dest*/
    while(src[bytes]!= '\0' && bytes<n){
        dest[bytes] = src[bytes];
        bytes++;
    }

    /*If the n input is bigger than the size of src
      the NULL character should be added
      (this is added for some corner cases)*/
    if(bytes<n && src[bytes] == '\0'){
        dest[bytes] = '\0';
    }

    return dest;
}

/*  Append whole string src to dest returning a pointer to dest.
    It is a checked runtime error for src or dest to be NULL.  */
char *ms_concat(char dest[], const char src[]){

    size_t counter = 0U; /*The index of the current characters*/
    size_t dest_letters = ms_length(dest); /*Letters to skip*/

    /*Runtime error for NULL input*/
    assert(dest != NULL);
    assert(src != NULL);

    /*Iterate src and collide its characters to dest*/
    while(src[counter] != '\0'){
        dest[dest_letters+counter] = src[counter];
        counter++;
    }

    /*Add the NULL character because it is a string*/
    dest[counter+dest_letters] = '\0';

    return dest;
}

/*  Append atmost n characters from string src to dest
    returning a pointer to dest.
    It is a checked runtime error for src or dest to be NULL.  */
char *ms_nconcat(char dest[], const char src[], size_t n){

    size_t bytes = 0U; /*The byte counter*/
    size_t dest_letters = ms_length(dest); /*Letters to skip*/

    /*Runtime error for NULL input*/
    assert(dest != NULL);
    assert(src != NULL);

    /*Iterate src and collide its first n characters to dest*/
    while(src[bytes] != '\0' && bytes<n){
        dest[dest_letters+bytes] = src[bytes];
        bytes++;
    }

    /*Add the NULL character because it is a string*/
    dest[bytes+dest_letters] = '\0';

    return dest;
}

/*  Find the first occurence of substring needle in the string
    haystack, returning a pointer to the beggining of the
    located substring or NULL if the substring in not found.
    It is a checked runtime error for haystack or needle to be NULL.  */
char *ms_search(const char haystack[],const char needle[]){

    size_t counter = 0U; /*The index of the current characters*/
    size_t size_needle = ms_length(needle);
    size_t size_hay = ms_length(haystack);

    /*Runtime error for NULL input*/
    assert(haystack != NULL);
    assert(needle != NULL);

    /*Seek the substring needle*/
    while(haystack[counter] != '\0' && (size_needle+counter<=size_hay)){
        int j = 0;
        if((haystack[counter] == needle[j])){
            int i;
            for(i=counter; i<size_needle+counter; i++){
                if(needle[j] != haystack[i]){
                    break;
                }
                j++;
            }

            if(j == size_needle){ /*If the substring is found*/
                /*Return a pointer to the first occurence of the substring inside haystack*/
                return (char*)(haystack+counter);
            }
        }
        counter++;
    }

    /*Return NULL if the substring is not found*/
    return NULL;
}
