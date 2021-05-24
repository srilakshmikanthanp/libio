#include "../src/srilakshmikanthanp/inout.h"

int main()
{
    string valstr = consoleinput("Enter String : ");
    consoleprint("You gave : ", valstr, "\n");

    char valchr = signed_char(consoleinput("Enter Char : "));
    consoleprint("You gave : ", str(valchr), "\n");

    int valint = signed_int(consoleinput("Enter Int : "));
    consoleprint("You gave : ", str(valint), "\n");

    float valflt = signed_float(consoleinput("Enter Float : "));
    consoleprint("You gave : ", str(valflt), "\n");

    return 0;
}