#include "../src/srilakshmikanthanp/libio.h"
#include <string.h>
#include <assert.h>

int main()
{
    // str test
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

    return 0;
}