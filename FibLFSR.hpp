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
};

std::ostream& operator<<(std::ostream&, const FibLFSR& lfsr);
}  // namespace PhotoMagic
