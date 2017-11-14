
#include <SFML/Graphics.hpp>
#include <math.h>

using sf::Event;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");

	window.setFramerateLimit(60);


	sf::CircleShape shape(50.f);
	shape.setFillColor(sf::Color::Green);

	float speed_x = 5;
	float speed_y = 5;


	sf::CircleShape shape2(50.f);
	shape2.setFillColor(sf::Color::Blue);

	bool drag = false;


	sf::Vector2f mouse_position;

	while (window.isOpen())
	{
		mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed:
				{
					window.close();
					break;
				}

				case Event::Resized:
				{
					//view.resize(window_size.x, window_size.y);

					break;
				}

				case Event::KeyPressed:
				{
					//view.on_key(event.key.code);
					break;
				}

				case Event::MouseButtonPressed:
				{
					if (event.mouseButton.button == sf::Mouse::Left) {
						if((mouse_position.x - mouse_position.y)^2 + (shape.getPosition().x + shape.getPosition().y)^2 < shape.getRadius()^2)
						drag = true;
					}
					break;
				}

				case Event::MouseButtonReleased:
				{
					if (event.mouseButton.button == sf::Mouse::Left) {
						
						drag = false;
					}
					//view.on_click(event.mouseButton.x, event.mouseButton.y, false);
					break;
				}

				case Event::MouseMoved:
				{
					//view.on_drag(event.mouseMove.x, event.mouseMove.y);
					break;
				}
			}

		}

		shape.move(speed_x, speed_y);

		if (shape.getPosition().x + shape.getRadius() * 2 >= window.getSize().x || shape.getPosition().x <= 0) {
			speed_x = -speed_x;
		}
		if (shape.getPosition().y + shape.getRadius() * 2 >= window.getSize().y || shape.getPosition().y <= 0) {
			speed_y = -speed_y;
		}

		if (drag) {
			shape2.setPosition(mouse_position);
		}


		window.clear();
		window.draw(shape);
		window.draw(shape2);
		window.display();
	}

	return 0;
}
