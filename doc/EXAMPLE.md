## Minimal example

Here we go over our minimal example setup used to showcase the workings of the library.

### Installation

This program must be compiled. It is written in C++ and can be built using any modern C++ compiler and build system. [Here](SETUP.md) we provide an example setup to build the program on several platforms using CMake.

### Usage

This program has a command-line interface. Assuming the name of the compiled executable is `readpars`, use the following command in the terminal from the working directory to run the minimal example:

```shell
./readpars
```

Note that there is no input to this example use case.

### Output

The above command will output to the screen some example values read from a mock parameter file.

### Tests

This program was tested using the [Boost.Test](https://www.boost.org/doc/libs/1_85_0/libs/test/doc/html/index.html) library. All the tests can be found in the `tests/` folder. [Here](TESTS.md) we show how we tested the program locally using our own custom setup.