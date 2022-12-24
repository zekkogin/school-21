# s21_string

## Contents

1. [Chapter II](#chapter-i) \
    1.1. [Information](#information)
2. [Chapter III](#chapter-ii) \
    2.1. [Part 1](#part-1-implementation-of-the-stringh-library-functions)  
    2.2. [Part 2](#part-2-partial-implementation-of-the-sprintf-function)  
    2.3. [Part 3](#part-3-bonus-implementation-of-some-format-modifiers-of-the-sprintf-function) 


## Chapter II

## Information

The C programming language has a set of functions implementing operations on strings (character strings and byte strings) in its standard library. Various operations, such as copying, concatenation, tokenization and searching are supported. For character strings, the standard library uses the convention that strings are null-terminated: a string of n characters is represented as an array of n + 1 elements, the last of which is a "NULL" character. \
The only support for strings in the programming language proper is that the compiler translates quoted string constants into null-terminated strings.

### string.h Types

| No. | Variable | Description |
| ------ | ------ | ------ |
| 1 | size_t | This is the unsigned integral type and is the result of the sizeof keyword. |
	
### string.h Macro

| No. | Macro | Description |
| ------ | ------ | ------ |
| 1 | NULL | This macro is the value of a null pointer constant. |

### string.h Functions

| No. | Function | Description |
| ------ | ------ | ------ |
| 1 | void *memchr(const void *str, int c, size_t n) | Searches for the first occurrence of the character c (an unsigned char) in the first n bytes of the string pointed to, by the argument str. |
| 2 | int memcmp(const void *str1, const void *str2, size_t n) | Compares the first n bytes of str1 and str2. |
| 3 | void *memcpy(void *dest, const void *src, size_t n) | Copies n characters from src to dest. |
| 4 | void *memmove(void *dest, const void *src, size_t n) | Another function to copy n characters from src to dest. |
| 5 | void *memset(void *str, int c, size_t n) | Copies the character c (an unsigned char) to the first n characters of the string pointed to, by the argument str. |
| 6 | char *strcat(char *dest, const char *src) | Appends the string pointed to, by src to the end of the string pointed to by dest. |
| 7 | char *strncat(char *dest, const char *src, size_t n) | Appends the string pointed to, by src to the end of the string pointed to, by dest up to n characters long. |
| 8	| char *strchr(const char *str, int c) | Searches for the first occurrence of the character c (an unsigned char) in the string pointed to, by the argument str. |
| 9 | int strcmp(const char *str1, const char *str2) | Compares the string pointed to, by str1 to the string pointed to by str2. |
| 10 | int strncmp(const char *str1, const char *str2, size_t n) | Compares at most the first n bytes of str1 and str2. |
| 11 | char *strcpy(char *dest, const char *src) | Copies the string pointed to, by src to dest. |
| 12 | char *strncpy(char *dest, const char *src, size_t n) | Copies up to n characters from the string pointed to, by src to dest. |
| 13 | size_t strcspn(const char *str1, const char *str2) | Calculates the length of the initial segment of str1 which consists entirely of characters not in str2. |
| 14 | char *strerror(int errnum) | Searches an internal array for the error number errnum and returns a pointer to an error message string. You need to declare macros containing arrays of error messages for mac and linux operating systems. Error descriptions are available in the original library. Checking the current OS is carried out using directives. |
| 15 | size_t strlen(const char *str) | Computes the length of the string str up to but not including the terminating null character. |
| 16 | char *strpbrk(const char *str1, const char *str2) | Finds the first character in the string str1 that matches any character specified in str2. |
| 17 | char *strrchr(const char *str, int c) | Searches for the last occurrence of the character c (an unsigned char) in the string pointed to by the argument str. |
| 18 | size_t strspn(const char *str1, const char *str2) | Calculates the length of the initial segment of str1 which consists entirely of characters in str2. |
| 19 | char *strstr(const char *haystack, const char *needle) | Finds the first occurrence of the entire string needle (not including the terminating null character) which appears in the string haystack. |
| 20 | char *strtok(char *str, const char *delim) | Breaks string str into a series of tokens separated by delim. |


## Chapter III

## Part 1. Implementation of the string.h library functions

It is necessary to implement the described [above](#stringh-functions) functions of the string.h library: 
 - The library must be developed in C language of C11 standard using gcc compiler
 - The library's code, including headers, makefile and library itself must be located in the src folder on the develop branch    
 - Do not use outdated and legacy language constructions and library functions. Pay attention to the legacy and obsolete marks in the official documentation on the language and the libraries used. Use the POSIX.1-2017 standard. 
 - Make it as a static library (with the header file s21_string.h)
 - The library must be developed in accordance with the principles of structured programming, duplication in the code must be avoided
 - Prepare a full coverage of the library's functions by unit-tests using the Check library
 - Test's code and the executable file must be located in the src folder or its any subfolder
 - Unit-tests must check the results of your implementation by comparing them with the implementation of the standard string.h library
 - Unit tests must cover at least 80% of each function (checked using gcov)
 - Provide a Makefile for building the library and tests (with the targets all, clean, test, s21_string.a, gcov_report)
 - The gcov_report target should generate a gcov report in the form of an html page. Unit tests must be run with gcov flags to do this
 - Use prefix s21_ before each function
 - It is forbidden to copy the implementation of the standard string.h library and other string processing libraries and to use them anywhere, except unit-tests
 - It is forbidden to use system errors arrays, including those not specified in POSIX (sys_nerr, sys_errlist). Instead, you need to implement your own platform-specific errors arrays, as it was mentioned in the description of the [strerror function](#stringh-functions)  
 - You must follow the logic of the standard string.h library (in terms of checks, working with memory and behavior in emergency situations - tests will help you with that)
 - Functions must work with z-string made of single-byte characters in ASCII encoding.

## Part 2. Partial implementation of the sprintf function

It is necessary to implement the sprintf function from the stdio.h library:
- The function must be placed in the s21_string.h library
- All of the requirements outlined in [the first part](#part-1-implementation-of-the-stringh-library-functions) are applied to function implementation.
- The next partial formatting must be supported:
  - Specifiers: c, d, i, f, s, u, %
  - Flags: -, +, (space)
  - Width description: (number)
  - Precision description: .(number)
  - Length description: h, l

## Part 3. Bonus. Implementation of some format modifiers of the sprintf function

Bonus assignment for extra points. It is necessary to implement some format modifiers of the sprintf function from the stdio.h library:
- The function must be placed in the s21_string.h library
- All of the requirements outlined in [the first part](#part-1-implementation-of-the-stringh-library-functions) are applied to function implementation.
- The next additional format modifiers must be supported:
  - Specifiers: g, G, e, E, x, X, o, n, p
  - Flags: #, 0
  - Width description: *
  - Precision description: .*
  - Length description: L
