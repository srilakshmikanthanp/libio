#include "../src/srilakshmikanthanp/libio.h"
#include <string.h>
#include <assert.h>

int main()
{
    char chval = 'A';
    assert(!strcmp(str(chval), "A"));

    signed short ssval = -123;
    assert(!strcmp(str(ssval), "-123"));

    unsigned short usval = 123;
    assert(!strcmp(str(usval), "123"));

    signed int sival = -123;
    assert(!strcmp(str(sival), "-123"));

    unsigned int uival = 123;
    assert(!strcmp(str(uival), "123"));

    signed long slval = -123;
    assert(!strcmp(str(slval), "-123"));

    unsigned long ulval = 123;
    assert(!strcmp(str(ulval), "123"));

    signed long long sllval = -123;
    assert(!strcmp(str(sllval), "-123"));

    unsigned long long ullval = 123;
    assert(!strcmp(str(ullval), "123"));

    return 0;
}