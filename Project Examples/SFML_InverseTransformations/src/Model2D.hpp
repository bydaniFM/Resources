
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
#include <list>
#include <memory>
#include "Point.hpp"
#include "Vector.hpp"
#include "Transformation.hpp"

namespace sf { class RenderWindow; }

namespace example
{

	using toolkit::Point2f;
	using toolkit::Point3f;
	using toolkit::Vector2f;
	using toolkit::Transformation2f;

	class Model2D
	{
		typedef std::vector< Point3f > Vertex_Buffer;
		typedef std::shared_ptr< Model2D > Child;

		// Buffers de vértices:

		Vertex_Buffer local_vertices;
		Vertex_Buffer transformed_vertices;

		// Atributos de transformación:

		Vector2f	  position;
		float		  angle;
		float		  scale;

		//Atributos de restriccion

		float min_angle;
		float max_angle;

		// Atributos de animación:

		float original_angle;
		float target_angle;
		float angle_delta;

		Point2f reference_point;

		//Child nodes

		Child child;

		//Own transformation plus parent transformations
		Transformation2f final_transform;

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

		}

		void set_child(std::shared_ptr<Model2D> new_child) { child = new_child; }

		void set_position		(float x, float y) { position = Vector2f({ x, y }); }
		void set_angle			(float new_angle) { 	angle = new_angle; }
		void set_min_angle		(float new_angle) { min_angle = new_angle; }
		void set_max_angle		(float new_angle) { max_angle = new_angle; }
		void set_scale			(float new_scale) { scale = new_scale; }


		void set_reference(const Point2f & point) { reference_point = point; }

		void update(float delta)
		{
			//Forward kinematics
			/*position += linear_speed;
			angle += angular_speed;*/
		}

		void render(sf::RenderWindow & renderer);

		void transform(const Transformation2f & parent_transform);

		bool solveInverse(const Point2f & target, float epsilon);

	private:
		
		Model2D * find_last_node() {
			if (child.get())
				return child->find_last_node();
			else
				return this;
		}

	};

}

#endif
