
#include "Rasterizer.hpp"

namespace example
{

	template< class  PIXEL_BUFFER_TYPE >
	size_t Rasterizer< PIXEL_BUFFER_TYPE >::clip_polygon
	(
		const Point2D * vertices,
		size_t    vertex_count,
		Point2D * clip_result,
		const float     width,
		const float     height
	)

	{
		Point2D clip_aux_a[20];
		Point2D clip_aux_b[20];

		vertex_count = clip_polygon_with_line
		(
			vertices,
			vertex_count,
			clip_aux_a,
			Point2D{ 0.f, 0.f },
			Vector2D{ 0.f, 1.f }
		);

		vertex_count = clip_polygon_with_line
		(
			clip_aux_a,
			vertex_count,
			clip_aux_b,
			Point2D{ 0.f, height },
			Vector2D{ 1.f, 0.f }
		);

		vertex_count = clip_polygon_with_line
		(
			clip_aux_b,
			vertex_count,
			clip_aux_a,
			Point2D{ width,  0.f },
			Vector2D{ 0.f, -1.f }
		);


		return clip_polygon_with_line
		(
			clip_aux_a,
			vertex_count,
			clip_result,
			Point2D{ 0.f, 0.f },
			Vector2D{ -1.f, 0.f }
		);
	}


	template< class  PIXEL_BUFFER_TYPE >
	size_t Rasterizer< PIXEL_BUFFER_TYPE >::clip_polygon_with_line
	(
		const Point2D  * vertices,
		size_t     vertex_count,
		Point2D  * clip_result,
		const Point2D  & line_point,
		const Vector2D & line_vector
	)
	{

		// CALCULAR LOS COEFICIENTES DE LA ECUACIÓN GENERAL (Ax+By+C=0)
		// DE LA LÍNEA DE RECORTE:

		float a = ...;
		float b = ...;
		float c = ...;

		// PARA CADA PAR DE PUNTOS DEL POLÍGONO:
		{
			float s0 = a * px0 + b * py0 + c;
			float s1 = a * px1 + b * py1 + c;

			if (s0 < 0.f && s1 < 0.f)
			{
				// ...
			}
			else
				if (s0 < 0.f && s1 > 0.f)
				{
				}
				else
					if (s0 > 0.f && s1 < 0.f)
					{
					}
					else
					{
					}
		}

	}

}