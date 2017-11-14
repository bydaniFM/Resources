
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PIXEL_BUFFER_HEADER
#define PIXEL_BUFFER_HEADER

    #include <cstdint>

    namespace example
    {

        /// Enumeración útil para indexar color.component.value.
        enum 
        {
            RED, GREEN, BLUE, ALPHA
        };

        class Pixel_Buffer
        {
        public:

            /// Definición general de color equivalente a RGBA8888.
            union Color
            {
                uint32_t value;

                struct
                {
                    uint8_t value[4];
                }
                component;

                Color() { }

                Color(uint32_t rgba8888_value)
                {
                    value = rgba8888_value;
                }

                Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
                {
                    component.value[RED  ] = r;
                    component.value[GREEN] = g;
                    component.value[BLUE ] = b;
                    component.value[ALPHA] = a;
                }
            };

        protected:

            size_t width;
            size_t height;

        public:

            Pixel_Buffer(size_t width, size_t height)
            :
                width (width ),
                height(height)
            {
            }

        public:

            size_t get_width () const
            {
                return width;
            }

            size_t get_height () const
            {
                return height;
            }

            Color get_color (int x, int y) const
            {
                return get_color (y * width + x);
            }

        public:

            virtual size_t bits_per_pixel () const               = 0;
            virtual Color  get_color      (size_t offset) const  = 0;
            virtual void   set_color      (int r, int  g, int b) = 0;
            virtual void   set_pixel      (size_t offset)        = 0;
            virtual void   blit_to_window () const               = 0;

        };

    }

#endif
