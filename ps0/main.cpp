#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
	// Demo Code
	sf::RenderWindow demoWindow(sf::VideoMode({200, 200}), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	//Extended Code - Idea is a spaceship going into space, New feature add some audio for takeoff
	sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML works!");
	
	//Loading spaceship sprite
	sf::Texture texture;
	// Error if image doesn't load
	if (!texture.loadFromFile("spaceship.png"))
	{
		std::cerr << "Error! Image could not be loaded" << std::endl;
		return -1;
	}
	sf::Sprite sprite(texture);
	float speed = 2.f; //speed for sprite

	// Load launch music
    	sf::Music music;
	// Error if image doesn't load
	if (!music.openFromFile("launch.wav"))
	{
		std::cerr << "Error! Audio could not be loaded" << std::endl;
		return -1;
	}
	
	// Play the music
	music.play();
	
	while (demoWindow.isOpen() || window.isOpen())
	{
		while (const std::optional event = demoWindow.pollEvent())
		{
			if (std::optional event = event->is<sf::Event::Closed>())
			{
				demoWindow.close();
			}
		}
		while (const std::optional event = window.pollEvent())
		{
			if (std::optional event = event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		// Responding to keystrokes
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  
		{
			sprite.move(sf::Vector2f(-speed, 0));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			sprite.move(sf::Vector2f(-speed, 0));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			sprite.move(sf::Vector2f(-speed, 0));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			sprite.move(sf::Vector2f(-speed, 0));
		}
		demoWindow.clear(); 
		demoWindow.draw(shape);
		demoWindow.display();
		
		window.clear(); 
		window.draw(sprite);
		window.display();
	}
}
