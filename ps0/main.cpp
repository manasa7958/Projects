#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
	// Responding to keystrokes
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		shape.move(0.0f, -2.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		shape.move(0.0f, 2.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		shape.move(-2.0f, 0.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		shape.move(2.0f, 0.0f);
	}

        window.clear();
        window.draw(shape);
        window.display();
    }
}
