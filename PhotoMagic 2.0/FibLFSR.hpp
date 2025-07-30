// Copyright 2025 Manasa Praveen
#pragma once

#include <iostream>
#include <string>

namespace PhotoMagic {
class FibLFSR {
 public:
  explicit FibLFSR(const std::string& seed);
  explicit FibLFSR(unsigned int seed);                       // Optional
  static FibLFSR fromPassword(const std::string& password);  // Optional
  int step();
  int generate(int steps);
  friend std::ostream& operator<<(std::ostream&, const FibLFSR& lfsr);

 private:
  std::string registerBits;
};
}  // namespace PhotoMagic
