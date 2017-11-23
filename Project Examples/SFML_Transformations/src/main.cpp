
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Started by Ángel on november of 2017                                       *
*                                                                             *
*  This is free software released into the public domain.                     *
*                                                                             *
*  angel.rodriguez@esne.edu                                                   *
*                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Model2D.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace example;

int main()
{
	RenderWindow window(VideoMode(800, 600), "Animation Examples: Transformations", sf::Style::Default, ContextSettings(32));

	window.setVerticalSyncEnabled(true);

	bool running = true;

	Model2D model
	{
		Point3f({ 0, 100, 1 }),
		Point3f({ -50,   0, 1 }),
		Point3f({ 50,   0, 1 })
	};

	model.set_position(400, 300);
	model.set_angular_speed(0.01f);
	model.set_linear_speed(.5f, .25f);

	do
	{
		// Process window events:

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				running = false;
			}
		}

		model.update(0);

		// Render:

		window.clear();

		model.render(window);

		window.display();
	} while (running);

	return EXIT_SUCCESS;
}
