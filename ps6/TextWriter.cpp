// Copyright Manasa Praveen 2025
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include "RandWriter.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <k> <L>\n";
        return 1;
    }

    size_t k = std::stoi(argv[1]);
    size_t L = std::stoi(argv[2]);

    std::string input((std::istreambuf_iterator<char>(std::cin)),
                      std::istreambuf_iterator<char>());

    input.erase(std::find_if(input.rbegin(), input.rend(), [](char ch) {
        return !std::isspace(static_cast<unsigned char>(ch));
    }).base(), input.end());

    if (input.length() < k) {
        std::cerr << "Error: Input text must be at least k characters long.\n";
        return 1;
    }

    RandWriter rw(input, k);
    std::string start = input.substr(0, k);
    std::cout << rw.generate(start, L) << std::endl;

    return 0;
}
