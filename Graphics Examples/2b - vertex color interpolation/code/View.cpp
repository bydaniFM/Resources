
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on october of 2013                                        *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "View.hpp"

namespace example
{

    void View::paint ()
    {
        rasterizer.clear (0, 0, 0);

        rasterizer.fill_triangle (350, 50, 90, 400, 700, 550, Color(255, 0, 0), Color(0, 255, 0), Color(0, 0, 255));

        rasterizer.get_color_buffer ().gl_draw_pixels (0, 0);
    }

}
