
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Started by Ángel on november of 2017                                       *
*                                                                             *
*  This is free software released into the public domain.                     *
*                                                                             *
*  angel.rodriguez@esne.edu                                                   *
*                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef MODEL2D_HEADER
#define MODEL2D_HEADER

#include <vector>
#include "Point.hpp"
#include "Vector.hpp"

namespace sf { class RenderWindow; }

namespace example
{

	using toolkit::Point3f;
	using toolkit::Vector2f;

	class Model2D
	{
		typedef std::vector< Point3f > Vertex_Buffer;

		// Buffers de vértices:

		Vertex_Buffer local_vertices;
		Vertex_Buffer transformed_vertices;

		// Atributos de transformación:

		Vector2f	  position;
		float		  angle;
		float		  scale;

		// Atributos de animación:

		Vector2f	  linear_speed;
		float        angular_speed;

	public:

		Model2D(const std::initializer_list< Point3f > & points)
		{
			local_vertices.reserve(points.size());

			for (auto & point : points)
			{
				local_vertices.push_back(point);
			}

			transformed_vertices.resize(local_vertices.size());

			set_position(0, 0);
			set_angle(0);
			set_scale(1);

			set_linear_speed(0, 0);
			set_angular_speed(0);
		}

		void set_position(float x, float y)
		{
			position = Vector2f({ x, y });
		}

		void set_angle(float new_angle)
		{
			angle = new_angle;
		}

		void set_scale(float new_scale)
		{
			scale = new_scale;
		}

		void set_linear_speed(float speed_x, float speed_y)
		{
			linear_speed = Vector2f({ speed_x, speed_y });
		}

		void set_angular_speed(float speed)
		{
			angular_speed = speed;
		}

		void update(float delta)
		{
			position += linear_speed;
			angle += angular_speed;
		}

		void render(sf::RenderWindow & renderer);

	};

}

#endif
