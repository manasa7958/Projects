#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
	// Demo Code
	sf::RenderWindow demoWindow(sf::VideoMode({200, 200}), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	//Extended Code - Idea is a spaceship going into space, New feature add some audio for takeoff and background changes in light blue to navy/black
	sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML works!");
	
	//Loading spaceship sprite
	sf::Texture texture;
	// Error is image doesn't load
	if (!texture.loadFromFile("spaceship.png"))
	{
		std::cerr << "Error! Image could not be loaded" << std::endl;
		return -1;
	}
	sf::Sprite sprite(texture);

	// Load a music to play
    	sf::Music music;
	// Error is image doesn't load
	if (!music.openFromFile("launch.wav"))
	{
		std::cerr << "Error! Audio could not be loaded" << std::endl;
		return -1;
	}
	
	// Play the music
	music.play();
	
	while (demoWindow.isOpen() && window.isOpen())
	{
		std::Event event;
		while (event = demoWindow.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				demoWindow.close();
			}
		}
		while (event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		// Responding to keystrokes
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  
		{
			sprite.move(0.0f, -2.0f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sprite.move(0.0f, 2.0f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sprite.move(-2.0f, 0.0f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sprite.move(2.0f, 0.0f);
		}
		demoWindow.clear(); 
		demoWindow.draw(shape);
		demoWindow.display();
		
		window.clear(); 
		window.draw(sprite);
		window.display();
	}
}
