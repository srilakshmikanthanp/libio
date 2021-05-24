<!-- PROJECT LOGO -->
<br />
<p align="center">
  <h3 align="center">InOut</h3>
  <p align="center">
    Easy Input Output Library For C
    <br />
    <a href="https://srilakshmikanthanp.github.io/InOut/docs/html/"><strong>Explore the docs »</strong></a>
    <br />
    <a href="https://github.com/srilakshmikanthanp/InOut/issues">Report Bug</a>
    ·
    <a href="https://github.com/srilakshmikanthanp/InOut/issues">Request Feature</a>
  </p>
</p>

<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

This is an easy input output library for c especially for begineers. This Library works on top off stdio.h but uses a input function that returns string that allocated on heap but it tracks of that with help of linked list that will be deallocated or freed after main. print function takes variable arg of char* you can conver buildin types to string easily with str that uses _Generic.

<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

~~~shell
git clone https://github.com/srilakshmikanthanp/InOut/
~~~

### Installation

This is Header only library so just download [inout.h](src/srilakshmikanthanp/inout.h) and use

<!-- USAGE EXAMPLES -->
## Usage

Usage is very simple, example whould be that takes some of types,

~~~c
#include "inout.h"

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
~~~

Available input functions,

~~~c
/**
 * @brief inputs line from a FILE and returns it back
 * to use as const NULL if fails.
 * 
 * @param file file to read
 * @return string readed string
 */
const string read(FILE *file, const string format, ...);

/**
 * @brief return same string
 * 
 * @param str string
 * @return string value
 */
string string_str(string str)

/**
 * @brief returns signed char from string if any error then
 * SCHAR_MIN or SCHAR_MAX is returned
 * 
 * @param str 
 * @return signed char 
 */
signed char signed_char(const string str);

/**
 * @brief returns unsigned char from string if any error then
 * 0 or UCHAR_MAX is returned
 * 
 * @param str 
 * @return signed char 
 */
unsigned char unsigned_char(const string str);

/**
 * @brief String to sort int if any erro occurs
 * then returns SHRT_MAX or SHRT_MIN
 * 
 * @param str string
 * @return short value
 */
signed short signed_short(const string str);

/**
 * @brief returns unsigned short of string if any
 * error occurs then 0 or USHRT_MAX is returned
 * 
 * @param str string value
 * @return unsigned short value
 */
unsigned short unsigned_short(const string str);

/**
 * @brief string to signed integer if any error
 * then INT_MIN or INT_MAX is returned 
 * 
 * @param str string value
 * @return signed int value
 */
signed int signed_int(const string str);

/**
 * @brief returns unsigned int of string if any
 * error occurs then 0 or UINT_MAX is returned
 * 
 * @param str string value
 * @return unsigned int value
 */
unsigned int unsigned_int(const string str);

/**
 * @brief string to signed long if any error
 * then LONG_MIN or LONG_MAX is returned 
 * 
 * @param str string value
 * @return signed long value
 */
signed long signed_long(const string str);

/**
 * @brief returns unsigned long of string if any
 * error occurs then 0 or ULONG_MAX is returned
 * 
 * @param str string value
 * @return unsigned long value
 */
unsigned long unsigned_long(const string str);

/**
 * @brief string to signed longlong if any error
 * then LLONG_MIN or LLONG_MAX is returned 
 * 
 * @param str string value
 * @return signed long long value
 */
signed long long signed_long_long(const string str);

/**
 * @brief returns unsigned long long of string if any
 * error occurs then 0 or ULONG_MAX is returned
 * 
 * @param str string value
 * @return unsigned long long value
 */
unsigned long long unsigned_long_long(const string str);

/**
 * @brief string to float if any error occurs If the 
 * converted value falls out of range of corresponding 
 * return type, range error occurs and HUGE_VALF is returned. 
 * If no conversion can be performed, ​0​ is returned.
 * 
 * @param str string value
 * @return float value
 */
float signed_float(const string str);

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
double signed_double(const string str);

/**
 * @brief string to long double if any error occurs If the 
 * converted value falls out of range of corresponding 
 * return type, range error occurs and HUGE_VALL is returned.
 * If no conversion can be performed, ​0​ is returned.
 * 
 * @param str string value
 * @return long double value
 */
long double signed_long_double(const string str);
~~~

Avaibale output functions,

~~~c
/**
 * @brief print function
 * 
 * @param file file to print
 * @param ...  char* 
 */
void write(FILE* file, ...);

/**
 * @brief convert definded types to string
 * 
 * @param val build in types
 * @return string value
 */
string str(type val);
~~~

Console defaults,

~~~c
/**
 * @brief console input with stdin default
 */
#define input(...) read(stdin, __VA_ARGS__)

/**
 * @brief console output with stdout default 
 */
#define print(...) write(stdout, __VA_ARGS__)
~~~

_For more examples, please refer to the Documentation_

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<!-- CONTACT -->
## Contact

Project Link: [https://github.com/srilakshmikanthanp/InOut](https://github.com/srilakshmikanthanp/InOut)
