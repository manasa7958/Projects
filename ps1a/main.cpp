#include "FibLFSR.hpp"
#include <iostream>

int main() {
    PhotoMagic::FibLFSR lfsr("1011011000110110");
    std::cout << "Initial LFSR state: " << lfsr << std::endl;
   
  std::cout << "Stepping 10 times: ";
    for (int i = 0; i < 10; i++) {
        int stepBit = lfsr.step();
        std::cout << stepBit;  // Print each step result
    }
    std::cout << std::endl;

    // Display LFSR after 10 steps
    std::cout << "LFSR after steps: " << lfsr << std::endl;

    // Debugging `generate(5)`
    int generated5 = lfsr.generate(5);
    std::cout << "Generated 5-bit integer: " << generated5 << std::endl;

    // Debugging `generate(1) == step()`
    int stepResult = lfsr.step();
    int generate1Result = lfsr.generate(1);
    std::cout << "Step(): " << stepResult << ", Generate(1): " << generate1Result << std::endl;

    return 0;
}


