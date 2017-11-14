
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

    #include <memory>
    #include "Rasterizer.hpp"
    #include "Pixel_Buffer_Argb1555.hpp"
    #include "Pixel_Buffer_Rgba8888.hpp"

    namespace example
    {

        class View
        {
        private:

            typedef Pixel_Buffer_Rgba8888 Pixel_Buffer;

        private:

            size_t width;
            size_t height;

            Pixel_Buffer                  pixel_buffer;
            std::auto_ptr< Pixel_Buffer > image;
            Rasterizer   < Pixel_Buffer > rasterizer;

        public:

            View(size_t width, size_t height, const char * image_path);

            bool load_image (const char * image_path);
            void paint      ();

        };

    }

#endif
