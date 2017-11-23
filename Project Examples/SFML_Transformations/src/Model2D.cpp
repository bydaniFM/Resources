
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
#include "Scaling.hpp"
#include "Rotation.hpp"
#include "Translation.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace toolkit;

namespace example
{

	void Model2D::render(sf::RenderWindow & renderer)
	{
		Scaling2f        scale(scale);
		Rotation2f       rotation(angle);
		Translation2f    translation(position);
		Transformation2f transform(translation * rotation * scale);

		int number_of_vertices = local_vertices.size();

		for (size_t i = 0; i < number_of_vertices; ++i)
		{
			transformed_vertices[i] = Matrix33f(transform) * Matrix31f(local_vertices[i]);
		}

		ConvexShape sfml_polygon;

		sfml_polygon.setPointCount(number_of_vertices);
		sfml_polygon.setFillColor(Color::Yellow);

		for (int i = 0; i < number_of_vertices; i++)
		{
			sfml_polygon.setPoint
			(
				i,
				sf::Vector2f
				(
					transformed_vertices[i][0],
					transformed_vertices[i][1]
				)
			);
		}

		renderer.draw(sfml_polygon);
	}


	//void render(sf::RenderWindow & renderer, const Transformation & parent_transform)
	//{
	//	Scale scale(...);
	//	Rotation rotation(...);
	//	Traslation traslation(...)

	//		Transformation  node_transform = traslation * rotation * scale;
	//	Transformation final_transform = parent_transform * node_transform;

	//	// Transformar los vértices con final_transform
	//	// Dibujar los vértices

	//	for (auto & child : children)
	//	{
	//		child->render(renderer, final_transform);
	//	}
	//}


}
