// Copyright 2025 Manasa Praveen
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

int main() {
  // Demo Code
  sf::RenderWindow demoWindow(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  // Extended Code - Idea is a spaceship going into space, New feature add some
  // audio for takeoff
  sf::RenderWindow window(sf::VideoMode(800, 600),
                          "Rocket launch is a success!");

  // Loading spaceship sprite
  sf::Texture texture;
  // Error if image doesn't load
  if (!texture.loadFromFile("sprite.png")) {
    std::cerr << "Error! Image could not be loaded" << std::endl;
    return -1;
  }
  sf::Sprite sprite(texture);
  sprite.setScale(0.3f, 0.3f);
  float speed = 1.f;  // speed for sprite

  // Load launch music
  sf::Music music;
  // Error if image doesn't load
  if (!music.openFromFile("launch.wav")) {
    std::cerr << "Error! Audio could not be loaded" << std::endl;
    return -1;
  }
  music.play();

  sf::Clock clock;
  sf::Color color = sf::Color(165, 229, 255);

  while (demoWindow.isOpen() || window.isOpen()) {
    sf::Event event;
    
    while (demoWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        demoWindow.close();
      }
    }
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    if (clock.getElapsedTime().asSeconds() > 4.0f) {
      color = sf::Color(0, 71, 100);
      window.clear(color);  // changing background color to Storm
    }

    // Responding to keystrokes
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      sprite.move(-speed, 0.0f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      sprite.move(0.0f, -speed);  // weird but the idea is we start at the top
                                     // left corner and +y means you move down
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      sprite.move(0.0f, speed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      sprite.move(speed, 0.0f);
    }
    demoWindow.clear();
    demoWindow.draw(shape);
    demoWindow.display();

    window.clear(color);  // changing background color to Lambent
    window.draw(sprite);
    window.display();
  }
  return 0;
}
