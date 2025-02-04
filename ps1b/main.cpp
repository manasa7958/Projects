// main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input-file> <output-file> <seed>\n";
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    std::string seed = argv[3];

    sf::Image image;
    if (!image.loadFromFile(inputFile)) {
        std::cerr << "Error loading file: " << inputFile << "\n";
        return 1;
    }

    FibLFSR lfsr(seed);

    // Display Original Image
    sf::RenderWindow window1(sf::VideoMode(image.getSize().x, image.getSize().y), "Original Image");
    sf::Texture texture1;
    texture1.loadFromImage(image);
    sf::Sprite sprite1(texture1);

    // Transform Image
    PhotoMagic::transform(image, &lfsr);

    // Display Transformed Image
    sf::RenderWindow window2(sf::VideoMode(image.getSize().x, image.getSize().y), "Transformed Image");
    sf::Texture texture2;
    texture2.loadFromImage(image);
    sf::Sprite sprite2(texture2);

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

    if (!image.saveToFile(outputFile)) {
        std::cerr << "Error saving file: " << outputFile << "\n";
        return 1;
    }

    return 0;
}
