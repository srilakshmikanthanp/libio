#include "../src/srilakshmikanthanp/inout.h"

int main()
{
    // unnessery string_str and str in valstr but it help beginer
    string valstr = string_str(input("Enter String : "));
    print("You gave : ", str(valstr), "\n");

    char valchr = signed_char(input("Enter Char : "));
    print("You gave : ", str(valchr), "\n");

    int valint = signed_int(input("Enter Int : "));
    print("You gave : ", str(valint), "\n");

    float valflt = signed_float(input("Enter Float : "));
    print("You gave : ", str(valflt), "\n");

    return 0;
}