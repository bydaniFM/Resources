
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

    #include "Pixel_Buffer_Rgb565.hpp"
    #include "Pixel_Buffer_Rgba8888.hpp"

    namespace example
    {

        class View
        {
        private:

            typedef Pixel_Buffer_Rgb565 Pixel_Buffer;

        private:

            size_t       width;
            size_t       height;
            Pixel_Buffer pixel_buffer;

        public:

            View(size_t width, size_t height)
            :
                width       (width ),
                height      (height),
                pixel_buffer(width, height)
            {
            }

            void paint ();

        };

    }

#endif
