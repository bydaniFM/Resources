
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2015                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef KERNEL_HEADER
#define KERNEL_HEADER

    #include "Pixel_Buffer.hpp"

    namespace example
    {

        template< size_t ROWS, size_t COLUMNS, class PIXEL_BUFFER >
        class Kernel
        {
        public:

            static  const int rows    = ROWS;
            static  const int columns = COLUMNS;

            typedef PIXEL_BUFFER Pixel_Buffer;

        private:

            int values[columns][rows];          ///< Valores de la matriz del kernel
            int divisor;                        ///< Divisor del kernel

        public:

            Kernel()
            {
                reset ();
            }

            /// Inicializa el kernel de modo tal que tenga un efecto neutro.
            ///
            void reset ()
            {
                // Se inicializan todos los valores de la matriz del kernel a cero:

                for (size_t j = 0; j < rows; j++)
                    for (size_t i = 0; i < columns; i++)
                        values[i][j] = 0;

                // A continuación se establece el valor 1 en la posición central de
                // la matriz para conseguir un kernel neutro (sin efecto):

                values[columns / 2][rows / 2] = 1;

                divisor = 1;
            }

            void set (int row, int column, int value)
            {
                values[column][row] = value;
            }

            void set_divisor (int new_divisor)
            {
                divisor = new_divisor;
            }

            /// Aplica el kernel a un pixel de una imagen guardando el resultado en otra imagen.
            ///
            void apply (Pixel_Buffer & input_image, Pixel_Buffer & output_image, int x, int y);

        };

        template< size_t ROWS, size_t COLUMNS, class PIXEL_BUFFER >
        void Kernel< ROWS, COLUMNS, PIXEL_BUFFER >::apply (Pixel_Buffer & input_image, Pixel_Buffer & output_image, int x, int y)
        {
            // Se inicializan algunas variables:

            int image_width  = input_image.get_width  ();
            int image_height = input_image.get_height ();

            int total_r = 0;
            int total_g = 0;
            int total_b = 0;

            // Se calcula la suma de productos de la matriz de convolución con los componentes de la imagen involucrados:

            for (int j = 0; j < rows; j++)
            {
                for (int i = 0; i < columns; i++)
                {
                    // Se determinan las coordenadas del pixel involucrado:

                    int aligned_x = x + i - columns / 2;
                    int aligned_y = y + j - rows    / 2;

                    // Se aplica un clamping de coordenadas (x,y):

                    aligned_x = aligned_x < 0 ? 0 : aligned_x >= image_width  ? image_width  - 1 : aligned_x;
                    aligned_y = aligned_y < 0 ? 0 : aligned_y >= image_height ? image_height - 1 : aligned_y;

                    // Se lee el color del pixel de la imagen de entrada normalizado a RGBA8888:

                    Pixel_Buffer::Color input_color = input_image.get_color (aligned_y * image_width + aligned_x);

                    // Se suman los productos:

                    total_r += values[i][j] * input_color.component.value[RED  ];
                    total_g += values[i][j] * input_color.component.value[GREEN];
                    total_b += values[i][j] * input_color.component.value[BLUE ];
                }
            }

            // Se ajusta el resultado de la suma de productos:

            total_r /= divisor;
            total_g /= divisor;
            total_b /= divisor;

            // Se aplica un clamping RGB:

            total_r  = total_r < 0 ? 0 : total_r > 255 ? 255 : total_r;
            total_g  = total_g < 0 ? 0 : total_g > 255 ? 255 : total_g;
            total_b  = total_b < 0 ? 0 : total_b > 255 ? 255 : total_b;

            // Se establece el color resultante en la imagen de salida:

            output_image.set_color (total_r, total_g, total_b);
            output_image.set_pixel (y * output_image.get_width () + x);
        }

    }

#endif
