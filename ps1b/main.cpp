// Copyright 2025 Manasa Praveen
#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    return -1;
  }

  std::string input = "cat.jpg";
  std::string output = "cat-out.bmp";
  std::string seed = argv[1];

  sf::Image image;
  if (!image.loadFromFile(input)) {
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
