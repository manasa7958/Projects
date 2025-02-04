#include <iostream>
#include "FibLFSR.hpp"

int main() {
    PhotoMagic::FibLFSR lfsr("");
    std::cout <<Initl state: " " << lfsr <<std::endl;
    lfsr.step();
    std::cout <<Initl state: " " << lfsr <<std::endl;
    int value = lfsr.generate(5);
    std::cout <<Initl state: " " << lfsr <<std::endl;
    return 0;
}
