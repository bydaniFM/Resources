
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
		new Model2D({ Point3f({ 0, 150, 1 }), Point3f({ -25, 0, 1 }), Point3f({ 25, 0, 1 }) })
	);

	std::shared_ptr< Model2D > node1
	(
		new Model2D({ Point3f({ 0, 100, 1 }), Point3f({ -15, 0, 1 }), Point3f({ 15, 0, 1 }) })
	);

	std::shared_ptr< Model2D > node2
	(
		new Model2D({ Point3f({ 0, 100, 1 }), Point3f({ -15, 0, 1 }), Point3f({ 15, 0, 1 }) })
	);

	std::shared_ptr< Model2D > node3
	(
		new Model2D({ Point3f({ 0,  75, 1 }), Point3f({ -10, 0, 1 }), Point3f({ 10, 0, 1 }) })
	);

	node0->set_child(node1);
	node1->set_child(node2);
	node2->set_child(node3);

	node0->set_position(400, 100);
	node0->set_min_angle(-1.57f);
	node0->set_max_angle(+1.57f);

	node1->set_position(0, 150);
	node1->set_min_angle(-1.57f);
	node1->set_max_angle(+1.57f);

	node2->set_position(0, 100);
	node2->set_min_angle(-1.57f);
	node2->set_max_angle(+1.57f);

	node3->set_position(0, 100);
	node3->set_min_angle(-1.57f);
	node3->set_max_angle(+1.57f);
	node3->set_reference(Point2f({ 0.f, 75.f }));

	return node0;
}

int main()
{
	RenderWindow window(VideoMode(800, 600), "Animation Examples: Inverse Kinematics", sf::Style::Default, ContextSettings(32));

	window.setVerticalSyncEnabled(true);

	bool running = true;

	std::shared_ptr< Model2D > robot = build_robot();
	sf::CircleShape target(10);

	target.setFillColor(sf::Color::Red);
	target.setPosition(-100, -100);

	do
	{
		// Se procesan los eventos que llegan a la ventana:

		Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				running = false;
				break;
			}

			case Event::MouseButtonPressed:
			{
				Point2f target_location({ event.mouseButton.x, event.mouseButton.y });

				target.setPosition(target_location.x() - target.getRadius(), target_location.y() - target.getRadius());

				robot->solve_inverse_kinematics(target_location, 7, 5.f);

				break;
			}
			}
		}

		// Se actuliza la animación del robot (en intervalos de tiempo regulares gracias a la llamada a sleep()):

		robot->update();

		// Se dibuja la escena (target y robot):

		window.clear();
		window.draw(target);

		robot->transform();
		robot->render(window);

		window.display();

		// Se detiene la ejecución unos milisegundos para conseguir una tasa de fotogramas estable:

		sleep(milliseconds(15));
	} while (running);

	return EXIT_SUCCESS;
}
