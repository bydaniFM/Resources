
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef COLOR_BUFFER_RGB565_HEADER
#define COLOR_BUFFER_RGB565_HEADER

    #include "Color_Buffer.hpp"
    #include <SFML/OpenGL.hpp>
    #include <GL/glext.h>
    #include <stdint.h>             // This header is <csdint> on C++11...
    #include <vector>

    namespace example
    {

        class Color_Buffer_Rgb565 : public Color_Buffer
        {
        public:

            typedef uint16_t             Color;
            typedef std::vector< Color > Buffer;

        private:

            Buffer buffer;
            Color  color;

        public:

            Color_Buffer_Rgb565(size_t width, size_t height)
            :
                Color_Buffer(width,  height),
                buffer      (width * height)
            {
            }

        public:

            Color * colors ()
            {
                return (&buffer.front ());
            }

            const Color * colors () const
            {
                return (&buffer.front ());
            }

            int bits_per_color () const
            {
                return (sizeof(Color) * 8);
            }

        public:

            void set_color (int r, int g, int b)
            {
                color = Color( (r >> 3 << 11) | (g >> 2 << 5) | (b >> 3) );
            }

            void set (int x, int y)
            {
                buffer[y * width + x] = color;
            }

            void set (size_t offset)
            {
                buffer[offset] = color;
            }

            void gl_draw_pixels (int raster_x, int raster_y) const
            {
                // glDrawPixels() is efficient when the driver has proper support. Otherwise it will be slow.
                // Pixel buffer objects could be more appropriate, but glDrawPixels() is more simple and compatible
                // within the context of this example.

                glRasterPos2i (raster_x, raster_y);
                glDrawPixels  (width, height, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, colors ());
            }

        };

    }

#endif
