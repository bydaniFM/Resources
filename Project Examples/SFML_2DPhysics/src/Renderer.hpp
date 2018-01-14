
#pragma once

#include <memory>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Window.hpp"

using namespace std;

namespace physics2D
{

	class Renderer
	{
	private:
		
		shared_ptr< b2World > physics_world;
		RenderWindow * window;

	public:

		Renderer(shared_ptr< b2World > physics_world, Window * window)
		{
			this->physics_world = physics_world;
			this->window = window->window;
		}

		void render();

		Vector2f box2d_position_to_sfml_position(const b2Vec2 & box2d_position, float window_height)
		{
			return Vector2f(box2d_position.x, window_height - box2d_position.y);
		}
	};
}