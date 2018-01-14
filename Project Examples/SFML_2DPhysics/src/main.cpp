
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Started by Ángel on april of 2016                                          *
*                                                                             *
*  This is free software released into the public domain.                     *
*                                                                             *
*  angel.rodriguez@esne.edu                                                   *
*                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <memory>
#include <vector>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Renderer.hpp"

using namespace sf;
using namespace std;
using namespace physics2D;

namespace
{

	/** En Box2D las coordenadas Y crecen hacia arriba y en SFML crecen hacia abajo desde el borde superior.
	** Esta función se encarga de convertir el sistema de coordenadas para que la escena no se vea invertida.
	**/
	/*
	inline Vector2f box2d_position_to_sfml_position(const b2Vec2 & box2d_position, float window_height)
	{
		return Vector2f(box2d_position.x, window_height - box2d_position.y);
	}

	void render(b2World & physics_world, RenderWindow & window)
	{
		// Se cachea el alto de la ventana en una variable local:

		float window_height = (float)window.getSize().y;

		// Se recorre toda la lista de bodies de physics_world:

		for (b2Body * body = physics_world.GetBodyList(); body != nullptr; body = body->GetNext())
		{
			// Se obtiene el transform del body:

			const b2Transform & body_transform = body->GetTransform();

			// Se recorre la lista de fixtures del body:

			for (b2Fixture * fixture = body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext())
			{
				// Se obtiene el tipo de forma de la fixture:

				b2Shape::Type shape_type = fixture->GetShape()->GetType();

				if (shape_type == b2Shape::e_circle)
				{
					// Se crea un CircleShape a partir de los atributos de la forma de la fixture y del body:
					// En SFML el centro de un círculo no está en su position. Su position es la esquina superior izquierda
					// del cuadrado en el que está inscrito. Por eso a position se le resta el radio tanto en X como en Y.

					b2CircleShape * circle = dynamic_cast< b2CircleShape * >(fixture->GetShape());

					float  radius = circle->m_radius;
					b2Vec2 center = circle->m_p;

					CircleShape shape;

					shape.setPosition(box2d_position_to_sfml_position(b2Mul(body_transform, center), window_height) - Vector2f(radius, radius));
					shape.setFillColor(Color::Blue);
					shape.setRadius(radius);

					window.draw(shape);
				}
				else
					if (shape_type == b2Shape::e_edge)
					{
						// Se toman los dos vértices del segmento y se ajusta su posición usando el transform del body.
						// Los vértices resultantes se convierten y se ponen en un array para finalmente dibujar el segmento
						// que los une usando la sobrecarga del método draw() que permite dibujar primitivas de OpenGL a
						// partir de datos de vértices.

						b2EdgeShape * edge = dynamic_cast< b2EdgeShape * >(fixture->GetShape());

						b2Vec2 start = b2Mul(body_transform, edge->m_vertex1);
						b2Vec2 end = b2Mul(body_transform, edge->m_vertex2);

						Vertex line[] =
						{
							Vertex(box2d_position_to_sfml_position(start, window_height), Color::Green),
							Vertex(box2d_position_to_sfml_position(end, window_height), Color::Green),
						};

						window.draw(line, 2, Lines);
					}
					else
						if (shape_type == b2Shape::e_polygon)
						{
							// Se toma la forma poligonal de Box2D (siempre es convexa) y se crea a partir de sus vértices un
							// ConvexShape de SFML. Cada vértice de Box2D hay que transformarlo usando el transform del body.

							b2PolygonShape * box2d_polygon = dynamic_cast< b2PolygonShape * >(fixture->GetShape());
							ConvexShape       sfml_polygon;

							int number_of_vertices = box2d_polygon->GetVertexCount();

							sfml_polygon.setPointCount(number_of_vertices);
							sfml_polygon.setFillColor(Color::Yellow);

							for (int index = 0; index < number_of_vertices; index++)
							{
								sfml_polygon.setPoint
								(
									index,
									box2d_position_to_sfml_position(b2Mul(body_transform, box2d_polygon->GetVertex(index)), window_height)
								);
							}

							window.draw(sfml_polygon);
						}
			}
		}
	}
	*/
	shared_ptr< b2World > create_physics_world(float world_width, float world_height)
	{
		// Se crea el mundo físico:

		shared_ptr< b2World > physics_world(new b2World(b2Vec2(0, -100.f)));

		// CÍRCULO
		{
			// Se crea el body a partir de una definición de sus características:

			b2BodyDef body_definition;

			body_definition.type = b2_dynamicBody;
			body_definition.position.Set(world_width / 2.f, world_height / 2.f);           // Posición inicial absoluta

			b2Body * body = physics_world->CreateBody(&body_definition);

			// Se añande una fixture al body:

			b2CircleShape body_shape;

			body_shape.m_radius = 25.f;

			b2FixtureDef body_fixture;

			body_fixture.shape = &body_shape;
			body_fixture.density = 1.00f;
			body_fixture.restitution = 0.75f;
			body_fixture.friction = 0.50f;

			body->CreateFixture(&body_fixture);
		}

		// CUADRADO
		{
			// Se crea el body a partir de una definición de sus características:

			b2BodyDef body_definition;

			body_definition.type = b2_dynamicBody;
			body_definition.position.Set(world_width / 2.f, world_height / 2.f + 200.f);   // Posición inicial absoluta
			body_definition.angle = 0.4f;

			b2Body * body = physics_world->CreateBody(&body_definition);

			// Se añande una fixture al body:

			b2PolygonShape body_shape;

			body_shape.SetAsBox(25.f, 25.f);

			b2FixtureDef body_fixture;

			body_fixture.shape = &body_shape;
			body_fixture.density = 1.00f;
			body_fixture.restitution = 0.50f;
			body_fixture.friction = 0.50f;

			body->CreateFixture(&body_fixture);
		}

		// SUELO
		{
			// Se crea el body a partir de una definición de sus características:

			b2BodyDef body_definition;

			body_definition.type = b2_staticBody;
			body_definition.position.Set(0.f, 50.f);                                       // Posición inicial absoluta
			body_definition.angle = 0.f;

			b2Body * body = physics_world->CreateBody(&body_definition);

			// Se añande una fixture al body:

			b2EdgeShape body_shape;

			body_shape.Set(b2Vec2(0.f, 0.f), b2Vec2(world_width, 0.f));                    // Coordenadas locales respecto al centro del body

			b2FixtureDef body_fixture;

			body_fixture.shape = &body_shape;

			body->CreateFixture(&body_fixture);
		}

		return physics_world;
	}

}

