
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
    #include "Kernel.hpp"
    #include "Rasterizer.hpp"
    #include "Optimized_Kernel.hpp"
    #include "Pixel_Buffer_Argb1555.hpp"
    #include "Pixel_Buffer_Rgba8888.hpp"

    namespace example
    {

        class View
        {
        private:

            typedef Pixel_Buffer_Rgba8888 Pixel_Buffer;

        private:

            size_t width;                                       ///< Ancho de la vista (normalmente igual al de la ventana)
            size_t height;                                      ///< Alto  de la vista (normalmente igual al de la ventana)

            Pixel_Buffer                  pixel_buffer;         ///< Pixel buffer del contenido de la ventana
            std::auto_ptr< Pixel_Buffer > image;                ///< Pixel buffer de la imagen que se carga de un archivo
            std::auto_ptr< Pixel_Buffer > filtered_image;       ///< Pixel buffer de la imagen que resulta de aplicar un filtro a la imagen cargada
            Rasterizer   < Pixel_Buffer > rasterizer;           ///< Rasterizer usado para realizar el blitting
            Kernel< 3, 3,  Pixel_Buffer > kernel;               ///< Kernel usado para aplicar un filtro de convolución a la imagen cargada

            Optimized_Kernel< 3, 3,  Pixel_Buffer > optimized_kernel;               ///< Kernel usado para aplicar un filtro de convolución a la imagen cargada

        public:

            View(size_t width, size_t height, const char * image_path);

        public:

            bool load_image             (const char * image_path);
            void apply_filter           ();
            void apply_optimized_filter ();
            void paint                  ();

        };

    }

#endif
