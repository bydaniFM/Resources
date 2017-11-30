
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

std::shared_ptr< Model2D > build_robot()
{
	std::shared_ptr< Model2D > node0
	(
		new Model2D
		({
		Point3f({ 0, 150, 1 }),
		Point3f({ -25,   0, 1 }),
		Point3f({ 25,   0, 1 })
	})
	);

	std::shared_ptr< Model2D > node1
	(
		new Model2D
		({
		Point3f({ 0, 100, 1 }),
		Point3f({ -15,   0, 1 }),
		Point3f({ 15,   0, 1 })
	})
	);

	std::shared_ptr< Model2D > node2
	(
		new Model2D
		({
		Point3f({ 0, 75, 1 }),
		Point3f({ -10,  0, 1 }),
		Point3f({ 10,  0, 1 })
	})
	);

	node0->set_child(node1);
	node1->set_child(node2);

	node0->set_position(400, 100);
	node1->set_position(0, 150);
	node2->set_position(0, 100);

	return node0;
}

int main()
{
	RenderWindow window(VideoMode(800, 600), "Animation Examples: Transformations", sf::Style::Default, ContextSettings(32));

	window.setVerticalSyncEnabled(true);

	bool running = true;

	std::shared_ptr< Model2D > robot = build_robot();

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

		robot->update(0);

		// Render:

		window.clear();

		robot->transform(Transformation2f());
		robot->render(window);

		window.display();
	} while (running);

	return EXIT_SUCCESS;
}
