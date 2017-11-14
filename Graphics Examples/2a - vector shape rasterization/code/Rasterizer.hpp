
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef RASTERIZER_HEADER
#define RASTERIZER_HEADER

    #include <algorithm>

    namespace example
    {

        template< class PIXEL_BUFFER_TYPE >
        class Rasterizer
        {
        public:

            typedef PIXEL_BUFFER_TYPE Pixel_Buffer;

        private:

            Pixel_Buffer & pixel_buffer;

        public:

            Rasterizer(Pixel_Buffer & target)
            :
                pixel_buffer(target)
            {
            }

            const Pixel_Buffer & get_pixel_buffer () const
            {
                return (pixel_buffer);
            }

        public:

            void set_color (int r, int  g, int b)
            {
                pixel_buffer.set_color (r, g, b);
            }

            void set_pixel (int x, int  y)
            {
                pixel_buffer.set_pixel (x, y);
            }

            void draw_segment   (int x0, int y0, int x1, int y1);
            void draw_triangle  (int x0, int y0, int x1, int y1, int x2, int y2);
            void draw_rectangle (int x0, int y0, int width, int height);
            void draw_circle    (int x0, int y0, int radius);
            void draw_ellipse   (int x0, int y0, int width, int height);

            void fill_triangle  (int x0, int y0, int x1, int y1, int x2, int y2);
            void fill_rectangle (int x0, int y0, int width, int height);

        };

        template< class  PIXEL_BUFFER_TYPE >
        void Rasterizer< PIXEL_BUFFER_TYPE >::draw_segment (int x0, int y0, int x1, int y1)
        {
            if (y0 > y1)                                    // The line will be drawn from top to bottom
            {
                std::swap (x0, x1);
                std::swap (y0, y1);
            }

            int pitch  = pixel_buffer.get_width ();         // Width of the pixel buffer
            int offset = pitch * y0 + x0;                   // Start offset
            int end    = pitch * y1 + x1;                   // End offset

            if (x0 == x1)
            {
                while (offset < end)
                {
                    pixel_buffer.set_pixel (offset);

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
                    pixel_buffer.set_pixel (offset++);
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

                    while (offset < end)
                    {
                        pixel_buffer.set_pixel (offset);

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
                        pixel_buffer.set_pixel (offset);

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

        template< class  PIXEL_BUFFER_TYPE >
        void Rasterizer< PIXEL_BUFFER_TYPE >::draw_rectangle (int x0, int y0, int width, int height)
        {
            int pitch  = pixel_buffer.get_width ();         // Width of the pixel buffer
            int offset = pitch  * y0 + x0;                  // Start offset
            int delta  = pitch  * height;                   // Offset distance from the top to the bottom horizontal line
            int end    = offset + width;                    // End of the top horizontal line

            while (offset < end)
            {
                pixel_buffer.set_pixel (offset);
                pixel_buffer.set_pixel (offset + delta);

                offset++;
            }

            offset += pitch - width;                        // Start from the second scanline
            end    += delta;                                // Set the end to the start of the bottom horizontal line

            while (offset < end)
            {
                pixel_buffer.set_pixel (offset);
                pixel_buffer.set_pixel (offset + width);

                offset += pitch;
            }
        }

        template< class  PIXEL_BUFFER_TYPE >
        void Rasterizer< PIXEL_BUFFER_TYPE >::draw_circle (int x0, int y0, int radius)
        {
            int error  = -radius;
            int x      =  radius;
            int y      =  0;
            int pitch  =  pixel_buffer.get_width ();
            int offset =  pitch * y0 + x0;

            while (x >= y)
            {
                int x_delta = x * pitch;
                int y_delta = y * pitch;

                pixel_buffer.set_pixel (offset - y_delta - x);
                pixel_buffer.set_pixel (offset - x_delta - y);
                pixel_buffer.set_pixel (offset - y_delta + x);
                pixel_buffer.set_pixel (offset - x_delta + y);
                pixel_buffer.set_pixel (offset + y_delta - x);
                pixel_buffer.set_pixel (offset + x_delta - y);
                pixel_buffer.set_pixel (offset + y_delta + x);
                pixel_buffer.set_pixel (offset + x_delta + y);

                error += y++;
                error += y;

                if (error >= 0)
                {
                    error -= x--;
                    error -= x;
                }
            }
        }

        template< class  PIXEL_BUFFER_TYPE >
        void Rasterizer< PIXEL_BUFFER_TYPE >::draw_ellipse (int x0, int y0, int width, int height)
        {
            int x1      = x0 + width;
            int y1      = y0 + height;
            int a       = x1 - x0;
            int b       = y1 - y0;
            int b1      = b & 1;
            int delta_x = 4 * (1  - a) * b * b;
            int delta_y = 4 * (b1 + 1) * a * a;
            int error   = delta_x + delta_y + b1 * a * a;

            y0 += (b + 1) >> 1;
            y1  = y0 - b1;
            a  *= 8 * a;
            b1  = 8 * b * b;

            do
            {
                set_pixel (x1, y0);
                set_pixel (x0, y0);
                set_pixel (x0, y1);
                set_pixel (x1, y1);

                int e2 = error + error;

                if (e2 <= delta_y)
                {
                    y0++;
                    y1--;
                    error += delta_y += a;
                }

                if (e2 >= delta_x || error + error > delta_y)
                {
                    x0++;
                    x1--;
                    error += delta_x += b1;
                }
            }
            while (x0 <= x1);

            while (y0 - y1 < b)
            {
                set_pixel (x0 - 1, y0  );
                set_pixel (x1 + 1, y0++);
                set_pixel (x0 - 1, y1  );
                set_pixel (x1 + 1, y1--);
            }
        }

        template< class  PIXEL_BUFFER_TYPE >
        void Rasterizer< PIXEL_BUFFER_TYPE >::fill_triangle  (int x0, int y0, int x1, int y1, int x2, int y2)
        {
            if (y0 > y1) { std::swap (x0, x1); std::swap (y0, y1); }
            if (y1 > y2) { std::swap (x1, x2); std::swap (y1, y2); }
            if (y0 > y1) { std::swap (x0, x1); std::swap (y0, y1); }
            if (y1 > y2) { std::swap (x1, x2); std::swap (y1, y2); }

            if (y0 != y2)
            {
                int pitch   = pixel_buffer.get_width ();
                int y_delta = y1 -  y0;
                int left_x  = x0 + (x2 - x0) * (y1 - y0) / (y2 - y0);
                int right_x;

                if (left_x < x1)
                {
                    right_x = x1;
                }
                else
                {
                    right_x = left_x;
                    left_x  = x1;
                }

                int_fast64_t offset_left     =  int_fast64_t(pitch * y0 + x0    ) << 32;
                int_fast64_t offset_left_end =  int_fast64_t(pitch * y1 + left_x) << 32;
                int_fast64_t offset_right    =  offset_left;
                int_fast64_t pitch_shifted   =  int_fast64_t(pitch       ) << 32;
                int_fast64_t left_step       = (int_fast64_t(left_x  - x0) << 32) / y_delta + pitch_shifted;
                int_fast64_t right_step      = (int_fast64_t(right_x - x0) << 32) / y_delta + pitch_shifted;

                while (offset_left < offset_left_end)
                {
                    for (int offset = offset_left >> 32, end = offset_right >> 32; offset <= end; offset++)
                    {
                        pixel_buffer.set_pixel (offset);
                    }

                    offset_left  += left_step;
                    offset_right += right_step;
                }

                y_delta         =  y2 - y1;
                offset_left_end =  int_fast64_t(pitch * y2 /**/- pitch/**/ + x2) << 32;
                left_step       = (int_fast64_t(x2 - left_x ) << 32) / y_delta + pitch_shifted;
                right_step      = (int_fast64_t(x2 - right_x) << 32) / y_delta + pitch_shifted;

                while (offset_left < offset_left_end)
                {
                    for (int offset = offset_left >> 32, end = offset_right >> 32; offset <= end; offset++)
                    {
                        pixel_buffer.set_pixel (offset);
                    }

                    offset_left  += left_step;
                    offset_right += right_step;
                }
            }
        }

        template< class  PIXEL_BUFFER_TYPE >
        void Rasterizer< PIXEL_BUFFER_TYPE >::fill_rectangle (int x0, int y0, int width, int height)
        {
            int pitch  = pixel_buffer.get_width ();         // Width of the pixel buffer
            int offset = pitch * y0 + x0;                   // Start offset
            int delta  = pitch - width;                     // Distance from the end of one row to the beginning of the next
            int length = width;                             // Cached value

            while (height-- > 0)
            {
                for (int end = offset + width; offset < end; offset++)
                {
                    pixel_buffer.set_pixel (offset);
                }

                offset += delta;
                width   = length;
            }
        }

    }

#endif
