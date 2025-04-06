// Copyright Manasa Praveen and Ponita Ty 2025
#include <iostream>
#include <string>
#include <stdexcept>
#include <SFML/System.hpp>
#include "EDistance.hpp"

int main() {
    try {
        std::string s1, s2;

        std::getline(std::cin, s1);
        std::getline(std::cin, s2);

        if (!s1.empty() && s1.back() == '\r') s1.pop_back();
        if (!s2.empty() && s2.back() == '\r') s2.pop_back();

        sf::Clock clock;

        EDistance ed(s1, s2);
        int distance = ed.optDistance();
        std::string alignmentResult = ed.alignment();

        sf::Time t = clock.getElapsedTime();

        std::cout << "Edit distance = " << distance << std::endl;
        std::cout << alignmentResult << std::endl;
        std::cout << "Execution time is " << t.asSeconds() << " seconds" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }

    return 0;
}
