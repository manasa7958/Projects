// PhotoMagic.cpp
#include "PhotoMagic.hpp"

namespace PhotoMagic {

void transform(sf::Image& image, FibLFSR* lfsr) {
    sf::Vector2u size = image.getSize();
    
    for (unsigned int x = 0; x < size.x; ++x) {
        for (unsigned int y = 0; y < size.y; ++y) {
            sf::Color pixel = image.getPixel(x, y);
            
            pixel.r ^= lfsr->generate(8);
            pixel.g ^= lfsr->generate(8);
            pixel.b ^= lfsr->generate(8);
            
            image.setPixel(x, y, pixel);
        }
    }
}

} // namespace PhotoMagic
