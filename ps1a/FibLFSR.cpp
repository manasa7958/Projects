#include <iostream>
#include <string>
#include <stdexcept>
#include "FibLFSR.hpp"

namespace PhotoMagic {

FibLFSR::FibLFSR(const std::string& seed) {
    /*if (seed.length() != 16 || seed.find_first_not_of("01") != std::string::npos) {
        throw std::invalid_argument("Seed should be 16-bits");
    }
    registerBits = seed;*/
}

int FibLFSR::step() {
    /*int bit0 = registerBits[0] - '0';
    int bit1 = registerBits[TAP1] - '0';
    int bi2 = registerBits[TAP2] - '0';
    int bit3 = registerBits[TAP3] - '0';
    int newBit = bit0 ^ bit1 ^ bit2 ^ bit3;
    registerBits = registerBits.substr(1) + std::to_string(newBit);*/
    return 0;
}

int FibLFSR::generate(int k) {
    /*if (k <= 0) {
        throw std::invalid_argument("k should be greater than 0");
    }

    int result = 0;
    for (int i = 0; i < k; i++) {
        int bit = step();
        std::cout << bit;
        result = (result << 1) | bit;
    }*/
    return 0;
}

std::ostream& operator<<(std::ostream& os, const FibLFSR& lfsr) {
    /*os << lfsr.registerBits;*/
    return os;
}
}
