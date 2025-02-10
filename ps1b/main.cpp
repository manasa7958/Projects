// main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"

int main(int argc, char* argv[]) {
    // Check if seed is provided
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <seed>\n";
        return 1;
    }

    std::string inputFile = "cat.jpg";  // Hardcoded input file
    std::string outputFile = "cat-out.png";  // Hardcoded output file
    std::string seed = argv[1];

    // Load input image
    sf::Image image;
    if (!image.loadFromFile(inputFile)) {
        std::cerr << "Error loading file: " << inputFile << "\n";
        return 1;
    }

    // Create a copy for displaying original image
    sf::Image originalImage = image;

    // Create LFSR instance
    try {
        FibLFSR lfsr(seed);

        // Transform the image
        PhotoMagic::transform(image, &lfsr);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    // Display the images
    sf::Vector2u size = image.getSize();
    sf::RenderWindow window1(sf::VideoMode(size.x, size.y), "Original Image");
    sf::RenderWindow window2(sf::VideoMode(size.x, size.y), "Transformed Image");

    sf::Texture texture1, texture2;
    texture1.loadFromImage(originalImage);
    texture2.loadFromImage(image);

    sf::Sprite sprite1(texture1), sprite2(texture2);

    while (window1.isOpen() && window2.isOpen()) {
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window1.close();
        }
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window2.close();
        }

        window1.clear();
        window1.draw(sprite1);
        window1.display();

        window2.clear();
        window2.draw(sprite2);
        window2.display();
    }

    // Save transformed image
    if (!image.saveToFile(outputFile)) {
        std::cerr << "Error saving file: " << outputFile << "\n";
        return 1;
    }

    return 0;
}
