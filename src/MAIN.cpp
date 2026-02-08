// This is the main simulation script. The core of the program has been
// encapsulated into a function called doMain(), so its proper behavior
// can be tested in different use cases in our tests.

#include "MAIN.hpp"

// Function to check that a number is positive
template <typename T>
std::string checkpositive(const T &x) { return x >= 0.0 ? "" : "must be positive"; }

// Function to check that a number is strictly positive
template <typename T>
std::string checkstrictpos(const T &x) { return x > 0.0 ? "" : "must be strictly positive"; }

// Function to check that a number is a proportion
template <typename T>
std::string checkprop(const T &x) { return x >= 0.0 && x <= 1.0 ? "" : "must be between zero and one"; }

// Note: In this implementation it is important that the function returns a
// string indicating the error message to display, not just true or false.

// Main function
void doMain() {

	// Declare containers
    int ngenes;
    double mutrate;
    double noise;

    // Vectors
    std::vector<double> genes;

    // Initialize a reader
    ReadPars r("parameters.txt");

    // Open the file
    r.open();

    // For each line in the file...
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
        if (name == "ngenes") r.readvalue<int>(ngenes, checkstrictpos<int>);
        else if (name == "mutrate") r.readvalue<double>(mutrate, checkprop<double>);
        else if (name == "noise") r.readvalue<double>(noise, checkpositive<double>);
        else if (name == "genes") r.readvalues<double>(genes, ngenes, checkstrictpos<double>);
        else
            r.readerror();

        // Note: Remember to indicate the type of the input when calling the checking function,
        // if the checking function is templated (as it is here).

    }

    // Verbose
    std::cout << "Input read in successfully:\n";
    std::cout << "ngenes: " << ngenes << '\n';
    std::cout << "mutrate: " << mutrate << '\n';
    std::cout << "noise: " << noise << '\n';
    std::cout << "genes:";
    for (double x : genes) std::cout << ' ' << x;
    std::cout << '\n';
    
}
