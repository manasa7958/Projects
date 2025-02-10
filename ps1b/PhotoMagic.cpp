// Copyright 2025 Manasa Praveen
#include "PhotoMagic.hpp"
#include <algorithm>

namespace PhotoMagic {

void transform(sf::Image& img, FibLFSR* lfsr) {
  sf::Vector2u size = img.getSize();

  for (unsigned int x = 0; x < size.x; ++x) {
    for (unsigned int y = 0; y < size.y; ++y) {
      sf::Color pixel = img.getPixel(x, y);

      pixel.r ^= lfsr->generate(8);
      pixel.g ^= lfsr->generate(8);
      pixel.b ^= lfsr->generate(8);

      img.setPixel(x, y, pixel);
    }
  }
}

}  // namespace PhotoMagic
