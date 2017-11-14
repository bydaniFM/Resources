
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

        };

        template< class PIXEL_BUFFER_TYPE >
        void Rasterizer< PIXEL_BUFFER_TYPE >::draw_image (int x0, int y0, const Pixel_Buffer & image)
        {
            int width  = image.get_width  ();
            int height = image.get_height ();
            int pitch  = pixel_buffer.get_width ();
            int offset = pitch * y0 + x0;

            const Pixel_Buffer::Pixel * image_pixels  = image.pixels ();
                  Pixel_Buffer::Pixel * buffer_pixels = pixel_buffer.pixels () + offset;

			int right_x = x0 + width > pitch ? pitch : x0 + width;

			int region_width = right_x - x0;
			

			int delta2 = width - region_width;

			int delta1 = delta2 + pitch - width;

            while (height-- > 0)
            {
                for (const Pixel_Buffer::Pixel * end = image_pixels + region_width; image_pixels < end; buffer_pixels++, image_pixels++)
                {
                    *buffer_pixels = *image_pixels;
                }

                buffer_pixels += delta1;
				image_pixels  += delta2;
            }
        }

    }

#endif
