#include <iostream>
#include <string>
#include <stdexcept>
#include "FibLFSR.hpp"

namespace PhotoMagic {

FibLFSR::FibLFSR(const std::string& seed) {}

int FibLFSR::step() {
    return 0;
}

int FibLFSR::generate(int k) {
    return 0;
}

std::ostream& operator<<(std::ostream& os, const FibLFSR& lfsr) {
    return os;
}
}
