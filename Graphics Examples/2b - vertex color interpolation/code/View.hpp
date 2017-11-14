
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on october of 2013                                        *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include "Rasterizer.hpp"
    #include "Color_Buffer_Rgb565.hpp"
    #include "Color_Buffer_Rgba8888.hpp"

    namespace example
    {

        class View
        {
        private:

            typedef Color_Buffer_Rgba8888      Color_Buffer;
            typedef Color_Buffer::Color        Color;
            typedef Rasterizer< Color_Buffer > Rasterizer;

        private:

            size_t       width;
            size_t       height;

            Color_Buffer color_buffer;
            Rasterizer   rasterizer;

        public:

            View(size_t width, size_t height)
            :
                width       (width ),
                height      (height),
                color_buffer(width, height),
                rasterizer  (color_buffer )
            {
            }

            void paint ();

        };

    }

#endif
