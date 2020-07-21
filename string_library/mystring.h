/*  File : mystring.h (Exercise 2)
    Name : Manos Chatzakis
    AM   : 4238
    eMail: csd4238@csd.uoc.gr  */

#include <stdio.h>
#include <stddef.h>
#include <assert.h>

/*  Compare strings s1 and s2, return 0 if they are equal
    or a positive or negative value based on their code.
    It is a checked runtime error if s1 or s2 are NULL.  */
int ms_compare(const char *s1,const char *s2);

/*  Compare at most n characters from strings s1 and s2
    return 0 if they are equal or a positive or negative
    value based on they ASCII code.
    It is a checked runtinme error if s1 or s2 are NULL.  */
int ms_ncompare(const char *s1,const char *s2,size_t n);

/*  Return the length of the string str.
    It is a checked runtime error if str is NULL.  */
size_t ms_length(const char *str);

/*  Copy the string src to dest, returning a pointer to dest.
    It is a checked runtime error for dest or src to be NULL.  */
char *ms_copy(char *dest,const char *src);

/*  Copy at most n characters from the string src to dest,
    returning a pointer to dest, without adding the terminating
    character at the end.
    It is a checked runtime error for dest or src to be NULL.  */
char *ms_ncopy(char *dest, const char *src, size_t n);

/*  Append whole string src to dest returning a pointer to dest.
    It is a checked runtime error for src or dest to be NULL.  */
char *ms_concat(char *dest, const char *src);

/*  Append atmost n characters from string src to dest
    returning a pointer to dest.
    It is a checked runtime error for src or dest to be NULL.  */
char *ms_nconcat(char *dest, const char *src, size_t n);

/*  Find the first occurence of substring needle in the string
    haystack, returning a pointer to the beggining of the
    located substring or NULL if the substring in not found.
    It is a checked runtime error for haystack or needle to be NULL.  */
char *ms_search(const char *haystack,const char *needle);


