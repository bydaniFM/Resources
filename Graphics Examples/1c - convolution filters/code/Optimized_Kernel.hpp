
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2015                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef OPTIMIZED_KERNEL_HEADER
#define OPTIMIZED_KERNEL_HEADER

    #include "Pixel_Buffer.hpp"
    #include "Pixel_Buffer_Rgba8888.hpp"

    namespace example
    {

        template< size_t ROWS, size_t COLUMNS, class PIXEL_BUFFER >
        class Optimized_Kernel
        {
        public:

            static  const int rows    = ROWS;
            static  const int columns = COLUMNS;

            typedef PIXEL_BUFFER Pixel_Buffer;
            typedef typename Pixel_Buffer::Color Color;

        private:

            int values[columns * rows];         ///< Valores de la matriz del kernel
            int divisor;                        ///< Divisor del kernel

        public:

            Optimized_Kernel()
            {
                reset ();
            }

            /// Inicializa el kernel de modo tal que tenga un efecto neutro.
            ///
            void reset ()
            {
                // Se inicializan todos los valores de la matriz del kernel a cero:

                for (size_t index = 0, end = rows * columns; index < end; index++)
                {
                    values[index] = 0;
                }

                // A continuación se establece el valor 1 en la posición central de
                // la matriz para conseguir un kernel neutro (sin efecto):

                set (columns / 2, rows / 2, 1);

                divisor = 1;
            }

            void set (int row, int column, int value)
            {
                values[row * columns + column] = value;
            }

            void set_divisor (int new_divisor)
            {
                divisor = new_divisor;
            }

            /// Aplica el kernel a un pixel de una imagen guardando el resultado en otra imagen.
            ///
            void apply (Pixel_Buffer & input_image, Pixel_Buffer & output_image);

        };

        template< size_t ROWS, size_t COLUMNS, class PIXEL_BUFFER >
        void Optimized_Kernel< ROWS, COLUMNS, PIXEL_BUFFER >::apply (Pixel_Buffer & input_image, Pixel_Buffer & output_image)
        {
            // Se inicializan algunas variables:

            int image_width        = input_image.get_width  ();
            int image_height       = input_image.get_height ();
            int kernel_radius_y    = rows    / 2;
            int kernel_radius_x    = columns / 2;
            int secure_top_y       = kernel_radius_y;
            int secure_bottom_y    = image_height - kernel_radius_y;
            int secure_left_x      = kernel_radius_x;
            int secure_right_x     = image_width  - kernel_radius_x;

            int image_offset       = kernel_radius_y * image_width + secure_left_x;
            int image_offset_delta = kernel_radius_x * 2;

            for (int y = secure_top_y; y < secure_bottom_y; y++, image_offset += image_offset_delta)
            {
                for (int x = secure_left_x; x < secure_right_x; x++, image_offset++)
                {
                    // Se calcula la suma de productos de la matriz de convolución con los componentes de la imagen involucrados:

                    int   total_r = 0;
                    int   total_g = 0;
                    int   total_b = 0;

                    int   image_aligned_offset       = (y - rows / 2) * image_width + (x - columns / 2);
                    int   image_aligned_offset_delta = image_width - columns;
                    int * value_pointer              = values;

                    for (int j = 0; j < rows; j++)
                    {
                        for (int i = 0; i < columns; i++)
                        {
                            Color color =  input_image.get_color (image_aligned_offset++);
                            int   value = *value_pointer++;

                            total_r += value * color.component.value[RED  ];
                            total_g += value * color.component.value[GREEN];
                            total_b += value * color.component.value[BLUE ];
                        }

                        image_aligned_offset += image_aligned_offset_delta;
                    }

                    // Se ajusta el resultado de la suma de productos:

                    total_r /= divisor;
                    total_g /= divisor;
                    total_b /= divisor;

                    // Se establece el color resultante en la imagen de salida aplicando un clamping RGB:

                    output_image.set_color
                    (
                        total_r < 0 ? 0 : total_r > 255 ? 255 : total_r,
                        total_g < 0 ? 0 : total_g > 255 ? 255 : total_g,
                        total_b < 0 ? 0 : total_b > 255 ? 255 : total_b
                    );

                    output_image.set_pixel (image_offset);
                }
            }
        }

        template< >
        void Optimized_Kernel< 3, 3, Pixel_Buffer_Rgba8888 >::apply (Pixel_Buffer_Rgba8888 & input_image, Pixel_Buffer_Rgba8888 & output_image);

    }

#endif
