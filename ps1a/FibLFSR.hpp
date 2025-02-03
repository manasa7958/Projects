#pragma once

#include <iostream>
#include <string>

namespace PhotoMagic {
class FibLFSR {
 public:
    explicit FibLFSR(const std::string& seed);
    //explicit FibLFSR(unsigned int seed); // Optional

    //static FibLFSR fromPassword(const std::string& password); // Optional

    int step();
    int generate(int k);
 private:
    std:: string registerBits;

    static const int TAP1;
    static const int TAP2;
    static const int TAP3;
};

std::ostream& operator<<(std::ostream&, const FibLFSR& lfsr);
}  // namespace PhotoMagic
