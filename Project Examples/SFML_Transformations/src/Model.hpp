
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Started by �ngel on november of 2015                                       *
*                                                                             *
*  This is free software released into the public domain.                     *
*                                                                             *
*  angel.rodriguez@esne.edu                                                   *
*                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SAMPLE_MODEL_HEADER
#define SAMPLE_MODEL_HEADER

#include <vector>
#include "Point.hpp"

namespace transformations
{

	class Model
	{

		std::vector< Point2f > local_vertices;

		// ATRIBUTOS DE TRANSFORMACI�N:
		// traslaci�n (x, y)
		// rotaci�n (�ngulo)
		// escala (sx, sy)

		// ATRIBUTOS DE ANIMACI�N:
		// velocidad, aceleraci�n, etc. del desplazamiento
		// velocidad angular de rotaci�n
		// variaci�n de la escala (normalmente cero)

	public:

		Model()
		{
		}

		Model(const std::initializer_list< Point2f > & points)
			:
			local_vertices(points)
		{
		}

		void update(float delta);
		void render();

	};

}

#endif
