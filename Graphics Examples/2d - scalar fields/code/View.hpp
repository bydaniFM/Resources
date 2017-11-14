
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2016                                       *
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

            typedef Pixel_Buffer_Rgba8888 Pixel_Buffer;

			struct Field
			{
				float energy;

				float center_x;
				float center_y;

                float speed_x;
                float speed_y;

				float potential_at (float x, float y)
	            {
		            float  delta_x  = center_x - x;
		            float  delta_y  = center_y - y;

		            return energy / (delta_x * delta_x + delta_y * delta_y);
	            }
			};

            static const size_t number_of_fields = 15;

        private:

            size_t       width;
            size_t       height;
            Pixel_Buffer pixel_buffer;
			
			std::vector< Field > fields;

        public:

            View(size_t width, size_t height);

            void update ();
            void render ();

        };

    }

#endif
