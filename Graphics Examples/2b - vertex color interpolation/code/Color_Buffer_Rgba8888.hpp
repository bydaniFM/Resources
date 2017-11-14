
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef COLOR_BUFFER_RGBA8888_HEADER
#define COLOR_BUFFER_RGBA8888_HEADER

    #include "Color_Buffer.hpp"
    #include <SFML/OpenGL.hpp>
    #include <stdint.h>             // This header is <csdint> on C++11...
    #include <vector>

    namespace example
    {

        class Color_Buffer_Rgba8888 : public Color_Buffer
        {
        public:

            struct Color
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

                    uint_fast32_t value;             // Beware of big/little endianness
                }
                data;

                Color()
                {
                    data.value = 0xFFFFffff;
                }

                Color(int r, int g, int b)
                {
                    data.component.r = uint8_t(r);
                    data.component.g = uint8_t(g);
                    data.component.b = uint8_t(b);
                    data.component.a = 255;
                }

                uint8_t get_r () const { return (data.component.r); }
                uint8_t get_g () const { return (data.component.g); }
                uint8_t get_b () const { return (data.component.b); }
            };

            typedef std::vector< Color > Buffer;

        private:

            Buffer buffer;
            Color  color;

        public:

            Color_Buffer_Rgba8888(size_t width, size_t height)
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
                color.data.component.r = uint8_t(r < 0 ? 0 : r > 255 ? 255 : r);
                color.data.component.g = uint8_t(g < 0 ? 0 : g > 255 ? 255 : g);
                color.data.component.b = uint8_t(b < 0 ? 0 : b > 255 ? 255 : b);
                color.data.component.a = 0xFF;                                      // Set opaque alpha
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
                glDrawPixels  (width, height, GL_RGBA, GL_UNSIGNED_BYTE, colors ());
            }

        };

    }

#endif
