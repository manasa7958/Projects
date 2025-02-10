// Copyright 2025 Manasa Praveen
#pragma once

#include <SFML/Graphics.hpp>

#include "FibLFSR.hpp"

namespace PhotoMagic {
void transform(sf::Image& img, FibLFSR* lfsr);
}
