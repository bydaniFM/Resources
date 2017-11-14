
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
#include "Kernel.hpp"

#include <iostream>
#include <SFML/System.hpp>

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

            // Si la imagen se ha podido cargar con éxito, se le aplica un filtro y se guarda el resultado en filtered_image:

            if (image.get ())
            {
                filtered_image.reset (new Pixel_Buffer(image->get_width (), image->get_height ()));

                kernel.set (0, 0, 1); kernel.set (0, 1, 1); kernel.set (0, 2, 1);
                kernel.set (1, 0, 1); kernel.set (1, 1, 1); kernel.set (1, 2, 1);
                kernel.set (2, 0, 1); kernel.set (2, 1, 1); kernel.set (2, 2, 1);

                kernel.set_divisor (9);

                optimized_kernel.set (0, 0, 1); optimized_kernel.set (0, 1, 1); optimized_kernel.set (0, 2, 1);
                optimized_kernel.set (1, 0, 1); optimized_kernel.set (1, 1, 1); optimized_kernel.set (1, 2, 1);
                optimized_kernel.set (2, 0, 1); optimized_kernel.set (2, 1, 1); optimized_kernel.set (2, 2, 1);

                optimized_kernel.set_divisor (9);

                sf::Clock chrono;

                for (int repeat = 100; repeat--; )
                {
                    apply_optimized_filter ();
                }

                int elapsed_time = chrono.getElapsedTime ().asMilliseconds ();

                std::cout << chrono.getElapsedTime ().asMilliseconds () << std::endl;
            }
        }
    }

    bool View::load_image (const char * image_path)
    {
        tga_image loaded_image;

        if (tga_read (&loaded_image, image_path) == TGA_NOERR)
        {
            image.reset (new Pixel_Buffer(loaded_image.width, loaded_image.height));

            tga_flip_vert     (&loaded_image);
            tga_convert_depth (&loaded_image, image->bits_per_pixel ());
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

    void View::apply_filter ()
    {
        if (image.get ())
        {
            for (int y = 0, height = image->get_height (); y < height; y++)
            {
                for (int x = 0, width = image->get_width (); x < width; x++)
                {
                    kernel.apply (*image, *filtered_image, x, y);
                }
            }
        }
    }

    void View::apply_optimized_filter ()
    {
        if (image.get ())
        {
            optimized_kernel.apply (*image, *filtered_image);
        }
    }

    void View::paint ()
    {
        if (image.get ())
        {
            rasterizer.draw_image (140, 100, *filtered_image);
        }

        pixel_buffer.blit_to_window ();
    }

}
