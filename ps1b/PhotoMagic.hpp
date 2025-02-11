// Copyright 2025 Manasa Praveen
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "FibLFSR.hpp"



namespace PhotoMagic {
void transform(sf::Image& img, FibLFSR* lfsr);
}
