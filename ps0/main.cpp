#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
	// Demo Code
	sf::RenderWindow demoWindow(sf::VideoMode({200, 200}), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	//Extended Code - Idea is a spaceship going into space, New feature add some audio for takeoff and background changes in light blue to navy/black
	sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML works!");
	
	//Loading spaceship sprite
	const sf::Texture texture("spaceship.png");
	sf::Sprite sprite(texture);

	// Load a music to play
    	sf::Music music("launch.wav");
	
	// Play the music
	music.play();
	
	while (demoWindow.isOpen() && window.isOpen())
	{
		while (const std::optional event = demoWindow.pollEvent() || const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
				demoWindow.close();
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
