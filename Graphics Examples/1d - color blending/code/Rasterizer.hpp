
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

            void clear (int r, int g, int b)
            {
                set_color (r, g, b);

                for (int offset = 0, end = pixel_buffer.get_width () * pixel_buffer.get_height (); offset < end; offset++)
                {
                    pixel_buffer.set_pixel (offset);
                }
            }

            void draw_image (int x0, int y0, const Pixel_Buffer & image);
            void draw_image_with_transparency (int x0, int y0, const Pixel_Buffer & image, int alpha);

        };

        template< class PIXEL_BUFFER_TYPE >
        void Rasterizer< PIXEL_BUFFER_TYPE >::draw_image (int x0, int y0, const Pixel_Buffer & image)
        {
            int width  = image.get_width  ();
            int height = image.get_height ();
            int pitch  = pixel_buffer.get_width ();
            int offset = pitch * y0 + x0;
            int delta  = pitch - width;

            const Pixel_Buffer::Pixel * image_pixels  = image.pixels ();
                  Pixel_Buffer::Pixel * buffer_pixels = pixel_buffer.pixels () + offset;

            while (height-- > 0)
            {
                for (Pixel_Buffer::Pixel * end = buffer_pixels + width; buffer_pixels < end; buffer_pixels++, image_pixels++)
                {
                    *buffer_pixels = *image_pixels;
                }

                buffer_pixels += delta;
            }
        }

        template< class PIXEL_BUFFER_TYPE >
        void Rasterizer< PIXEL_BUFFER_TYPE >::draw_image_with_transparency (int x0, int y0, const Pixel_Buffer & image, int alpha)
        {
            if (alpha <=   0) { return; }
            if (alpha >= 255) { draw_image (x0, y0, image); return; }

            int width  = image.get_width  ();
            int height = image.get_height ();
            int pitch  = pixel_buffer.get_width ();
            int offset = pitch * y0 + x0;
            int delta  = pitch - width;

            const Pixel_Buffer::Pixel * image_pixels  = image.pixels ();
                  Pixel_Buffer::Pixel * buffer_pixels = pixel_buffer.pixels () + offset;

            int alpha_comp = 255 - alpha;

            while (height-- > 0)
            {
                for (Pixel_Buffer::Pixel * end = buffer_pixels + width; buffer_pixels < end; buffer_pixels++, image_pixels++)
                {
                    int ra =  image_pixels->get_red   ();
                    int ga =  image_pixels->get_green ();
                    int ba =  image_pixels->get_blue  ();
                    int rb = buffer_pixels->get_red   ();
                    int gb = buffer_pixels->get_green ();
                    int bb = buffer_pixels->get_blue  ();

                    buffer_pixels->set
                    (
                        (ra * alpha + rb * alpha_comp) >> 8,
                        (ga * alpha + gb * alpha_comp) >> 8,
                        (ba * alpha + bb * alpha_comp) >> 8
                    );
                }

                buffer_pixels += delta;
            }
        }

    }

#endif
