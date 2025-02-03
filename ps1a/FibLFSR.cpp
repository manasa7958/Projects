#include <iostream>
#include <string>

#include "FibLFSR.hpp"

namespace PhotoMagic {
    int FibLFSR::TAP1 = 13;
    int FibLFSR::TAP2 = 12;
    int FibLFSR::TAP3 = 10;

FibLFSR::::FibLFSR(const std::string& seed) {
    if (seed.length() != 16 || seed.find_first_not_of("01") != std::string::npos) {
        throw std::invalid_argument("Seed must be a 16-bit binary string.");
    }
    registerBits = seed;
}
int FibLFSR::step() {
    int newBit = (registerBits[0] - '0') ^ (registerBits[2] - '0') ^ (registerBits[3] - '0') ^ (registerBits[5] - '0');
    registerBits = registerBits.substr(1) + std::to_string(newBit);
    return newBit;
}

int FibLFSR::generate(int k) {
    int result = 0;
    for (int i = 0; i < k; i++) {
        result = (result << 1) | step();
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const FibLFSR& lfsr) {
    os << lfsr.registerBits;
    return os;
}
}
