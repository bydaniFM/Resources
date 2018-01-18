
#pragma once

#include <list>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "World.hpp"

using namespace std;
using namespace sf;

namespace physics2D
{
	class Body
	{
	private:

		Model * model;
		b2Body * body;
		list< b2Fixture * > fixtures;
		list< shared_ptr< Shape > > shapes;

	public:

		Body(Model * model, float pos_x, float pos_y)	//Un constructor para cada tipo de shape?
		{
			this->model = model;

			//añadir fixture

			b2BodyDef body_definition;

			body_definition.type = b2_dynamicBody;
			body_definition.position.Set(pos_x, pos_y);           // Posición inicial absoluta

			body = model->world->physics_world->CreateBody(&body_definition);
		}

		void add_circle (...)
		{
			//añade una fixture y un shape
		}

		void render(World & world);
	};
}
