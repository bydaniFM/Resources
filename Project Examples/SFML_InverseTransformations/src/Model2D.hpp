
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Started by �ngel on november of 2017                                       *
*                                                                             *
*  This is free software released into the public domain.                     *
*                                                                             *
*  angel.rodriguez@esne.edu                                                   *
*                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef MODEL2D_HEADER
#define MODEL2D_HEADER

#include <vector>
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

		/// Esta estructura guarda la informaci�n de control de movimiento (angular) de un nodo que
		/// forma parte del Model2D mientras se est� buscando una soluci�n de cinem�tica inversa.

		struct Control
		{
			Model2D * node;             ///< Nodo que se controla con la informaci�n de la estructura
			float     before;           ///< �ngulo antes de comenzar la b�squeda
			float     start;            ///< �ngulo con el que se empieza a aproximar
			float     limit;            ///< �ngulo con el que termina la aproximaci�n
			float     angle;            ///< �ngulo en un momento dado
			float     step;             ///< Paso con el que se incrementa el �ngulo desde start hasta limit
			float     best;             ///< �ngulo de la mejor soluci�n hasta la �ltima iteraci�n
		};

		typedef std::vector< Point3f > Vertex_Buffer;       ///< Tipo de la  lista de v�rtices del modelo
		typedef std::vector< Control > Control_List;        ///< Tipo de una lista de controles de movimiento

	private:

		// Buffers de v�rtices:

		Vertex_Buffer local_vertices;                       ///< Coordenadas locales de los v�rtices del modelo
		Vertex_Buffer transformed_vertices;                 ///< Buffer prealojado para guardar las coordenadas transformadas cada fotograma

															// Atributos de transformaci�n:

		Vector2f      position;                             ///< Posici�n del origen de coordenadas locales del modelo
		float         angle;                                ///< �ngulo del modelo alrededor de su origen de coordenadas
		float         scale;                                ///< Escala del modelo

															// Atributos de restricci�n:

		float         min_angle;                            ///< �ngulo m�nimo en el que puede orientarse el modelo
		float         max_angle;                            ///< �ngulo m�ximo en el que puede orientarse el modelo
		Point3f       reference_point;                      ///< Coordenadas locales del punto que debe coincidir con
															///< el target al buscar la soluci�n de cinem�tica inversa
															// Atributos de animaci�n:

		float         target_angle;                         ///< �ngulo hacia el que debe rotar el modelo (lo establece solve_inverse_kinematics)

															// Atributos de grafo:

		std::shared_ptr< Model2D > child;                   ///< Primero de los nodos hijos que puede tener el modelo
		Transformation2f final_transform;                   ///< Cach� prealojado donde se guarda la transformaci�n final del modelo,
															///< que es la transformaci�n propia combinada con la de los nodos padre
	public:

		Model2D(const std::initializer_list< Point3f > & points);

		void set_child(std::shared_ptr< Model2D > & given_child)
		{
			child = given_child;
		}

		void set_position(float x, float y) { position = Vector2f({ x, y }); }
		void set_angle(float new_angle) { target_angle = angle = new_angle; }
		void set_scale(float new_scale) { scale = new_scale; }
		void set_min_angle(float new_angle) { min_angle = new_angle; }
		void set_max_angle(float new_angle) { max_angle = new_angle; }
		void set_target_angle(float new_angle) { target_angle = new_angle; }
		void set_reference(const Point2f & point) { reference_point = Point3f({ point[0], point[1], 1.f }); }

	public:

		/// Actualiza la animaci�n del modelo y sus nodos hijos.

		void update();

		/// Calcula la matriz de transformaci�n final del nodo y las de sus hijos recursivamente.

		void transform(const Transformation2f & parent_transform = Transformation2f());

		/// Dibuja el nodo y sus hijos recursivamente.

		void render(sf::RenderWindow & renderer);

		/// Determina la posici�n (angular) hacia la que debe moverse el modelo y sus hijos
		/// para que el punto de referencia del �ltimo nodo del grafo coincida con el punto
		/// target indicado dentro de cierta tolerancia definica con steps y epsilon.

		void solve_inverse_kinematics(const Point2f & target, int steps, float epsilon);

	private:

		/// Devuelve el n�mero de nodos hijos que tiene el modelo.

		size_t count_children() const;

		/// Devuelve un puntero al �ltimo nodo del grafo.

		Model2D * find_last_node();

		/// Enlaza cada nodo del grafo con la estructura de control que le corresponde seg�n
		/// su profundidad (de recursi�n).

		void link_node_controls(Control_List & controls, size_t depth);

	};

}

#endif
