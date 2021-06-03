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

#ifndef LIBIO_HEADER
#define LIBIO_HEADER

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
 * @mainpage libio
 *
 * @brief This is input/ouput library for c which
 * makes work easy especially for beginers see in
 * File section for documentation
 * @author Sri Lakshmi Kanthan P
 */

#ifndef MANUAL_CALL_LNLISTDEL
    #if defined(__GNUC__) || defined(__clang__)
        void __attribute__((destructor)) lnlistdel(void);
    #elif
        #error "unknown compiler For libio.h library an Issue at"
               "https://github.com/srilakshmikanthanp/InOut"
               "or define MANUAL_CALL_LNLISTDEL before include and"
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
 * @brief inputs raw string returns in in heap
 * must be freed manualy
 * 
 * @return string 
 */
const string raw_string(FILE *file)
{
    // capacity of buffer
    size_t capacity = 0;

    // size of buffer
    size_t size = 0;

    // string buffer
    string buffer = NULL;

    // current character
    int c = 0;

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

    // size is 0 then NULL
    if (size == 0)
    {
        return NULL;
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

    // done
    return buffer;
}

/**
 * @brief inputs line from a FILE and returns it back
 * to use as const NULL if fails.
 * 
 * @param file file to read
 * @return string readed string
 */
const string get_string(FILE *file, const string format, ...)
{
    // print the args
    if (format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // get string
    string str = raw_string(file);

    // if null then try to alloc single byte
    if(str == NULL)
    {
        str = calloc(1, sizeof(char));
    }

    // add to list
    if (!lnlistadd(str))
    {
        free(str);
        return NULL;
    }

    // finally done
    return str;
}

/**
 * @brief returns signed char from file if any error then
 * SCHAR_MIN or SCHAR_MAX is returned
 * 
 * @param file file
 * @param format format string 
 * @return signed char 
 */
signed char get_signed_char(FILE *file, const string format, ...)
{
    // print the args
    if (format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // get raw string
    const string str = raw_string(file);

    // if failed then return SCHAR_MAX
    if(str == NULL)
    {
        return SCHAR_MAX;
    }

    // length
    size_t len = strlen(str);

    // extract char
    signed char ch = str[0];

    // unget remaining character
    for(int i = 1; str[i] != '\0'; ++i)
    {
        // if fails
        if(ungetc(ch, file) == EOF)
        {
            free(str);
            return SCHAR_MAX;
        }
    }

    // free the str
    free(str);

    // return char
    return ch;
}

/**
 * @brief returns unsigned char from string if any error then
 * 0 or UCHAR_MAX is returned
 * 
 * @param file file
 * @param format format string 
 * @return unsigned char 
 */
unsigned char get_unsigned_char(FILE *file, const string format, ...)
{
    // print the args
    if (format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // get raw string
    const string str = raw_string(file);

    // if failed then return SCHAR_MAX
    if(str == NULL)
    {
        return UCHAR_MAX;
    }

    // length
    size_t len = strlen(str);

    // extract char
    unsigned char ch = str[0];

    // unget remaining character
    for(int i = 1; str[i] != '\0'; ++i)
    {
        // if fails
        if(ungetc(ch, file) == EOF)
        {
            free(str);
            return UCHAR_MAX;
        }
    }

    // free the str
    free(str);

    // return char
    return ch;
}

/**
 * @brief get sort int if any erro occurs
 * then returns SHRT_MAX or SHRT_MIN
 * 
 * @param file file
 * @param format format string 
 * @return sort int 
 */
signed short get_signed_short(FILE *file, const string format, ...)
{
    // print the args
    if (format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // get string
    string str = raw_string(file);

    // length
    size_t len = strlen(str);

    // end ptr for track
    char *end = NULL;

    // if str is NULL or empty then return SHRT_MAX
    if (str == NULL || len == 0)
    {
        return SHRT_MAX;
    }

    // actual value in long
    long value = strtol(str, &end, 0);

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

    // unget
    while(*end != '\0')
    {
        // if fails
        if(ungetc(*end, file) == EOF)
        {
            free(str);
            return SHRT_MAX;
        } 
    }

    // free str
    free(str);

    // finally done
    return value;
}

/**
 * @brief returns unsigned short from file if any
 * error occurs then 0 or USHRT_MAX is returned
 * 
 * @param file file
 * @param format format string 
 * @return unsigned sort int 
 */
unsigned short get_unsigned_short(FILE *file, const string format, ...)
{
    // print the args
    if (format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // get string
    string str = raw_string(file);

    // length
    size_t len = strlen(str);

    // end ptr for track
    char *end = NULL;

    // if str is NULL or empty then return SHRT_MAX
    if (str == NULL || len == 0)
    {
        return USHRT_MAX;
    }

    // actual value in long
    unsigned long value = strtoul(str, &end, 0);

    // if value too big for short
    if (value > USHRT_MAX)
    {
        return USHRT_MAX;
    }

    // unget
    while(*end != '\0')
    {
        // if fails
        if(ungetc(*end, file) == EOF)
        {
            free(str);
            return USHRT_MAX;
        } 
    }

    // finally done
    return value;
}

/**
 * @brief read signed integer if any error
 * then INT_MIN or INT_MAX is returned 
 * 
 * @param file file
 * @param format format string 
 * @return signed int
 */
signed int get_signed_int(FILE *file, const string format, ...)
{
    // print the args
    if (format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // get string
    string str = raw_string(file);

    // length
    size_t len = strlen(str);

    // end ptr for track
    char *end = NULL;

    // if str is NULL or empty then return INT_MAX
    if (str == NULL || len == 0)
    {
        return INT_MAX;
    }

    // actual value in long
    long value = strtol(str, &end, 0);

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

    // unget
    while(*end != '\0')
    {
        // if fails
        if(ungetc(*end, file) == EOF)
        {
            free(str);
            return INT_MAX;
        } 
    }

    // free string
    free(str);

    // finally done
    return value;
}

/**
 * @brief returns unsigned int of from file if any
 * error occurs then 0 or UINT_MAX is returned
 * 
 * @param file file
 * @param format format string 
 * @return unsigned int
 */
unsigned int get_unsigned_int(FILE *file, const string format, ...)
{
    // print the args
    if (format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // read string
    string str = raw_string(file);

    // length
    size_t len = strlen(str);

    // end ptr for track
    char *end = NULL;

    // if str is NULL or empty then return UINT_MAX
    if (str == NULL || len == 0)
    {
        return UINT_MAX;
    }

    // actual value in long
    unsigned long value = strtoul(str, &end, 0);

    // if value too big for unsigned int
    if (value > UINT_MAX)
    {
        return UINT_MAX;
    }

    // unget
    while(*end != '\0')
    {
        // if fails
        if(ungetc(*end, file) == EOF)
        {
            free(str);
            return UINT_MAX;
        } 
    }

    // free string
    free(str);

    // finally done
    return value;
}

/**
 * @brief read signed long if any error
 * then LONG_MIN or LONG_MAX is returned 
 * 
 * @param file file
 * @param format format string 
 * @return signed long
 */
signed long get_signed_long(FILE *file, const string format, ...)
{
    // print the args
    if (format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // get string
    string str = raw_string(file);

    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return LONG_MAX
    if (str == NULL || len == 0)
    {
        return LONG_MAX;
    }

    // end ptr for track
    char *end = NULL;

    // actual value in long
    long value = strtol(str, &end, 0);

    // unget
    while(*end != '\0')
    {
        // if fails
        if(ungetc(*end, file) == EOF)
        {
            free(str);
            return LONG_MAX;
        } 
    }

    // free string
    free(str);

    // finally done
    return value;
}

/**
 * @brief returns unsigned long of string if any
 * error occurs then 0 or ULONG_MAX is returned
 * 
 * @param file file
 * @param format format string 
 * @return unsigned long
 */
unsigned long get_unsigned_long(FILE *file, const string format, ...)
{
    // print the args
    if (format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // get string
    string str = raw_string(file);

    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return ULONG_MAX
    if (str == NULL || len == 0)
    {
        return ULONG_MAX;
    }

    // end ptr for track
    char *end = NULL;

    // actual value in long
    unsigned long value = strtoul(str, &end, 0);

    // unget
    while(*end != '\0')
    {
        // if fails
        if(ungetc(*end, file) == EOF)
        {
            free(str);
            return ULONG_MAX;
        } 
    }

    // free string
    free(str);

    // finally done
    return value;
}

/**
 * @brief string to signed longlong if any error
 * then LLONG_MIN or LLONG_MAX is returned 
 * 
 * @param file file
 * @param format format string 
 * @return signed long long
 */
signed long long get_signed_long_long(FILE *file, const string format, ...)
{
    // print the args
    if (format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // get string
    string str = raw_string(file);

    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return LONG_MAX
    if (str == NULL || len == 0)
    {
        return LLONG_MAX;
    }

    // end ptr for track
    char *end = NULL;

    // actual value in long
    long long value = strtoll(str, &end, 0);

    // unget
    while(*end != '\0')
    {
        // if fails
        if(ungetc(*end, file) == EOF)
        {
            free(str);
            return LLONG_MAX;
        } 
    }

    // free string
    free(str);

    // finally done
    return value;
}

/**
 * @brief returns unsigned long long of string if any
 * error occurs then 0 or ULONG_MAX is returned
 * 
 * @param file file
 * @param format format string 
 * @return unsigned long long
 */
unsigned long long get_unsigned_long_long(FILE *file, const string format, ...)
{
    // print the args
    if (format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // get string
    string str = raw_string(file);

    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return ULONG_MAX
    if (str == NULL || len == 0)
    {
        return ULLONG_MAX;
    }

    // end ptr for track
    char *end = NULL;

    // actual value in long
    unsigned long long value = strtoull(str, &end, 0);


    // unget
    while(*end != '\0')
    {
        // if fails
        if(ungetc(*end, file) == EOF)
        {
            free(str);
            return ULLONG_MAX;
        } 
    }

    // free string
    free(str);

    // finally done
    return value;
}

/**
 * @brief string to float if any error occurs If the 
 * converted value falls out of range of corresponding 
 * return type, range error occurs and HUGE_VALF is returned. 
 * If no conversion can be performed, ​0​ is returned.
 * 
 * @param file file
 * @param format format string 
 * @return float 
 */
float get_float(FILE *file, const string format, ...)
{
    // print the args
    if (format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // get string
    string str = raw_string(file);

    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return LONG_MAX
    if (str == NULL || len == 0)
    {
        return HUGE_VALF;
    }

    // end ptr for track
    char *end = NULL;

    // actual value in long
    float value = strtof(str, &end);

    // unget
    while(*end != '\0')
    {
        // if fails
        if(ungetc(*end, file) == EOF)
        {
            free(str);
            return HUGE_VALF;
        } 
    }

    // free string
    free(str);

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
 * @param file file
 * @param format format string 
 * @return double
 */
double get_double(FILE *file, const string format, ...)
{
    // print the args
    if (format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // get string
    string str = raw_string(file);

    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return LONG_MAX
    if (str == NULL || len == 0)
    {
        return HUGE_VAL;
    }

    // end ptr for track
    char *end = NULL;

    // actual value in double
    double value = strtod(str, &end);

    // unget
    while(*end != '\0')
    {
        // if fails
        if(ungetc(*end, file) == EOF)
        {
            free(str);
            return HUGE_VAL;
        } 
    }

    // free string
    free(str);

    // finally done
    return value;
}

/**
 * @brief string to long double if any error occurs If the 
 * converted value falls out of range of corresponding 
 * return type, range error occurs and HUGE_VALL is returned.
 * If no conversion can be performed, ​0​ is returned.
 * 
 * @param file file
 * @param format format string 
 * @return long double 
 */
long double get_long_double(FILE *file, const string format, ...)
{
    // print the args
    if (format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // get string
    string str = raw_string(file);

    // length
    size_t len = strlen(str);

    // if str is NULL or empty then return LONG_MAX
    if (str == NULL || len == 0)
    {
        return HUGE_VAL;
    }

    // end ptr for track
    char *end = NULL;

    // actual value in long
    long double value = strtof(str, &end);

    // unget
    while(*end != '\0')
    {
        // if fails
        if(ungetc(*end, file) == EOF)
        {
            free(str);
            return HUGE_VAL;
        } 
    }

    // free string
    free(str);

    // finally done
    return value;
}

/**
 * @brief read from file
 */
#define read(T, file, ...) _Generic( (T) 0,                     \
    string             : get_string,                            \
    char               : get_signed_char,                       \
    signed char        : get_signed_char,                       \
    unsigned char      : get_unsigned_char,                     \
    signed short       : get_signed_short,                      \
    unsigned short     : get_unsigned_short,                    \
    signed int         : get_signed_int,                        \
    unsigned int       : get_unsigned_int,                      \
    signed long        : get_signed_long,                       \
    unsigned long      : get_unsigned_long,                     \
    signed long long   : get_signed_long_long,                  \
    unsigned long long : get_unsigned_long_long,                \
    float              : get_float,                             \
    double             : get_double,                            \
    long double        : get_long_double                        \
)(file, format, __VA_ARGS__)

/**
 * @brief read from console 
 */
#define input(T, ...) _Generic( (T) 0,                          \
    string             : get_string,                            \
    char               : get_signed_char,                       \
    signed char        : get_signed_char,                       \
    unsigned char      : get_unsigned_char,                     \
    signed short       : get_signed_short,                      \
    unsigned short     : get_unsigned_short,                    \
    signed int         : get_signed_int,                        \
    unsigned int       : get_unsigned_int,                      \
    signed long        : get_signed_long,                       \
    unsigned long      : get_unsigned_long,                     \
    signed long long   : get_signed_long_long,                  \
    unsigned long long : get_unsigned_long_long,                \
    float              : get_float,                             \
    double             : get_double,                            \
    long double        : get_long_double                        \
)(stdin, __VA_ARGS__)

/**
 * @brief [internal] print the out to file
 * 
 * @param count count of arguments
 * @param ... char*
 * @return number of args printed
 */
int raw_write(FILE *file, size_t count, ...)
{
    // printed count
    size_t pcount = 0;

    // varg init
    va_list valist;

    // va start the valist
    va_start(valist, count);

    // print iteratively
    for (int i = 0; i < count; ++i)
    {
        string arg = va_arg(valist, string);

        if (arg != NULL)
        {
            fputs(arg, file);
            pcount += 1;
        }
        else
        {
            fputs("(null)", file);
        }
    }

    // end va_arg
    va_end(valist);

    // return
    return pcount;
}

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
 * @brief converts pointer to string
 * 
 * @param ptr 
 * @return string 
 */
string pointer_to_str(void *ptr)
{
    size_t len = snprintf(NULL, 0, "%p", ptr);
    string str = calloc(++len, sizeof(char));

    if(!lnlistadd(str))
    {
        free(str);
        return NULL;
    }

    snprintf(str, len, "%p", ptr);

    return str;
}

/**
 * @brief str converts a value into string
 * 
 * @param val value to convert
 */
#define str(val) _Generic((val),                         \
    string              : string_to_str,                 \
    char                : signed_char_to_str,            \
    signed char         : signed_char_to_str,            \
    unsigned char       : unsigned_char_to_str,          \
    signed short        : signed_short_to_str,           \
    unsigned short      : unsigned_short_to_str,         \
    signed int          : signed_int_to_str,             \
    unsigned int        : unsigned_int_to_str,           \
    signed long         : signed_long_to_str,            \
    unsigned long       : unsigned_long_to_str,          \
    signed long long    : signed_long_long_to_str,       \
    unsigned long long  : unsigned_long_long_to_str,     \
    float               : signed_float_to_str,           \
    double              : signed_double_to_str,          \
    long double         : signed_long_double_to_str,     \
    signed short*       : pointer_to_str,                \
    unsigned short*     : pointer_to_str,                \
    signed int*         : pointer_to_str,                \
    unsigned int*       : pointer_to_str,                \
    signed long*        : pointer_to_str,                \
    unsigned long*      : pointer_to_str,                \
    signed long long*   : pointer_to_str,                \
    unsigned long long* : pointer_to_str,                \
    float*              : pointer_to_str,                \
    double*             : pointer_to_str,                \
    long double*        : pointer_to_str                 \
)(val)

/**
 * @brief prints to a File
 * 
 * @param File file to print
 * @param ... char*
 */
#define write(File, ...) raw_write(File,                \
    sizeof((char *[]){__VA_ARGS__}) / sizeof(char *),   \
    __VA_ARGS__                                         \
)

/**
 * @brief prints to console
 */
#define print(...) write(stdout, __VA_ARGS__)

#endif