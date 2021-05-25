/*
 * MIT License
 *
 * Copyright (c) 2021 Sri lakshmi kanthan P
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @brief start of library 
 */
#ifndef INOUT_HEADER
#define INOUT_HEADER

/*
 * include required headers
 */
#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <float.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @mainpage InOut
 *
 * @brief This is input/ouput library for c which
 * makes work easy especially for beginers see in
 * File section for documentation
 * @author Sri Lakshmi Kanthan P
 */

#ifndef MANUAL_CALL_LNDEL
    #if defined(__GNUC__) || defined(__clang__)
        void __attribute__((destructor)) lnlistdel(void);
    #elif
        #error "unknown compiler For inout.h library an Issue at"
               "https://github.com/srilakshmikanthanp/InOut"
               "or define MANUAL_CALL_LNDEL before include and"
               "call Manually lnlistdel at end of main or"
               "register with atexit"
    #endif
#endif

/**
 * @brief string representation of this library
 */
typedef char *string;

/**
 * @brief [internal] linked list  
 */
typedef struct lnlist
{
    // string ptr
    string ptr;
    // next ptr
    struct lnlist *nxt;

} lnlist;

/**
 * @brief Node to strings 
 */
lnlist *node = NULL;

/**
 * @brief [internal] appends a pointer to list
 * 
 * @param ptr pointer to string
 */
bool lnlistadd(string sptr)
{
    lnlist *data = NULL;

    if ((data = (lnlist *)malloc(sizeof(lnlist))) != NULL)
    {
        data->ptr = sptr;
        data->nxt = NULL;

        lnlist **sub = &node;

        while (*sub != NULL)
        {
            sub = &((*sub)->nxt);
        }

        (*sub) = data;

        return true;
    }

    return true;
}

/**
 * @brief [internal] delets list
 */
void lnlistdel(void)
{
    while (node != NULL)
    {
        lnlist *next = node->nxt;

        free(node->ptr);
        free(node);

        node = next;
    }
}

/**
 * @brief inputs line from a FILE and returns it back
 * to use as const NULL if fails.
 * 
 * @param file file to read
 * @return string readed string
 */
