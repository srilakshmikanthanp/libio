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

#ifndef SRILAKSHMIKANTHANPINOUT_H
#define SRILAKSHMIKANTHANPINOUT_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <float.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief destructor based on compiler or
 * define MANUAL_CALL_LNDEL and call lndel
 * at end of main function or register to
 * atexit
 */
#ifndef MANUAL_CALL_LNDEL
    #if defined(__GNUC__) || defined(__clang__)
        void __attribute__((destructor)) lndel();
    #elif
        #error unknown compiler For inout.h library an Issue at \
        https://github.com/srilakshmikanthanp/InOut \
        or define MANUAL_CALL_LNDEL before include and \
        call Manually lndel at end of main or \
        register with atexit
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
    string  ptr;
    // next ptr
    struct lnlist *nxt;

}lnlist;

/**
 * @brief Node to strings 
 */
lnlist *node = NULL;

/**
 * @brief [internal] appends a pointer to list
 * 
 * @param ptr pointer to string
 */
bool lnadd(string sptr)
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
void lndel()
{
    while (node->nxt != NULL)
    {
        lnlist *next = node->nxt;

        free(node->ptr);
        free(node);

        node = next;
    }

    free(node->ptr);
    free(node);
}

/**
 * @brief inputs line from a FILE and returns it back
 * to use as const NULL if fails.
 * 
 * @param file file to read
 * @return string readed string
 */
const string input(FILE* file, const string format, ...)
{
    // print the args
    if(format != NULL)
    {
        va_list vlis;
        va_start(vlis, format);
        vprintf(format, vlis);
        va_end(vlis);
    }

    // capacity of buffer
    int capacity = 0;

    // size of buffer
    int size = 0;

    // string buffer
    string buffer = NULL;

    // current character
    char c = 0;

    // read and apped character
    while((c = fgetc(file)) != '\n' && c != '\r' && c != EOF)
    {
        // is enough room
        if(size + 1 > capacity)
        {
            // expand capacity
            if(capacity < SIZE_MAX)
            {
                ++capacity;
            }
            else
            {
                free(buffer);
                return NULL;
            }

            // try to realloc
            string temp = (string) realloc(buffer, capacity);

            // alloc fails
            if(temp == NULL)
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
    if(size == 0)
    {
        return "";
    }

    // if size is max then there is no room for NULL
    if(size == SIZE_MAX)
    {
        free(buffer);
        return NULL;
    }

    //shrink buffer
    string temp = (string) realloc(buffer, size + 1);

    // if fails then return NULL
    if(temp == NULL)
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
    if(!lnadd(buffer))
    {
        free(buffer);
        return NULL;
    }

    // finally done
    return buffer;
}

#endif