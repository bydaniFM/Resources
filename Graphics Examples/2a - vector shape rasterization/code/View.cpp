
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
        rasterizer.set_color      (0, 0, 255);
        rasterizer.fill_triangle  (400, 0, 0, 300, 800, 600);
        rasterizer.set_color      (255, 255, 0);
        rasterizer.fill_triangle  (600, 500, 400, 400, 700, 300);
        rasterizer.set_color      (255, 255, 255);
        rasterizer.fill_rectangle (100, 100, 200, 200);

        rasterizer.set_color      (100, 100, 255);
        rasterizer.draw_rectangle (100, 100, 200, 200);
        rasterizer.draw_triangle  (200, 100, 300, 200, 100, 300);
        rasterizer.draw_circle    (200, 200, 100);
        rasterizer.draw_ellipse   (100, 150, 200, 100);

        pixel_buffer.blit_to_window ();
    }

}
