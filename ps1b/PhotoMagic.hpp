// Copyright 2025 Manasa Praveen
#pragma once
#include "FibLFSR.hpp"
#include <algorithm>
#include <SFML/Graphics.hpp>


namespace PhotoMagic {
void transform(sf::Image& img, FibLFSR* lfsr);
}
