
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
        // Draws a yellow diagonal line:

        pixel_buffer.set_color (255, 255, 0);

        for (int i = 0, max = width < height ? width : height; i < max; i++)
        {
            pixel_buffer.set_pixel (i, i);
        }

        // Draws a magenta diagonal line:

        pixel_buffer.set_color (255, 0, 255);

        for (int i = 0, max = width < height ? width : height; i < max; i++)
        {
            pixel_buffer.set_pixel (width - i, i);
        }

        // Moves the pixel buffer into the window:

        pixel_buffer.blit_to_window ();
    }

}
