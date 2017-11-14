
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2016                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctime>
#include <cstdlib>
#include "View.hpp"

namespace example
{

    View::View(size_t width, size_t height)
    :
        width       (width ),
        height      (height),
        pixel_buffer(width, height)
    {
        // Se inicializa el generador de números aleatorios:

        srand (unsigned(time (nullptr)));

        // Se generan los campos escalares con posiciones aleatorias:

        fields.resize (number_of_fields);

        for (auto & field : fields)
        {
            field.energy   = float(rand () % 500 + 500);
            field.center_x = float(rand () % width    );
            field.center_y = float(rand () % height   );
            field.speed_x  = float(rand () % 5 + 5    );
            field.speed_y  = float(rand () % 5 + 5    );
        }
    }

    void View::update ()
    {
        for (auto & field : fields)
        {
            field.center_x += field.speed_x;
            field.center_y += field.speed_y;

            if (field.center_x < 0 || field.center_x > width)
            {
                field.speed_x = -field.speed_x;
            }

            if (field.center_y < 0 || field.center_y > height)
            {
                field.speed_y = -field.speed_y;
            }
        }
    }

    void View::render ()
    {
		const float threshold = 0.2f;
        const float width     = float(this->width );
        const float height    = float(this->height);
		unsigned    offset    = 0;

        // Se borra el buffer con color negro y se establece el color de relleno:

        pixel_buffer.set_color (0, 0, 0);
        pixel_buffer.clear ();
		pixel_buffer.set_color (255, 255, 0);

        // Se calcula el potencial en cada píxel y se establece su color según esté por
        // encima o por debajo del umbral:

		for (float y = 0.f; y < height; y += 1.f)
		{
			for (float x = 0.f; x < width; x += 1.f, offset++)
			{
                // Se calcula el potencial en el píxel actual:

				float potential = 0.f;

				for (auto & field : fields)
				{
					potential += field.potential_at (x, y);
				}

                // Se cambia el color del píxel si su potencial está por encima del umbral:

                if (potential > threshold)
                {
				    pixel_buffer.set_pixel (offset);
                }
			}
		}

        // Se mueve el buffer de pixels a la ventana:

        pixel_buffer.blit_to_window ();
    }

}
