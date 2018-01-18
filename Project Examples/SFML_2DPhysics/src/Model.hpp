
#pragma once

//#include <list>
#include "World.hpp"
#include "Body.hpp"

using namespace std;

namespace physics2D
{
	class Model
	{
	public:

		World * world;

	private:

		list<Body> bodys;
		//list<Joint> joints;
		
	public:

		Model(){}
		Model(World * world){
			this->world = world;
		}

		render(World & world);


	};
}