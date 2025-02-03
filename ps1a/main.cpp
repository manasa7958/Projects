#include "FibLFSR.hpp"
#include <iostream>

int main() {
    PhotoMagic::FibLFSR lfsr("1011011000110110");

    std::cout << "Initial LFSR state: " << lfsr << std::endl;

    std::cout << "Stepping 10 times: ";
    for (int i = 0; i < 10; i++) {
        std::cout << lfsr.step();
    }
    std::cout << std::endl;

    std::cout << "LFSR after steps: " << lfsr << std::endl;

    int generated = lfsr.generate(5);
    std::cout << "Generated 5-bit integer: " << generated << std::endl;

    return 0;
}