const string read(FILE *file, const string format, ...)
{
    // print the args
    if (format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // capacity of buffer
    size_t capacity = 0;

    // size of buffer
    size_t size = 0;

    // string buffer
    string buffer = NULL;

    // current character
    char c = 0;

    // read and apped character
    while ((c = fgetc(file)) != '\n' && c != '\r' && c != EOF)
    {
        // is enough room
        if (size + 1 > capacity)
        {
            // expand capacity
            if (capacity < SIZE_MAX)
            {
                ++capacity;
            }
            else
            {
                free(buffer);
                return NULL;
            }

            // try to realloc
            string temp = (string)realloc(buffer, capacity);

            // alloc fails
            if (temp == NULL)
            {
                free(buffer);
                return NULL;
            }

            // assign temp
            buffer = temp;
        }

        // append char
        buffer[size++] = c;
    }

    // size is 0 the ""
    if (size == 0)
    {
        return "";
    }

    // if size is max then there is no room for NULL
    if (size == SIZE_MAX)
    {
        free(buffer);
        return NULL;
    }

    //shrink buffer
    string temp = (string)realloc(buffer, size + 1);

    // if fails then return NULL
    if (temp == NULL)
    {
        free(buffer);
        return NULL;
    }
    else
    {
        buffer = temp;
    }

    // assign NULL
    buffer[size] = '\0';

    // add to list
    if (!lnlistadd(buffer))
    {
        free(buffer);
        return NULL;
    }

    // finally done
    return buffer;
}

/**
 * @brief returns signed char from string if any error then
 * SCHAR_MIN or SCHAR_MAX is returned
 * 
 * @param str 
 * @return signed char 
 */
signed char signed_char(const string str)
{
    // length
    size_t len = strlen(str);

    // if str is NULL or empty or > 1 then return CHAR_MAX
    if (str == NULL || len == 0 || len > 1)
    {
        return SCHAR_MAX;
    }

    // finally done
    return str[0];
}

/**
 * @brief return same string
 * 
 * @param str string
 * @return string value
 */
string string_str(string str)
{
    return str;
}

/**
 * @brief returns unsigned char from string if any error then
 * 0 or UCHAR_MAX is returned
 * 
 * @param str 
 * @return signed char 
 */
unsigned char unsigned_char(const string str)
{
    // length
    size_t len = strlen(str);

    // if str is NULL or empty or > 1 then return CHAR_MAX
    if (str == NULL || len == 0 || len > 1)
    {
        return UCHAR_MAX;
    }

    // finally done
    return str[0];
}

/**
 * @brief String to sort int if any erro occurs
 * then returns SHRT_MAX or SHRT_MIN
 * 
 * @param str string
 * @return short value
 */
signed short signed_short(const string str)
{
    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return SHRT_MAX
    if (str == NULL || len == 0)
    {
        return SHRT_MAX;
    }

    // end ptr for track
    char *endptr = NULL;

    // actual value in long
    long value = strtol(str, &endptr, 0);

    // if value too low for short
    if (value < SHRT_MIN)
    {
        return SHRT_MIN;
    }

    // if value too bog for short
    if (value > SHRT_MAX)
    {
        return SHRT_MAX;
    }

    // if this string is not perfect short
    if (*endptr != '\0')
    {
        return SHRT_MAX;
    }

    // finally done
    return value;
}

/**
 * @brief returns unsigned short of string if any
 * error occurs then 0 or USHRT_MAX is returned
 * 
 * @param str string value
 * @return unsigned short value
 */
unsigned short unsigned_short(const string str)
{
    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return SHRT_MAX
    if (str == NULL || len == 0)
    {
        return USHRT_MAX;
    }

    // end ptr for track
    char *endptr = NULL;

    // actual value in long
    unsigned long value = strtoul(str, &endptr, 0);

    // if value too big for short
    if (value > USHRT_MAX)
    {
        return USHRT_MAX;
    }

    // if this string is not perfect short
    if (*endptr != '\0')
    {
        return USHRT_MAX;
    }

    // finally done
    return value;
}

/**
 * @brief string to signed integer if any error
 * then INT_MIN or INT_MAX is returned 
 * 
 * @param str string value
 * @return signed int value
 */
signed int signed_int(const string str)
{
    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return INT_MAX
    if (str == NULL || len == 0)
    {
        return INT_MAX;
    }

    // end ptr for track
    char *endptr = NULL;

    // actual value in long
    long value = strtol(str, &endptr, 0);

    // if value too low for int
    if (value < INT_MIN)
    {
        return INT_MIN;
    }

    // if value too big for int
    if (value > INT_MAX)
    {
        return INT_MAX;
    }

    // if this string is not perfect int
    if (*endptr != '\0')
    {
        return INT_MAX;
    }

    // finally done
    return value;
}

/**
 * @brief returns unsigned int of string if any
 * error occurs then 0 or UINT_MAX is returned
 * 
 * @param str string value
 * @return unsigned int value
 */
unsigned int unsigned_int(const string str)
{
    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return UINT_MAX
    if (str == NULL || len == 0)
    {
        return UINT_MAX;
    }

    // end ptr for track
    char *endptr = NULL;

    // actual value in long
    unsigned long value = strtoul(str, &endptr, 0);

    // if value too big for unsigned int
    if (value > UINT_MAX)
    {
        return UINT_MAX;
    }

    // if this string is not perfect unsigned int
    if (*endptr != '\0')
    {
        return UINT_MAX;
    }

    // finally done
    return value;
}

/**
 * @brief string to signed long if any error
 * then LONG_MIN or LONG_MAX is returned 
 * 
 * @param str string value
 * @return signed long value
 */
signed long signed_long(const string str)
{
    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return LONG_MAX
    if (str == NULL || len == 0)
    {
        return LONG_MAX;
    }

    // end ptr for track
    char *endptr = NULL;

    // actual value in long
    long value = strtol(str, &endptr, 0);

    // if this string is not perfect int
    if (*endptr != '\0')
    {
        return LONG_MAX;
    }

    // finally done
    return value;
}

/**
 * @brief returns unsigned long of string if any
 * error occurs then 0 or ULONG_MAX is returned
 * 
 * @param str string value
 * @return unsigned long value
 */
unsigned long unsigned_long(const string str)
{
    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return ULONG_MAX
    if (str == NULL || len == 0)
    {
        return ULONG_MAX;
    }

    // end ptr for track
    char *endptr = NULL;

    // actual value in long
    unsigned long value = strtoul(str, &endptr, 0);

    // if this string is not perfect unsigned int
    if (*endptr != '\0')
    {
        return ULONG_MAX;
    }

    // finally done
    return value;
}

/**
 * @brief string to signed longlong if any error
 * then LLONG_MIN or LLONG_MAX is returned 
 * 
 * @param str string value
 * @return signed long long value
 */
signed long long signed_long_long(const string str)
{
    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return LONG_MAX
    if (str == NULL || len == 0)
    {
        return LLONG_MAX;
    }

    // end ptr for track
    char *endptr = NULL;

    // actual value in long
    long long value = strtoll(str, &endptr, 0);

    // if this string is not perfect int
    if (*endptr != '\0')
    {
        return LLONG_MAX;
    }

    // finally done
    return value;
}

/**
 * @brief returns unsigned long long of string if any
 * error occurs then 0 or ULONG_MAX is returned
 * 
 * @param str string value
 * @return unsigned long long value
 */
unsigned long long unsigned_long_long(const string str)
{
    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return ULONG_MAX
    if (str == NULL || len == 0)
    {
        return ULLONG_MAX;
    }

    // end ptr for track
    char *endptr = NULL;

    // actual value in long
    unsigned long long value = strtoull(str, &endptr, 0);

    // if this string is not perfect unsigned int
    if (*endptr != '\0')
    {
        return ULLONG_MAX;
    }

    // finally done
    return value;
}

/**
 * @brief string to float if any error occurs If the 
 * converted value falls out of range of corresponding 
 * return type, range error occurs and HUGE_VALF is returned. 
 * If no conversion can be performed, ​0​ is returned.
 * 
 * @param str string value
 * @return float value
 */
float signed_float(const string str)
{
    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return LONG_MAX
    if (str == NULL || len == 0)
    {
        return HUGE_VALF;
    }

    // end ptr for track
    char *endptr = NULL;

    // actual value in long
    float value = strtof(str, &endptr);

    // if this string is not perfect float
    if (*endptr != '\0')
    {
        return HUGE_VALF;
    }

    // finally done
    return value;
}

/**
 * @brief string to double if any error occurs If the 
 * converted value falls out of range of corresponding 
 * return type, range error occurs and HUGE_VAL, 
 * is returned. If no conversion can be performed, ​
 * 0​ is returned.
 * 
 * @param str string value
 * @return double value
 */
double signed_double(const string str)
{
    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return LONG_MAX
    if (str == NULL || len == 0)
    {
        return HUGE_VAL;
    }

    // end ptr for track
    char *endptr = NULL;

    // actual value in double
    double value = strtod(str, &endptr);

    // if this string is not perfect double
    if (*endptr != '\0')
    {
        return HUGE_VAL;
    }

    // finally done
    return value;
}

/**
 * @brief string to long double if any error occurs If the 
 * converted value falls out of range of corresponding 
 * return type, range error occurs and HUGE_VALL is returned.
 * If no conversion can be performed, ​0​ is returned.
 * 
 * @param str string value
 * @return long double value
 */
long double signed_long_double(const string str)
{
    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return LONG_MAX
    if (str == NULL || len == 0)
    {
        return HUGE_VAL;
    }

    // end ptr for track
    char *endptr = NULL;

    // actual value in long
    long double value = strtof(str, &endptr);

    // if this string is not perfect long double
    if (*endptr != '\0')
    {
        return HUGE_VAL;
    }

    // finally done
    return value;
}

#define get(T, FUNC) _Generic( (T) 0,            \
    char *             : string_str,             \
    char               : signed_char,            \
    signed char        : signed_char,            \
    unsigned char      : unsigned_char,          \
    signed short       : signed_short,           \
    unsigned short     : unsigned_short,         \
    signed int         : signed_int,             \
    unsigned int       : unsigned_int,           \
    signed long        : signed_long,            \
    unsigned long      : unsigned_long,          \
    signed long long   : signed_long_long,       \
    unsigned long long : unsigned_long_long,     \
    float              : signed_float,           \
    double             : signed_double,          \
    long double        : signed_long_double      \
)(FUNC)

