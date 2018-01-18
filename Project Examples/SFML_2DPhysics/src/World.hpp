
#pragma once

#include <memory>
#include <vector>
#include <Box2D/Box2D.h>

using namespace std;

namespace physics2D
{
	class World
	{
	private:

		//List<Model>;

	public:

		shared_ptr< b2World > physics_world;

		World(){}
		World(float gravity) {
			physics_world = shared_ptr<b2World>(new b2World(b2Vec2(0, gravity)));
		}

		void Update(float delta_time)	//b2world->Step();
		{
			physics_world->Step(delta_time, 8, 4);
		}
		void render(World & world);

	};

}