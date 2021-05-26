#include "../src/srilakshmikanthanp/libio.h"

int main()
{
    // unnessery string_str and str in valstr but it help beginer
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