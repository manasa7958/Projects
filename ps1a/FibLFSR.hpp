// Copyright 2025 Manasa Praveen
#pragma once

#include <iostream>
#include <string>

namespace PhotoMagic {
class FibLFSR {
 public:
  explicit FibLFSR(const std::string& seed);
  explicit FibLFSR(unsigned int seed);  // Optional
  static FibLFSR fromPassword(const std::string& password);  // Optional
  friend std::ostream& operator<<(std::ostream&, const FibLFSR& lfsr);
  int step();
  int generate(int steps);

 private:
  std::string registerBits;
};
}  // namespace PhotoMagic
