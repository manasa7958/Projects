// Copyright 2025 Manasa Praveen
#pragma once
#include <iostream>
#include <algorithm>
#include "FibLFSR.hpp"
#include <SFML/Graphics.hpp>


namespace PhotoMagic {
void transform(sf::Image& img, FibLFSR* lfsr);
}
