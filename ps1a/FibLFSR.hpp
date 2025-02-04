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
    std::ostream& print(std::ostream& os) const;

 private:
   std::string registerBits;
};

inline std::ostream& operator<<(std::ostream& os, const FibLFSR& lfsr){
   return lfsr.print(os);
}
}  // namespace PhotoMagic
