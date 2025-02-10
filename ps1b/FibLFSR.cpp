// Copyright 2025 Manasa Praveen
#include "FibLFSR.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

namespace PhotoMagic {

FibLFSR::FibLFSR(const std::string& seed) {
  if (seed.length() != 16) {
    throw std::invalid_argument("Seed should be 16-bits");  // For length
  }
  if (!std::all_of(seed.begin(), seed.end(),
                   [](char c) { return c == '0' || c == '1'; })) {
    throw std::invalid_argument(
        "Seed should contain 0 and 1 only");  // For valid characters
  }
  registerBits =
      seed;  // was gonna try storing as integers but I just did string
}
int FibLFSR::step() {
  int leftBit = registerBits[0] - '0';
  int tap13 =
      registerBits[2] - '0';  // index is 2 at position 13 as seen in photo
  int tap12 =
      registerBits[3] - '0';  // index is 3 at position 12 as seen in photo
  int tap10 =
      registerBits[5] - '0';  // index is 5 at position 10 as seen in photo
  int newBit = leftBit ^ tap13 ^ tap12 ^ tap10;  // XOR here
  registerBits = registerBits.substr(1) + std::to_string(newBit);
  return newBit;
}

int FibLFSR::generate(int steps) {
  if (steps < 0) {
    throw std::invalid_argument("Number of steps should be positive");
  }
  int answer = 0;
  for (int i = 0; i < steps; ++i) {
    answer = (answer << 1) | step();  // adding new bit
  }
  return answer;
}
std::ostream& operator<<(std::ostream& os, const FibLFSR& lfsr) {
  os << lfsr.registerBits;
  return os;
}
}  // namespace PhotoMagic
