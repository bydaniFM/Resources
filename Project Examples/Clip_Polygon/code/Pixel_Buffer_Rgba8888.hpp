
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PIXEL_BUFFER_RGBA8888_HEADER
#define PIXEL_BUFFER_RGBA8888_HEADER

    #include "Pixel_Buffer.hpp"
    #include <SFML/OpenGL.hpp>
    #include <stdint.h>             // This header is <csdint> on C++11...
    #include <vector>

    namespace example
    {

        class Pixel_Buffer_Rgba8888 : public Pixel_Buffer
        {
        public:

            struct Pixel
            {
                union
                {
                    struct
                    {
                        uint8_t r;
                        uint8_t g;
                        uint8_t b;
                        uint8_t a;
                    }
                    component;

                    uint32_t value;             // Beware of big/little endianness
                }
                data;
            };

            typedef std::vector< Pixel > Buffer;

        private:

            Buffer buffer;
            Pixel  color;

        public:

            Pixel_Buffer_Rgba8888(size_t width, size_t height)
            :
                Pixel_Buffer(width,  height),
                buffer      (width * height)
            {
            }

        public:

            Pixel * pixels ()
            {
                return (&buffer.front ());
            }

            const Pixel * pixels () const
            {
                return (&buffer.front ());
            }

            int bits_per_pixel () const
            {
                return (sizeof(Pixel) * 8);
            }

        public:

            void set_color (int r, int g, int b)
            {
                color.data.component.r = uint8_t(r < 0 ? 0 : r > 255 ? 255 : r);
                color.data.component.g = uint8_t(g < 0 ? 0 : g > 255 ? 255 : g);
                color.data.component.b = uint8_t(b < 0 ? 0 : b > 255 ? 255 : b);
                color.data.component.a = 0xFF;                                      // Set opaque alpha
            }

            void set_pixel (int x, int y)
            {
                buffer[y * width + x] = color;
            }

            void set_pixel (size_t offset)
            {
                buffer[offset] = color;
            }

            void gl_draw_pixels (int raster_x, int raster_y) const
            {
                // glDrawPixels() is efficient when the driver has proper support. Otherwise it will be slow.
                // Pixel buffer objects could be more appropriate, but glDrawPixels() is more simple and compatible
                // within the context of this example.

                glRasterPos2i (raster_x, raster_y);
                glDrawPixels  (width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels ());
            }

        };

    }

#endif
