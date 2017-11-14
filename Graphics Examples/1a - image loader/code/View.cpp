
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "View.hpp"

extern "C"
{
    #include <targa.h>
}

namespace example
{

    View::View(size_t width, size_t height, const char * image_path)
    :
        width       (width ),
        height      (height),
        pixel_buffer(width, height),
        rasterizer  (pixel_buffer )
    {
        if (image_path != 0)
        {
            load_image (image_path);
        }
    }

    bool View::load_image (const char * image_path)
    {
        tga_image loaded_image;

        if (tga_read (&loaded_image, image_path) == TGA_NOERR)
        {
            image.reset (new Pixel_Buffer(loaded_image.width, loaded_image.height));

            tga_flip_vert     (&loaded_image);
            tga_convert_depth (&loaded_image, (uint8_t)image->bits_per_pixel ());
            tga_swap_red_blue (&loaded_image);

            Pixel_Buffer::Pixel * loaded_image_pixels     = reinterpret_cast< Pixel_Buffer::Pixel * >(loaded_image.image_data);
            Pixel_Buffer::Pixel * loaded_image_pixels_end = loaded_image_pixels + loaded_image.width * loaded_image.height;
            Pixel_Buffer::Pixel * image_buffer_pixels     = image->pixels ();

            while (loaded_image_pixels <  loaded_image_pixels_end)
            {
                *image_buffer_pixels++ = *loaded_image_pixels++;
            }

            rasterizer.clear (255, 255, 255);

            tga_free_buffers (&loaded_image);

            return (true);
        }
        else
        {
            rasterizer.clear (255, 0, 0);

            return (false);
        }
    }

    void View::paint ()
    {
        if (image.get ())
        {
            rasterizer.draw_image (512, 10, *image);
        }

        pixel_buffer.blit_to_window ();
    }

}