/**
 * @brief [internal] print the out to file
 * 
 * @param count count of arguments
 * @param ... char*
 */
void basic_write(FILE *file, int count, ...)
{
    // varg init
    va_list valist;

    // va start the valist
    va_start(valist, count);

    // print iteratively
    for (int i = 0; i < count; ++i)
    {
        char *arg = va_arg(valist, char *);

        if (arg == NULL)
        {
            fputs("<NULL>", file);
        }
        else
        {
            fputs(arg, file);
        }
    }

    // end va_arg
    va_end(valist);
}

/**
 * @brief prints to a File
 * 
 * @param File file to print
 * @param ... char*
 */
#define write(File, ...) basic_write(File,              \
    sizeof((char *[]){__VA_ARGS__}) / sizeof(char *),   \
    __VA_ARGS__                                         \
)

/**
 * @brief return same string pointer
 * 
 * @param str string
 * @return string string
 */
string string_to_str(string str)
{
    return str;
}

/**
 * @brief signed char to string 
 * 
 * @param ch char
 * @return string string 
 */
string signed_char_to_str(signed char ch)
{
    string str = calloc(1, sizeof(signed char));

    if (str == NULL)
    {
        return NULL;
    }

    if(!lnlistadd(str))
    {
        free(str);
        return NULL;
    }

    str[0] = ch;
    
    return str;
}

