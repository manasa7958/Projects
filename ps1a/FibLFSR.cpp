#include <iostream>
#include <string>
#include <stdexcept>
#include "FibLFSR.hpp"

namespace PhotoMagic {
    const int FibLFSR::TAP13 = 13;
    const int FibLFSR::TAP12 = 12;
    const int FibLFSR::TAP10 = 10;

FibLFSR::FibLFSR(const std::string& seed) {
    if (seed.length() != 16) {
        throw std::invalid_argument("Seed should be 16-bits"); //For length
    }
    if (!std::all_of(seed.begin(), seed.end(), [](char c) { return c == '0' || c == '1'; })) {
        throw std::invalid_argument("Seed should contain 0 and 1 only");  //For valid characters
    }
    registerBits = seed; //was gonna try storing as integers but I just did string
}
int FibLFSR::step() {
    int leftBit = registerBits[0] - '0';
    int newBit = leftBit ^ (registerBits[TAP13] - '0') ^ (registerBits[TAP12] - '0') ^ (registerBits[TAP10] - '0');
    registerBits = registerBits.substr(1) + std::to_string(newBit);
    return newBit;
    /*int leftBit = registerBits[0] - '0';
    int tap13 = registerBits[TAP13] - '0'; 
    int tap12 = registerBits[TAP12] - '0'; 
    int tap10 = registerBits[TAP10] - '0'; 
    int newBit = leftBit ^ tap13 ^ tap12 ^ tap10; //XOR here
    registerBits = registerBits.substr(1) + std::to_string(newBit);
    return newBit;*/
}

int FibLFSR::generate(int steps) {
    if (steps < 0) {
        throw std::invalid_argument("Number of steps should be non-negative.");
    }
    int result = 0;
    for (int i = 0; i < steps; ++i) {
        result = (result << 1) | step(); // Correct bit accumulation
    }
    return result;
    /*if (steps < 0) {
        throw std::invalid_argument("Number of steps should be positive");
    }
    int answer = 0;
    for (int i = 0; i < steps; ++i) {
        answer = (answer << 1) | step(); //adding new bit
    }
    return answer;*/
}
std::ostream& PhotoMagic::FibLFSR::print(std::ostream& os) const {
    os << registerBits; // Output the registerBits string
    return os;
}
}
