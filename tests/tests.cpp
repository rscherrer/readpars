#define BOOST_TEST_DYNAMIC_LINK
#define BOOST_TEST_MODULE Main

// Here we test all the uses and misuses of the program. These mostly have to
// with calling the program, passing arguments, reading from and writing to
// files, and error handling.

#include "testutils.hpp"
#include "../src/MAIN.hpp"
#include <boost/test/unit_test.hpp>

// Test that the simulation runs
BOOST_AUTO_TEST_CASE(useCase) {

    // Write a parameter file
    tst::write("parameters.txt", "ngenes 4\nmutrate 0.01\nnoise 0\ngenes 1.0 1.2 3.5 2.0");

    // Check that the program runs
    BOOST_CHECK_NO_THROW(doMain());

    // Remove files
    std::remove("parameters.txt");

}

// Test with reader error
BOOST_AUTO_TEST_CASE(abuseCase) {

    // Write a parameter file
    tst::write("parameters.txt", "unknown 1");

    // Check error
    tst::checkError([&] {

        doMain();

    }, "Invalid parameter: unknown in line 1 of file parameters.txt");


    // Remove files
    std::remove("parameters.txt");

}