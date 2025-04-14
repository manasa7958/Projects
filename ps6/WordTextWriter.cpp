// Copyright Manasa Praveen 2025
#include <iostream>
#include <string>
#include "WordWriter.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <k> <L>\n";
        return 1;
    }

    size_t k = std::stoi(argv[1]);
    size_t L = std::stoi(argv[2]);

    std::string input((std::istreambuf_iterator<char>(std::cin)),
                      std::istreambuf_iterator<char>());

    WordWriter ww(input, k);
    std::string start;
    std::istringstream iss(input);
    std::string word;
    for (size_t i = 0; i < k && iss >> word; ++i) {
        if (i > 0) start += " ";
        start += word;
    }
    std::cout << ww.generate(start, L) << std::endl;
    return 0;
}
