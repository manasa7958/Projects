// Copyright 2025 Manasa Praveen
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"

int main(int argc, char* argv[]) {
  if (argc != 4) {
    return -1;
  }
  
  std::string input = argv[1];
  std::string output = argv[2];
  std::string seed = argv[3];

  sf::Image image;
  if (!image.loadFromFile(input)) {
    std::cerr << "Error loading input file";
    return -1;
  }

  sf::Image og = image;
  
  PhotoMagic::FibLFSR lfsr(seed);
  PhotoMagic::transform(image, &lfsr);

  sf::Vector2u size = image.getSize();
  sf::RenderWindow window(sf::VideoMode(size.x, size.y), "Original Image");
  sf::RenderWindow newWindow(sf::VideoMode(size.x, size.y),
                             "Transformed Image");

  sf::Texture ogTexture, newTexture;
  ogTexture.loadFromImage(og);
  newTexture.loadFromImage(image);

  sf::Sprite ogSprite(ogTexture), newSprite(newTexture);

  while (window.isOpen() && newWindow.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    while (newWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed) newWindow.close();
    }

    window.clear();
    window.draw(ogSprite);
    window.display();

    newWindow.clear();
    newWindow.draw(newSprite);
    newWindow.display();
  }

  if (!image.saveToFile(output)) {
    return -1;
  }

  return 0;
}