/**
 * @brief undigned char to string
 * 
 * @param ch char
 * @return string string 
 */
string unsigned_char_to_str(unsigned char ch)
{
    string str = calloc(1, sizeof(unsigned char));

    if (str == NULL)
    {
        return NULL;
    }

    if(!lnlistadd(str))
    {
        free(str);
        return NULL;
    }

    str[0] = ch;
    
    return str;
}

/**
 * @brief signed short to string
 * 
 * @param val value
 * @return string string
 */
string signed_short_to_str(signed short val)
{
    size_t len = snprintf(NULL, 0, "%hd", val);
    string str = calloc(++len, sizeof(char));

    if(!lnlistadd(str))
    {
        free(str);
        return NULL;
    }

    snprintf(str, len, "%d", val);

    return str;
}

/**
 * @brief unsigned short to string
 * 
 * @param val value
 * @return string string
 */
string unsigned_short_to_str(unsigned short val)
{
    size_t len = snprintf(NULL, 0, "%hu", val);
    string str = calloc(++len, sizeof(char));

    if(!lnlistadd(str))
    {
        free(str);
        return NULL;
    }

    snprintf(str, len, "%u", val);

    return str;
}

/**
 * @brief signed int to string
 * 
 * @param val value
 * @return string string
 */
string signed_int_to_str(signed int val)
{
    size_t len = snprintf(NULL, 0, "%d", val);
    string str = calloc(++len, sizeof(char));

    if(!lnlistadd(str))
    {
        free(str);
        return NULL;
    }

    snprintf(str, len, "%d", val);

    return str;
}

/**
 * @brief unsigned int to string
 * 
 * @param val value
 * @return string string
 */
string unsigned_int_to_str(unsigned int val)
{
    size_t len = snprintf(NULL, 0, "%u", val);
    string str = calloc(++len, sizeof(char));

    if(!lnlistadd(str))
    {
        free(str);
        return NULL;
    }

    snprintf(str, len, "%u", val);

    return str;
}