int main() {
	physics2D::Window window(800, 600, "Box2D Demo");

	shared_ptr< b2World > physics_world = create_physics_world(800, 600);

	physics2D::Renderer renderer(physics_world, & window);

	bool running = true;

	Clock timer;
	float delta_time = 0.017f;          // ~60 fps

	do
	{
		timer.restart();

		// Process window events:

		Event event;

		while (window.window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				running = false;
			}
		}

		// Update:

		physics_world->Step(delta_time, 8, 4);

		// Render:

		window.window->clear();

		renderer.render();

		window.window->display();

		delta_time = (delta_time + timer.getElapsedTime().asSeconds()) * 0.5f;
	} while (running);

	return EXIT_SUCCESS;
}

//Old main
/*
int main2()
{
	RenderWindow window(VideoMode(800, 600), "Animation Examples: Box2D Rigid Bodies", Style::Titlebar | Style::Close, ContextSettings(32));

	window.setVerticalSyncEnabled(true);

	shared_ptr< b2World > physics_world = create_physics_world(800, 600);

	bool running = true;

	Clock timer;
	float delta_time = 0.017f;          // ~60 fps

	do
	{
		timer.restart();

		// Process window events:

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				running = false;
			}
		}

		// Update:

		physics_world->Step(delta_time, 8, 4);

		// Render:

		window.clear();

		render(*physics_world, window);

		window.display();

		delta_time = (delta_time + timer.getElapsedTime().asSeconds()) * 0.5f;
	} while (running);

	return EXIT_SUCCESS;
}
*/
