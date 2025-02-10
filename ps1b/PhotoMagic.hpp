// Copyright 2025 Manasa Praveen
#pragma once
#include "FibLFSR.hpp"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>


namespace PhotoMagic {
void transform(sf::Image& img, FibLFSR* lfsr);
}
