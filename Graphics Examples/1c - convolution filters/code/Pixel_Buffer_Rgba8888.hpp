
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

            union Pixel
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

                int get_red   () const { return component.r; }
                int get_green () const { return component.g; }
                int get_blue  () const { return component.b; }

                void set (int r, int g, int b)
                {
                    component.r = uint8_t(r);
                    component.g = uint8_t(g);
                    component.b = uint8_t(b);
                    component.a = 0xFF;                                      // Set opaque alpha
                }
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

            size_t bits_per_pixel () const
            {
                return (sizeof(Pixel) * 8);
            }

        public:

            Pixel_Buffer::Color get_color (size_t offset) const
            {
                return buffer[offset].value;
            }

            void set_color (int r, int g, int b)
            {
                color.component.r = r;
                color.component.g = g;
                color.component.b = b;
                color.component.a = 0xFF;                                      // Set opaque alpha
            }

            void set_pixel (size_t offset)
            {
                buffer[offset] = color;
            }

            void set_pixel (size_t offset, const Pixel & color)
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
                glDrawPixels  (width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels ());
            }

        };

    }

#endif
