# ReadPars: Simple C++ library to read parameter text files

This repository contains the code for a C++ library that may be used for reading parameter files into simulation programs, as well as a minimal example setup to illustrate how the library may be incorporated in a C++ project.

![Build](https://img.shields.io/badge/build-passing-brightgreen)
![Tests](https://img.shields.io/badge/tests-passing-brightgreen)
![Coverage](https://img.shields.io/badge/coverage-100%25-brightgreen)

## Description

The library defines the ReadPars class, an object designed to read parameters from an input text file. Assuming that parameters are provided as a succession of parameter names followed by their value(s), for example:

```
# parameters.txt
ngenes 4
mutrate 0.01
noise 0
genes 1.0 1.2 3.5 2.0
```

then, a ReadPars can open such file, read each line as a separate parameter, perform requested checks on the input value(s), and store the input into specified container variables.

## How to

Simply copy the header `src/readpars.hpp` and the associated source file `src/readpars.cpp` in your own project, make sure your C++ code and build setup can locate and include these files without a hitch, and you should be good to go. In this repository, we provide an example, minimal setup showcasing how to use the library. [Here](doc/EXAMPLE.md) we explain how to compile this minimal setup. For concrete examples of how to use the functions of the library, please refer to the source file `src/MAIN.cpp`.

## Workflow

First, a ReadPars must be instantiated with the name of a parameter input file as argument:

```cpp
ReadPars r("parameters.txt");
```

The file then needs to be open, using:

```cpp
r.open();
```

This will return an error if the file cannot be open, or if the file is empty. Once the file is open, several functions can be used and combined in various ways. One typical workflow is to loop through the lines in the file and collect parameters and their values this way:

```cpp
// Prepare to read parameters
int x;
double y, z;

// For each line in the file
while (!r.iseof()) {

    // Read a line
    r.readline();

    // Skip empty line
    if (r.isempty()) continue;

    // Skip if comment line
    if (r.iscomment()) continue;
        
    // Current parameter name 
    std::string name = r.getname();

    // Read the parameter value(s)
    if (name == "x") r.readvalue<int>(x);
    else if (name == "y") r.readvalue<double>(y);
    else if (name == "z") r.readvalue<double>(z);
    else
        r.readerror();
    
}
```

Here, `iseof()` tells us whether we have reached the end of the file, `readline()` reads the entire line as a string, `isempty()` tells us whether the line is empty, `iscomment()` tells us whether it is a comment (starting with **#**) and should be ignored, and `getname()` reads the first term on the line, expecting a character string standing for the name of the parameter. Following that, the if-else statement reads the next incoming value and stores it into the right parameter (here `x`, `y` or `z`). In this example, the name of the next parameter, read by `getname()`, is used to match a series of expected parameter names, and triggers an error otherwise. 

The key function to read the value of a parameter and store it into the appropriate container is:

```cpp
r.readvalue<...>(param, checkfun);
```

This function takes the `param` object (which must have already been defined), and tries to coerce the next value on the line of text into this object, provided that the type of the variable to coerce is given (in place of `<...>`, e.g. `<double>` or `<int>`). If the next input cannot be coerced (e.g. a character string being provided in place of a numerical value if `param` is of type `double`, or a negative number in place of a natural integer if `param` is of type `unsigned int`), the ReadPars will error with a message indicating what went wrong. 

Once `param` has been read, the (optional) checking function `checkfun()` is applied to it. This function must also exist (or be provided as a lambda), and must be defined in such a way that `checkfun(param)` should return an **empty string** if `param` has the expected features, or an informative error message otherwise. For example:

```cpp
// Checker function
std::string checkpositive(double x) { x >= 0.0 ? "" : "must be positive"; }
```

will return an empty string (`""`) when the input `double` is zero or more. When used in combination with the ReadPars's `readvalue<>()` function, the following:

```cpp
double param;
r.readvalue<double>(param, checkpositive);
```

will read the next value into `x`, but error if the provided number is not positive, saying something like:

```
Parameter param must be positive on line 1 of file parameters.txt
```

The other function that can be used to read parameter values is this one:

```cpp
r.readvalues<...>(parvec, n, checkfun);
```

where this time, `parvec` is a vector that should contain `n` values, all of type `...`, and all checkable with the `checkfun` function. For example:

```cpp
std::vector<double> genes;
r.readvalues<double>(genes, 4u, checkpositive);
```

will read the 4 values next values into the `genes` vector, and error if any of these values is not a positive number.

Note that this can help to catch parameter errors, as simply reading input into variables (e.g. `fstream`'s `>>` operator) can trigger cryptic conversions that do not crash a program. For example, negative numbers (provided as text) will tend to be converted into very large positive integers when forced to be coerced to `unsigned int` (and may therefore go unnoticed).

If a given parameter does not match any of the ones expected by the program (e.g. reaching the end of an if-else series without a match), one can use the following function as default:

```cpp
r.readerror();
```

to say that some invalid parameter was encountered, for example:

```
Invalid parameter: blabla in line 1 of file parameters.txt
```

Finally, to close the input file, simply use:

```cpp
r.close();
```

It is worth noting that the exact way in which these functions are combined needs not be as presented here or in `src/MAIN.cpp`. These are merely examples, which may be adapted according to the needs of the user.

## About

This code is written in C++20. It was developed on Ubuntu Linux 24.04 LTS, making mostly use of [Visual Studio Code](https://code.visualstudio.com/) 1.99.0 ([C/C++ Extension Pack](https://marketplace.visualstudio.com/items/?itemName=ms-vscode.cpptools-extension-pack) 1.3.1). [CMake](https://cmake.org/) 3.28.3 was used as build system, with [g++](https://gcc.gnu.org/) 13.3.0 as compiler. [GDB](https://www.gnu.org/savannah-checkouts/gnu/gdb/index.html) 15.0.50.20240403 was used for debugging. Tests (see [here](doc/TESTS.md)) were written with [Boost.Test](https://www.boost.org/doc/libs/1_85_0/libs/test/doc/html/index.html) 1.87, itself retrieved with [Git](https://git-scm.com/) 2.43.0 and [vcpkg](https://github.com/microsoft/vcpkg) 2025.04.09. Memory use was checked with [Valgrind](https://valgrind.org/) 3.22.0. Code coverage was analyzed with [LCOV](https://github.com/linux-test-project/lcov) 2.0-1. Profiling was performed with [gprof](https://ftp.gnu.org/old-gnu/Manuals/gprof-2.9.1/html_mono/gprof.html) 2.42. (See the `dev/` folder and [this page](dev/README.md) for details about the checks performed.) During development, occasional use was also made of [ChatGPT](https://chatgpt.com/) and [GitHub Copilot](https://github.com/features/copilot).

## Links

The present library has been used (in this form or slightly modified) in the following, non-exhaustive list of projects:

* [reschoice](https://github.com/rscherrer/reschoice): evolutionary simulation of ecological specialization under informed resource choice
* [brachypode](https://github.com/rscherrer/brachypode): evolutionary simulation of adaptation to a changing climate in a facilitated system
* [porpgame](https://github.com/rscherrer/porpgame): simulation of a board game in preparation

## Permissions

Copyright (c) 2025-2026, Raphaël Scherrer. 

This code is licensed under the MIT license. See [license file](LICENSE.txt) for details. This code comes with no guarantee whatsoever.