/**
 * @brief signed long to string
 * 
 * @param val value
 * @return string string
 */
string signed_long_to_str(signed long val)
{
    size_t len = snprintf(NULL, 0, "%ld", val);
    string str = calloc(len +1, sizeof(char));

    if(!lnlistadd(str))
    {
        free(str);
        return NULL;
    }

    snprintf(str, len, "%ld", val);

    return str;
}

/**
 * @brief unsigned long to string
 * 
 * @param val value
 * @return string string
 */
string unsigned_long_to_str(unsigned long val)
{
    size_t len = snprintf(NULL, 0, "%lu", val);
    string str = calloc(++len, sizeof(char));

    if(!lnlistadd(str))
    {
        free(str);
        return NULL;
    }

    snprintf(str, len, "%lu", val);

    return str;
}

/**
 * @brief signed long long to string
 * 
 * @param val value
 * @return string string
 */
string signed_long_long_to_str(signed long long val)
{
    size_t len = snprintf(NULL, 0, "%lld", val);
    string str = calloc(++len, sizeof(char));

    if(!lnlistadd(str))
    {
        free(str);
        return NULL;
    }

    snprintf(str, len, "%lld", val);

    return str;
}

/**
 * @brief unsigned long long to string
 * 
 * @param val value
 * @return string string
 */
string unsigned_long_long_to_str(unsigned long long val)
{
    size_t len = snprintf(NULL, 0, "%llu", val);
    string str = calloc(++len, sizeof(char));

    if(!lnlistadd(str))
    {
        free(str);
        return NULL;
    }

    snprintf(str, len, "%llu", val);

    return str;
}

/**
 * @brief float to string
 * 
 * @param val 
 * @return string 
 */
string signed_float_to_str(float val)
{
    size_t len = snprintf(NULL, 0, "%f", val);
    string str = calloc(++len, sizeof(char));

    if(!lnlistadd(str))
    {
        free(str);
        return NULL;
    }

    snprintf(str, len, "%f", val);

    return str;
}

/**
 * @brief double to string
 * 
 * @param val 
 * @return string 
 */
string signed_double_to_str(double val)
{
    size_t len = snprintf(NULL, 0, "%lf", val);
    string str = calloc(++len, sizeof(char));

    if(!lnlistadd(str))
    {
        free(str);
        return NULL;
    }

    snprintf(str, len, "%lf", val);

    return str;
}

/**
 * @brief long double to string
 * 
 * @param val 
 * @return string 
 */
string signed_long_double_to_str(long double val)
{
    size_t len = snprintf(NULL, 0, "%Lf", val);
    string str = calloc(++len, sizeof(char));

    if(!lnlistadd(str))
    {
        free(str);
        return NULL;
    }

    snprintf(str, len, "%Lf", val);

    return str;
}


/**
 * @brief str converts a value into string 
 * 
 * @param val value to convert
 */
#define str(val) _Generic((val),                        \
    char*              : string_to_str,                 \
    char               : signed_char_to_str,            \
    signed char        : signed_char_to_str,            \
    unsigned char      : unsigned_char_to_str,          \
    signed short       : signed_short_to_str,           \
    unsigned short     : unsigned_short_to_str,         \
    signed int         : signed_int_to_str,             \
    unsigned int       : unsigned_int_to_str,           \
    signed long        : signed_long_to_str,            \
    unsigned long      : unsigned_long_to_str,          \
    signed long long   : signed_long_long_to_str,       \
    unsigned long long : unsigned_long_long_to_str,     \
    float              : signed_float_to_str,           \
    double             : signed_double_to_str,          \
    long double        : signed_long_double_to_str      \
)(val)

/**
 * @brief console input with stdin default
 */
#define input(...) read(stdin, __VA_ARGS__)

/**
 * @brief console output with stdout default 
 */
#define print(...) write(stdout, __VA_ARGS__)

/**
 * @brief end of library 
 */
#endif