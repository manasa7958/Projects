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

    friend std::ostream& operator<<(std::ostream&, const FibLFSR& lfsr);

 private:
    std:: string registerBits;

    static const int TAP1 = 13;
    static const int TAP2 = 12;
    static const int TAP3 = 10;
};


}  // namespace PhotoMagic
