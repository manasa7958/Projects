#include <iostream>
#include <string>
#include <stdexcept>
#include "FibLFSR.hpp"

namespace PhotoMagic {

FibLFSR::FibLFSR(const std::string& seed) {
    if (seed.length() != 16) {
        throw std::invalid_argument("Seed should be 16-bits"); //check to see seed is 16 bits
    }
    if (!std::all_of(seed.begin(), seed.end(), [](char c) { return c == '0' || c == '1'; })) {
        throw std::invalid_argument("Seed should contain 0 and 1 only"); //check to see seed contains only 1 and 0
    }
    for (char c : seed) {
        reg.push_back(c - '0'); //converting seed to integers
    }
}
int FibLFSR::step() {
    int new_bit = reg[0];
    for (int tap : taps) {
        new_bit ^= reg[tap]; 
    }
    reg.erase(reg.begin());
    reg.push_back(new_bit);
    return new_bit;
}

int FibLFSR::generate(int k) {
    if (k < 0) {
        throw std::invalid_argument("Number of steps (k) must be non-negative.");
    }
    int result = 0;
    for (int i = 0; i < k; ++i) {
        result = (result << 1) | step(); // Shift result left and add new bit
    }
    return result;
}
std::ostream& operator<<(std::ostream& os, const FibLFSR& lfsr) {
    for (int bit : lfsr.reg) {
        os << bit;
    }
    return os;
}
