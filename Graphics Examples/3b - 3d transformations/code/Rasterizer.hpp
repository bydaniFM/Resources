
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on december of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef RASTERIZER_HEADER
#define RASTERIZER_HEADER

    #include <stdint.h>
    #include <Point.hpp>
    #include <algorithm>

    namespace example
    {

        using toolkit::Point;

        template< class COLOR_BUFFER_TYPE >
        class Rasterizer
        {
        public:

            typedef COLOR_BUFFER_TYPE Color_Buffer;

        private:

            Color_Buffer & color_buffer;

            int offset_cache0[1082];
            int offset_cache1[1082];

        public:

            Rasterizer(Color_Buffer & target)
            :
                color_buffer(target)
            {
            }

            const Color_Buffer & get_color_buffer () const
            {
                return (color_buffer);
            }

        public:

            void set_color (int r, int  g, int b)
            {
                color_buffer.set_color (r, g, b);
            }

            void clear ()
            {
                for (Color_Buffer::Color * c = color_buffer.colors (), * end = c + color_buffer.size (); c < end; c++)
                {
                    *c = 0;
                }
            }

            void set_pixel (int x, int y)
            {
                color_buffer.set_pixel (x, y);
            }

            void draw_segment  (int x0, int y0, int x1, int y1);
            void draw_triangle (int x0, int y0, int x1, int y1, int x2, int y2);

        };


        template< class  PIXEL_BUFFER_TYPE >
        void Rasterizer< PIXEL_BUFFER_TYPE >::draw_segment (int x0, int y0, int x1, int y1)
        {
            if (y0 > y1)                                    // The line will be drawn from top to bottom
            {
                std::swap (x0, x1);
                std::swap (y0, y1);
            }

            int pitch  = color_buffer.get_width ();         // Width of the pixel buffer
            int offset = pitch * y0 + x0;                   // Start offset
            int end    = pitch * y1 + x1;                   // End offset

            if (x0 == x1)
            {
                while (offset < end)
                {
                    color_buffer.set_pixel (offset);

                    offset += pitch;
                }
            }
            else
            if (y0 == y1)
            {
                if (offset > end)                           // This may only be swapped when y0 == y1
                {
                    std::swap (offset, end);
                }

                while (offset < end)
                {
                    color_buffer.set_pixel (offset++);
                }
            }
            else
            {
                int y_delta = y1 - y0;
                int x_delta;
                int x_step;

                if (x0 < x1)
                {
                    x_delta = x1 - x0;
                    x_step  = +1;
                }
                else
                {
                    x_delta = x0 - x1;
                    x_step  = -1;
                }

                if (x_delta > y_delta)
                {
                    int error = x_delta >> 1;

                    while (offset != end)
                    {
                        color_buffer.set_pixel (offset);

                        offset += x_step;
                        error  += y_delta;

                        if (error > x_delta)
                        {
                            offset += pitch;
                            error  -= x_delta;
                        }
                    }
                }
                else
                {
                    int error = y_delta >> 1;

                    while (offset < end)
                    {
                        color_buffer.set_pixel (offset);

                        offset += pitch;
                        error  += x_delta;

                        if (error > y_delta)
                        {
                            offset += x_step;
                            error  -= y_delta;
                        }
                    }
                }
            }
        }

        template< class  PIXEL_BUFFER_TYPE >
        inline void Rasterizer< PIXEL_BUFFER_TYPE >::draw_triangle (int x0, int y0, int x1, int y1, int x2, int y2)
        {
            draw_segment (x0, y0, x1, y1);
            draw_segment (x0, y0, x2, y2);
            draw_segment (x1, y1, x2, y2);
        }

    }

#endif
