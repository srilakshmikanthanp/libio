# liblo Docs

This is available input functions that achived using some simple trick on macros and _Generic,

~~~c
/**
 * @brief read a line of string from file
 * 
 * @param file file to read
 * @param format format spec like printf to print
 * @param ... varargs
 * 
 * @return line of string from file
 */
string read(FILE* file, const char* format, ...);

/**
 * @brief same as read but stdin as default
 */
string input(const char* format, ...);

/**
 * @brief type type to convert
 * 
 * @param string string to convert
 * @return type converted type
 */
type get(type, string);
~~~

This is available output functions that achived using some simple trick on macros and _Generic,

~~~c
/**
 * @brief writes to a File
 * 
 * @param File file to print
 * @param ... strings
 * @return number of args printed
 */
int write(File *file, ...);

/**
 * @brief same as write but stdout as defaul
 */
int print(...);

/**
 * @brief converts a type to string
 * 
 * @param val value
 * @return string of val
 */
string str(type val);
~~~

A simple example whould be followed like this,

~~~c
#include "inout.h"

int main()
{
    // Here get and str is unnesseary because it is alderdy string but may help begineers to understand better
    string valstr = get(string, input("Enter String : "));
    print("You gave : ", str(valstr), "\n");

    char valchr = get(char, input("Enter Char : "));
    print("You gave : ", str(valchr), "\n");

    int valint = get(int, input("Enter Int : "));
    print("You gave : ", str(valint), "\n");

    float valflt = get(float, input("Enter Float : "));
    print("You gave : ", str(valflt), "\n");

    return 0;
}
~~~

_This or not same prototype that implemented this is for understanding_
