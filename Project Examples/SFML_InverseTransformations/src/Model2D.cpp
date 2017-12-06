
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

	Model2D::Model2D(const std::initializer_list< Point3f > & points)
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

	void Model2D::update()
	{
		angle = (angle + target_angle) *.5f;

		if (child.get())
		{
			child->update();
		}
	}

	void Model2D::transform(const Transformation2f & parent_transform)
	{
		Scaling2f     scale(scale);
		Rotation2f    rotation(angle);
		Translation2f translation(position);

		final_transform = parent_transform * translation * rotation * scale;

		if (child.get())
		{
			child->transform(final_transform);
		}
	}

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

		for (size_t i = 0; i < number_of_vertices; i++)
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

		if (child.get())
		{
			child->render(renderer);
		}
	}

	void Model2D::solve_inverse_kinematics(const Point2f & target, int steps, float epsilon)
	{
		// Se cuenta el número de nodos total y se busca un puntero al último nodo:

		size_t    node_count = count_children() + 1;
		Model2D * last_node = find_last_node();

		// Se crea una estructura de control para nodo y se enlazan con los nodos correspondientes:

		Control_List controls(node_count);

		link_node_controls(controls, 0);

		// Se inicializan todos los controles de nodos y se guardan punteros al primero y al último:

		for (auto & control : controls)
		{
			Model2D & node = *control.node;

			control.before = node.angle;
			control.start = node.min_angle;
			control.limit = node.max_angle + 0.01f;
			control.angle = node.min_angle;
			control.step = (node.max_angle - node.min_angle) / float(steps);
			control.best = (node.max_angle + node.min_angle) * 0.5f;
		}

		Control * first = &controls.front();
		Control * last = &controls.back();

		// Se comienza el bucle dentro del cual se buscará la posición del grafo tal que el punto
		// de referencia del último nodo coincida con el punto (target) que se ha recibido:

		bool  solution_found = false;
		float best_distance = 1000000.f;

		while (!solution_found)
		{
			// Se ajusta el ángulo de todos los nodos del grafo según lo que indiquen los controles
			// en la iteración actual y se actualiza la matriz de transformación de los nodos:

			for (auto & control : controls)
			{
				control.node->set_angle(control.angle);
			}

			transform();

			// Se determina la posición del punto de referencia del último nodo del grafo en la
			// iteración actual y se calcula su distancia al punto target:

			Point3f transformed_reference = Matrix33f(last_node->final_transform) * Matrix31f(last_node->reference_point);
			float   reference_delta_x = target[0] - transformed_reference[0];
			float   reference_delta_y = target[1] - transformed_reference[1];
			float   reference_distance = reference_delta_x * reference_delta_x + reference_delta_y * reference_delta_y;

			// Si la distancia es la menor encontrada hasta ahora, se guarda la posición del grafo
			// como posible resultado:

			if (reference_distance < best_distance)
			{
				best_distance = reference_distance;

				for (auto & control : controls)
				{
					control.best = control.angle;
				}

				// Si la distancia está dentro del rango de precisión indicado por epsilon, se toma
				// la posición actual del grafo como resultado y se termina:

				if (best_distance < epsilon)
				{
					solution_found = true;
					break;
				}
			}

			// Se ajusta la posición (angular) del grafo: se empieza incrementando el ángulo del nodo
			// raíz y, solo si alguno de los nodos llega a su extremo, se incrementa el ángulo de los
			// siguientes nodos:

			first->angle += first->step;

			for (auto & control : controls)
			{
				Control * current = &control;

				if (current->angle > current->limit)
				{
					if (current == last)                    // Si el último nodo ha alcanzado su ángulo
					{                                       // límite, se han terminado de comprobar todas
						solution_found = true;              // las posibilidades y se termina dando por buena
						break;                              // la mejor solución guardada hasta el momento
					} else                                    // Si hay un siguiente nodo, se incrementa su
					{                                       // ángulo y se restablece el del nodo actual
						Control * next = current + 1;
						current->angle = current->start;
						next->angle += next->step;
					}
				} else
					break;                                  // Si no hay overflow del ángulo se sale de este bucle
			}
		}

		// Al terminar se establece como target de movimiento del grafo la mejor posición encontrada y
		// se restablece la posición del grafo a la que tenía antes de empezar la búsqueda:

		for (auto & control : controls)
		{
			control.node->set_angle(control.before);
			control.node->set_target_angle(control.best);
		}
	}

	size_t Model2D::count_children() const
	{
		return child.get() ? child->count_children() + 1 : 0;
	}

	Model2D * Model2D::find_last_node()
	{
		return child.get() ? child->find_last_node() : this;
	}

	void Model2D::link_node_controls(Control_List & controls, size_t depth)
	{
		controls[depth].node = this;

		if (child.get())
		{
			child->link_node_controls(controls, depth + 1);
		}
	}

}
