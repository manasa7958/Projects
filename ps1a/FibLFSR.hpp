#pragma once

#include <iostream>
#include <string>

namespace PhotoMagic {
class FibLFSR {
 public:
    explicit FibLFSR(const std::string& seed);
    explicit FibLFSR(unsigned int seed); // Optional

    static FibLFSR fromPassword(const std::string& password); // Optional

    int step();
    int generate(int k);
 private:
    std:: string register_state;

    static int TAP1;
    static int TAP2;
    static int TAP3;
};

std::ostream& operator<<(std::ostream&, const FibLFSR& lfsr);
}  // namespace PhotoMagic
