// Copyright 2025 Manasa Praveen
#pragma once
#include "FibLFSR.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>

namespace PhotoMagic {
void transform(sf::Image& img, FibLFSR* lfsr);
}
