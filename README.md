<!-- PROJECT LOGO -->
<br />
<p align="center">
  <h3 align="center">libio</h3>
  <p align="center">
    Easy Input Output Library For C
    <br />
    <a href="https://srilakshmikanthanp.github.io/libio/docs/"><strong>Explore the docs »</strong></a>
    <br />
    <a href="https://github.com/srilakshmikanthanp/libio/issues">Report Bug</a>
    ·
    <a href="https://github.com/srilakshmikanthanp/libio/issues">Request Feature</a>
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

## Warning ⚠️

I made this library for fun and for begineers NOT FOR PRODUCTION because this library use much space on heap that going to relesed only relesed afer main

<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

~~~shell
git clone https://github.com/srilakshmikanthanp/libio/
~~~

### Installation

This is Header only library so just download [libio.h](src/srilakshmikanthanp/libio.h).

<!-- USAGE EXAMPLES -->
## Usage

Usage is very easy, a sample whould be,

~~~c
#include "libio.h"

int main()
{
    int a = input(int, "Enter a : ");
    int b = input(int, "Enter a : ");

    print("Sum = ", str(a+b));

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

Project Link: [https://github.com/srilakshmikanthanp/libio](https://github.com/srilakshmikanthanp/libio)