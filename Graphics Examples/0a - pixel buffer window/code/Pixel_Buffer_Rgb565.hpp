
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PIXEL_BUFFER_RGB565_HEADER
#define PIXEL_BUFFER_RGB565_HEADER

    #include "Pixel_Buffer.hpp"
    #include <SFML/OpenGL.hpp>
    #include <GL/glext.h>
    #include <stdint.h>             // This header is <csdint> on C++11...
    #include <vector>

    namespace example
    {

        class Pixel_Buffer_Rgb565 : public Pixel_Buffer
        {
        public:

            typedef uint16_t             Pixel;
            typedef std::vector< Pixel > Buffer;

        private:

            Buffer buffer;
            Pixel  color;

        public:

            Pixel_Buffer_Rgb565(size_t width, size_t height)
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

            size_t bits_per_pixel () const
            {
                return (sizeof(Pixel) * 8);
            }

        public:

            void set_color (int r, int g, int b)
            {
                color = Pixel( (r >> 3 << 11) | (g >> 2 << 5) | (b >> 3) );
            }

            void set_pixel (int x, int y)
            {
                buffer[y * width + x] = color;
            }

            void set_pixel (size_t offset)
            {
                buffer[offset] = color;
            }

            void blit_to_window () const
            {
                // glDrawPixels() is efficient when the driver has proper support. Otherwise it will be slow.
                // Pixel buffer objects could be more appropriate, but glDrawPixels() is more simple and compatible
                // within the context of this example.

                glRasterPos2f (-1.f, +1.f);
                glPixelZoom   (+1.f, -1.f);
                glDrawPixels  (width, height, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, pixels ());
            }

        };

    }

#endif
