
#include <SFML/Graphics.hpp>
#include <SFML\System\Clock.hpp>
#include <SFML\System\Vector2.hpp>
//#include <cmath>

using namespace sf;

Vector2<float> calculateBezier(int num_steps, Vector2<float> points[3]);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");

	window.setFramerateLimit(60);


	sf::CircleShape shape(50.f);
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(50, 50);
	shape.setPosition(128, 128);

	float speed_x = 5;
	float speed_y = 5;


	sf::CircleShape shape2(50.f);
	shape2.setFillColor(sf::Color::Blue);
	shape2.setOrigin(50, 50);
	shape2.setPosition(50, 50);

	bool drag = false;

	sf::CircleShape shape3(30.f);
	shape3.setFillColor(sf::Color::Magenta);
	shape3.setOrigin(15, 15);
	shape3.setPosition(50, 384);
	float C0x = 50.f;
	float C0y = 384.f;
	float C1x = 341.f;
	float C1y = -341.f;
	float C2x = 682.f;
	float C2y = 700.f * 2;
	float C3x = 1000.f;
	float C3y = 341.f;
	float t = 0.f;


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
						if(sqrt(pow((mouse_position.x - shape2.getPosition().x), 2) + pow((mouse_position.y - shape2.getPosition().y), 2)) < shape2.getRadius())
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

		if (shape.getPosition().x + shape.getRadius() >= window.getSize().x || shape.getPosition().x - shape.getRadius() <= 0) {
			speed_x = -speed_x;
		}
		if (shape.getPosition().y + shape.getRadius() >= window.getSize().y || shape.getPosition().y - shape.getRadius() <= 0) {
			speed_y = -speed_y;
		}

		if (drag) {
			shape2.setPosition(mouse_position);
		}

		if (sqrt(pow((shape.getPosition().x - shape2.getPosition().x), 2) + pow((shape.getPosition().y - shape2.getPosition().y), 2)) < (shape.getRadius() + shape2.getRadius())) {
			sf::Color color(rand() % UINT8_MAX,rand()%UINT8_MAX, rand() % UINT8_MAX, UINT8_MAX);
			sf::Color color2(rand() % UINT8_MAX, rand() % UINT8_MAX, rand() % UINT8_MAX, UINT8_MAX);
			shape.setFillColor(color);
			shape2.setFillColor(color2);
		}

		float x3;
		float y3;

		float k = 1 - t;
		x3 = k*k*k*C0x +
			3 * k*k*t*C1x +
			3 * k*t*t*C2x +
			t*t*t*C3x;
		y3 = k*k*k*C0y +
			3 * k*k*t*C1y +
			3 * k*t*t*C2y +
			t*t*t*C3y;
		t += 0.005f;	//incremento = 1/num_muestras
		shape3.setPosition(x3, y3);

		window.clear();
		window.draw(shape);
		window.draw(shape2);
		window.draw(shape3);
		window.display();
	}

	return 0;
}
