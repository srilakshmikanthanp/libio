#include "../src/srilakshmikanthanp/libio.h"
#include <string.h>
#include <assert.h>

int main()
{
    // input test
    char chval = 'A';
    assert(!strcmp(str(chval), "A"));

    signed short ssival = -123;
    assert(!strcmp(str(chval), "-123"));

    unsigned short ssival = 123;
    assert(!strcmp(str(chval), "123"));

    return 0;
}