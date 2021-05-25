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

This is an easy input output library for c especially for begineers. This Library works on top of stdio.h but uses a input function that returns string that allocated on heap but it tracks of that with help of linked list that will be deallocated or freed after main. print function takes variable arg of char* you can convert build in types to string easily with str that uses _Generic to operate on various types.

<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

~~~shell
git clone https://github.com/srilakshmikanthanp/InOut/
~~~

### Installation

This is Header only library so just download [inout.h](src/srilakshmikanthanp/inout.h) and use it.

<!-- USAGE EXAMPLES -->
## Usage

To get input use this below functions,

~~~c
/**
 * @brief read a line of string from file
 * 
 * @param file file to read
 * @param format format spec like printf
 * @param ... varargs
 * 
 * @return line of string from file
 */
string read(FILE* file, const char* format, ...);

/**
 * @brief same as read but stdin as default
 */
string input(const char* format, ...);

/**
 * @brief type type to convert
 * 
 * @param string string to convert
 * @return type converted type
 */
type get(type, string);
~~~

To put output use below functions,

~~~c
/**
 * @brief writes to a File
 * 
 * @param File file to print
 * @param ... strings
 */
void write(File *file, ...);

/**
 * @brief same as write but stdout as defaul
 */
void print(...);

/**
 * @brief converts a type to string
 * 
 * @param val value
 * @return string of val
 */
string str(type val);
~~~

**_This is not a prototype as implemented they use some trick on macros and _Generic to achive this_**

A Basic Example,

~~~c
#include "inout.h"

int main()
{
    // Here get and str is unnessery because it is alderdy string but may help begineers
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
~~~

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
