
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
		
		size_t number_of_vertices = local_vertices.size();

		for (size_t i = 0; i < number_of_vertices; ++i)
		{
			transformed_vertices[i] = Matrix33f(final_transform) * Matrix31f(local_vertices[i]);
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

		if(child.get()){
			child->render(renderer);
		}
	}



	void Model2D::transform(const Transformation2f & parent_transform) {
		Scaling2f        scale(scale);
		Rotation2f       rotation(angle);
		Translation2f    translation(position);
		final_transform = parent_transform * translation * rotation * scale;

		if (child.get()){
			child->transform(final_transform);
		}

	}

	bool Model2D::solveInverse(const Point2f & target, float epsilon) {

		Model2D * last_node = find_last_node();

		// REPETIR HASTA ENCONTRAR SOLUCIÓN:
		// DETERMINAR LOS ÁNGULOS DE CADA NODO HIJO
		// CALCULAR LA POSICIÓN DEL PUNTO DE REFERENCIA DE LAST_NODE
		// CALCULAR DISTANCIA DEL PUNTO DE REFERENCIA A TARGET
		//      SI LA DISTANCIA ES MENOR QUE EPSILON SE DA POR BUENA

		std::list<float> angles;
		float distance;

		set_reference(last_node->position);

		while (child.get()) {
			
		}


		if (distance > epsilon) {
			return true;
		}





		return false;

	}


}