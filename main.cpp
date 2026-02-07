#include "src/MAIN.hpp"

#include <iostream>

// Main function
int main() {

    // Try to...
    try {
        
        // Run the program
        doMain();

        // Exit
        return 0;

    }
    catch (const std::exception& err) {

        // Catch exceptions
        std::cerr << "Exception: " << err.what() << '\n';

    }
    catch (const char* err) {

        // Catch error messages
        std::cerr << "Exception: " << err << '\n';

    }
    catch (...) {

        // Or unknown errors
        std::cerr << "Unknown Exception\n";

    }

    // Return failure flag if got here
    return 1;

}