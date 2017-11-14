
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

        template< class COLOR_BUFFER_TYPE >
        class Rasterizer
        {
        public:

            typedef          COLOR_BUFFER_TYPE   Color_Buffer;
            typedef typename Color_Buffer::Color Color;

        private:

            Color_Buffer & color_buffer;

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

            void clear (int r, int g, int b)
            {
                set_color (r, g, b);

                for (int offset = 0, end = color_buffer.get_width () * color_buffer.get_height (); offset < end; offset++)
                {
                    color_buffer.set (offset);
                }
            }

            void fill_triangle (int x0, int y0, int x1, int y1, int x2, int y2, Color color0, Color color1, Color color2);

        private:

            void fill_trapezoid
            (
                int   left_x0,          int   right_x0,
                int   left_x1,          int   right_x1,
                int   min_y,            int   max_y,
                Color left_color0,      Color right_color0,
                Color left_color1,      Color right_color1,
                int   left_color_delta, int   right_color_delta,
                int   left_color_skip,  int   right_color_skip
            );

        };

        template< class  COLOR_BUFFER_TYPE >
        void Rasterizer< COLOR_BUFFER_TYPE >::fill_triangle (int x0, int y0, int x1, int y1, int x2, int y2, Color c0, Color c1, Color c2)
        {
            // Se ordenan los vértices de coordenada Y menor a mayor (y0 < y1 < y2).
            // Cabe resaltar que y1 queda en medio de y0 e y2.

            if (y0 > y1) { std::swap (x0, x1); std::swap (y0, y1); std::swap (c0, c1); }
            if (y1 > y2) { std::swap (x1, x2); std::swap (y1, y2); std::swap (c1, c2); }
            if (y0 > y1) { std::swap (x0, x1); std::swap (y0, y1); std::swap (c0, c1); }

            // Si el triángulo no tiene al menos un píxel de altura no se dibuja:

            if (y0 == y2) return;

            // Se calcula la coordenada X de la intersección entre la recta P0-P2 (puntos con Y menor y mayor) y la recta y=y1

            int cut_x1 = x0 + (x2 - x0) * (y1 - y0) / (y2 - y0);

            // Se dibujan las dos mitades que quedan por encima y por debajo de y=y1:

            if (cut_x1 < x1)
            {
                if (y0 < y1) fill_trapezoid (x0, x0, cut_x1, x1,  y0, y1,  c0, c0, c2, c1,  y2 - y0, y1 - y0,       0, 0);
                if (y1 < y2) fill_trapezoid (cut_x1, x1, x2, x2,  y1, y2,  c0, c1, c2, c2,  y2 - y0, y2 - y1, y1 - y0, 0);
            }
            else
            {
                if (y0 < y1) fill_trapezoid (x0, x0, x1, cut_x1,  y0, y1,  c0, c0, c1, c2,  y1 - y0, y2 - y0, 0,       0);
                if (y1 < y2) fill_trapezoid (x1, cut_x1, x2, x2,  y1, y2,  c1, c0, c2, c2,  y2 - y1, y2 - y0, 0, y1 - y0);
            }
        }

        template< class  COLOR_BUFFER_TYPE >
        void Rasterizer< COLOR_BUFFER_TYPE >::fill_trapezoid
        (
            int   left_x0,          int   right_x0,
            int   left_x1,          int   right_x1,
            int   min_y,            int   max_y,
            Color left_color0,      Color right_color0,
            Color left_color1,      Color right_color1,
            int   left_color_delta, int   right_color_delta,
            int   left_color_skip,  int   right_color_skip
        )
        {
            // Se cachea en variables locales el ancho del buffer:

            int     pitch  = color_buffer.get_width ();
            int64_t pitch_ = int64_t(pitch) << 32;

            // Se calcula la altura del trapecio:

            int y_delta = max_y - min_y;

            // Se calculan los offsets izquierdo y derecho así como los saltos de offset por cada scanline:

            int64_t  left_offset_      = (int64_t( pitch * min_y +  left_x0 ) << 32);
            int64_t  left_offset_end_  = (int64_t( pitch * max_y +  left_x0 ) << 32);
            int64_t right_offset_      = (int64_t( pitch * min_y + right_x0 ) << 32);
            int64_t  left_offset_step_ = (int64_t(       left_x1 -  left_x0 ) << 32) / y_delta + pitch_;
            int64_t right_offset_step_ = (int64_t(      right_x1 - right_x0 ) << 32) / y_delta + pitch_;

            // Se calculan los colores izquierdo y derecho así como los saltos de color por cada scanline:

            int lr0 =  left_color0.get_r (), lg0 =  left_color0.get_g (), lb0 =  left_color0.get_b ();
            int rr0 = right_color0.get_r (), rg0 = right_color0.get_g (), rb0 = right_color0.get_b ();
            int lr1 =  left_color1.get_r (), lg1 =  left_color1.get_g (), lb1 =  left_color1.get_b ();
            int rr1 = right_color1.get_r (), rg1 = right_color1.get_g (), rb1 = right_color1.get_b ();

            int left_r_ = lr0 << 16, right_r_ = rr0 << 16;
            int left_g_ = lg0 << 16, right_g_ = rg0 << 16;
            int left_b_ = lb0 << 16, right_b_ = rb0 << 16;

            int left_r_step_ = ((lr1 - lr0) << 16) / left_color_delta, right_r_step_ = ((rr1 - rr0) << 16) / right_color_delta;
            int left_g_step_ = ((lg1 - lg0) << 16) / left_color_delta, right_g_step_ = ((rg1 - rg0) << 16) / right_color_delta;
            int left_b_step_ = ((lb1 - lb0) << 16) / left_color_delta, right_b_step_ = ((rb1 - rb0) << 16) / right_color_delta;

            if (left_color_skip > 0)
            {
                left_r_  += left_r_step_  * left_color_skip;
                left_g_  += left_g_step_  * left_color_skip;
                left_b_  += left_b_step_  * left_color_skip;
            }

            if (right_color_skip > 0)
            {
                right_r_ += right_r_step_ * right_color_skip;
                right_g_ += right_g_step_ * right_color_skip;
                right_b_ += right_b_step_ * right_color_skip;
            }

            // Se rellenan todas las scanlines del trapecio:

            while (left_offset_ < left_offset_end_)
            {
                // Se calculan los offsets izquierdo y derecho de la scanline y su ancho:

                int offset  = left_offset_  >> 32;
                int end     = right_offset_ >> 32;
                int x_delta = end - offset;

                if (x_delta > 0)
                {
                    // Se inicializa el color por el extremo izquierdo y se calcula el salto de color
                    // por cada píxel hasta el extremo derecho:

                    int r_ = left_r_;
                    int g_ = left_g_;
                    int b_ = left_b_;

                    int r_step_ = (right_r_ - left_r_) / x_delta;
                    int g_step_ = (right_g_ - left_g_) / x_delta;
                    int b_step_ = (right_b_ - left_b_) / x_delta;

                    // Se rellena la scanline:

                    while (offset <= end)
                    {
                        color_buffer.set_color (r_ >> 16, g_ >> 16, b_ >> 16);
                        color_buffer.set (offset++);

                        r_ += r_step_;
                        g_ += g_step_;
                        b_ += b_step_;
                    }
                }

                // Se ajustan los parámetros de color y offset para pasar a la siguiente scanline:

                left_r_  +=  left_r_step_;
                left_g_  +=  left_g_step_;
                left_b_  +=  left_b_step_;

                right_r_ += right_r_step_;
                right_g_ += right_g_step_;
                right_b_ += right_b_step_;

                left_offset_  +=  left_offset_step_;
                right_offset_ += right_offset_step_;
            }
        }

    }

#endif
