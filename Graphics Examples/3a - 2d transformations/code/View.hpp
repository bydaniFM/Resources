
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

    #include <vector>
    #include <Point.hpp>
    #include "Rasterizer.hpp"
    #include "Color_Buffer_Rgb565.hpp"
    #include "Color_Buffer_Rgba8888.hpp"

    namespace example
    {

        class View
        {
        private:

            typedef Color_Buffer_Rgb565   Color_Buffer;
            typedef toolkit::Point3f      Vertex;
            typedef std::vector< Vertex > Vertex_Buffer;
            typedef std::vector< int    > Index_Buffer;

        private:

            size_t width;
            size_t height;

            Color_Buffer               color_buffer;
            Rasterizer< Color_Buffer > rasterizer;

            Vertex_Buffer original_vertices;
            Vertex_Buffer transformed_vertices;
            Index_Buffer  indices;

        public:

            View(size_t width, size_t height);

            void update ();
            void paint  ();

        };

    }

#endif
