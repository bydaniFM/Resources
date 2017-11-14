
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2015                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Optimized_Kernel.hpp"

//#define CPP_VERSION
#define IA32_ASSEMBLY_VERSION
//#define SSE2_ASSEMBLY_VERSION

namespace example
{

    #if defined(CPP_VERSION)

        template< >
        void Optimized_Kernel< 3, 3, Pixel_Buffer_Rgba8888 >::apply (Pixel_Buffer_Rgba8888 & input_image, Pixel_Buffer_Rgba8888 & output_image)
        {
            typedef Pixel_Buffer_Rgba8888::Pixel Color;

            // Se inicializan algunas variables:

            int image_width     = input_image.get_width  ();
            int image_height    = input_image.get_height ();
            int kernel_radius_y = rows    / 2;
            int kernel_radius_x = columns / 2;
            int secure_top_y    = kernel_radius_y;
            int secure_bottom_y = image_height - kernel_radius_y;
            int secure_left_x   = kernel_radius_x;
            int secure_right_x  = image_width  - kernel_radius_x;
        
            Color *  output_image_pointer       = output_image.pixels () + kernel_radius_y * image_width + secure_left_x;
            int             image_pointer_delta = kernel_radius_x * 2;
            Color * aligned_image_pointer_base  = input_image.pixels () + (secure_top_y - rows / 2) * image_width + (secure_left_x - columns / 2);
            int     aligned_image_pointer_delta = image_width - columns + 3;

            for (int y = secure_top_y; y < secure_bottom_y; y++)
            {
                for (int x = secure_left_x; x < secure_right_x; x++)
                {
                    // Se calcula la suma de productos de la matriz de convolución con los componentes de la imagen involucrados:

                    int total_r = 0;
                    int total_g = 0;
                    int total_b = 0;

                    Color * aligned_image_pointer = aligned_image_pointer_base;
                    int   * value_pointer         = values;

                    for (int j = 0; j < rows; j++)
                    {
                        Color color0 = aligned_image_pointer[0];
                        Color color1 = aligned_image_pointer[1];
                        Color color2 = aligned_image_pointer[2];

                        int   value0 = value_pointer[0];
                        int   value1 = value_pointer[1];
                        int   value2 = value_pointer[2];

                        total_r += value0 * color0.component.r;
                        total_g += value0 * color0.component.g;
                        total_b += value0 * color0.component.b;
                        total_r += value1 * color1.component.r;
                        total_g += value1 * color1.component.g;
                        total_b += value1 * color1.component.b;
                        total_r += value2 * color2.component.r;
                        total_g += value2 * color2.component.g;
                        total_b += value2 * color2.component.b;

                        aligned_image_pointer += aligned_image_pointer_delta;
                        value_pointer         += 3;
                    }

                    // Se ajusta el resultado de la suma de productos:

                    total_r /= divisor;
                    total_g /= divisor;
                    total_b /= divisor;

                    // Se establece el color resultante en la imagen de salida aplicando un clamping RGB:

                    output_image_pointer->component.r = total_r < 0 ? 0 : total_r > 255 ? 255 : total_r;
                    output_image_pointer->component.g = total_g < 0 ? 0 : total_g > 255 ? 255 : total_g;
                    output_image_pointer->component.b = total_b < 0 ? 0 : total_b > 255 ? 255 : total_b;

                    output_image_pointer++;
                   aligned_image_pointer_base++;
                }

                aligned_image_pointer_base += image_pointer_delta;
                 output_image_pointer      += image_pointer_delta;
            }
        }

    #elif defined(IA32_ASSEMBLY_VERSION)

        #if !defined(_MSC_VER)
            #error "A Microsoft compiler is required for compiling the IA32_ASSEMBLY_VERSION"
        #endif

        template< >
        void Optimized_Kernel< 3, 3, Pixel_Buffer_Rgba8888 >::apply (Pixel_Buffer_Rgba8888 & input_image, Pixel_Buffer_Rgba8888 & output_image)
        {
            typedef Pixel_Buffer_Rgba8888::Pixel Color;

            // Se inicializan algunas variables:

            int image_width     = input_image.get_width  ();
            int image_height    = input_image.get_height ();
            int kernel_radius_y = rows    / 2;
            int kernel_radius_x = columns / 2;
            int secure_top_y    = kernel_radius_y;
            int secure_bottom_y = image_height - kernel_radius_y;
            int secure_left_x   = kernel_radius_x;
            int secure_right_x  = image_width  - kernel_radius_x;

            Color *  output_image_pointer       = output_image.pixels () + kernel_radius_y * image_width + secure_left_x;
            int             image_pointer_delta = kernel_radius_x * 2;
            Color * aligned_image_pointer_base  = input_image.pixels () + (secure_top_y - rows / 2) * image_width + (secure_left_x - columns / 2);
            int     aligned_image_pointer_delta = (image_width - columns + 3) * 4;

            int     divisor = this->divisor;
            int   * values  = this->values;

            for (int y = secure_top_y; y < secure_bottom_y; y++)
            {
                for (int x = secure_left_x; x < secure_right_x; x++)
                {
                    __asm
                    {
                        mov     esi, [aligned_image_pointer_base]

                    // Se desenrollan las 9 iteraciones de los dos bucles anidados (i,j) que aplican el kernel:

                        mov     edi, [values]
                        mov     edi, [edi]
                        movzx   eax, byte ptr [esi+0]               // total_r -> EAX
                        movzx   ebx, byte ptr [esi+1]               // total_g -> EBX
                        movzx   ecx, byte ptr [esi+2]               // total_b -> ECX
                        imul    eax, edi
                        imul    ebx, edi
                        imul    ecx, edi

                        mov     edi, [values]
                        mov     edi, [edi+4]
                        movzx   edx, byte ptr [esi+4]
                        imul    edx, edi
                        add     eax, edx
                        movzx   edx, byte ptr [esi+5]
                        imul    edx, edi
                        add     ebx, edx
                        movzx   edx, byte ptr [esi+6]
                        imul    edx, edi
                        add     ecx, edx

                        mov     edi, [values]
                        mov     edi, [edi+8]
                        movzx   edx, byte ptr [esi+8]
                        imul    edx, edi
                        add     eax, edx
                        movzx   edx, byte ptr [esi+9]
                        imul    edx, edi
                        add     ebx, edx
                        movzx   edx, byte ptr [esi+10]
                        imul    edx, edi
                        add     ecx, edx

                        add     esi, [aligned_image_pointer_delta]

                        mov     edi, [values]
                        mov     edi, [edi+12]
                        movzx   edx, byte ptr [esi+0]
                        imul    edx, edi
                        add     eax, edx
                        movzx   edx, byte ptr [esi+1]
                        imul    edx, edi
                        add     ebx, edx
                        movzx   edx, byte ptr [esi+2]
                        imul    edx, edi
                        add     ecx, edx

                        mov     edi, [values]
                        mov     edi, [edi+16]
                        movzx   edx, byte ptr [esi+4]
                        imul    edx, edi
                        add     eax, edx
                        movzx   edx, byte ptr [esi+5]
                        imul    edx, edi
                        add     ebx, edx
                        movzx   edx, byte ptr [esi+6]
                        imul    edx, edi
                        add     ecx, edx

                        mov     edi, [values]
                        mov     edi, [edi+20]
                        movzx   edx, byte ptr [esi+8]
                        imul    edx, edi
                        add     eax, edx
                        movzx   edx, byte ptr [esi+9]
                        imul    edx, edi
                        add     ebx, edx
                        movzx   edx, byte ptr [esi+10]
                        imul    edx, edi
                        add     ecx, edx

                        add     esi, [aligned_image_pointer_delta]

                        mov     edi, [values]
                        mov     edi, [edi+24]
                        movzx   edx, byte ptr [esi+0]
                        imul    edx, edi
                        add     eax, edx
                        movzx   edx, byte ptr [esi+1]
                        imul    edx, edi
                        add     ebx, edx
                        movzx   edx, byte ptr [esi+2]
                        imul    edx, edi
                        add     ecx, edx

                        mov     edi, [values]
                        mov     edi, [edi+28]
                        movzx   edx, byte ptr [esi+4]
                        imul    edx, edi
                        add     eax, edx
                        movzx   edx, byte ptr [esi+5]
                        imul    edx, edi
                        add     ebx, edx
                        movzx   edx, byte ptr [esi+6]
                        imul    edx, edi
                        add     ecx, edx

                        mov     edi, [values]
                        mov     edi, [edi+32]
                        movzx   edx, byte ptr [esi+8]
                        imul    edx, edi
                        add     eax, edx
                        movzx   edx, byte ptr [esi+9]
                        imul    edx, edi
                        add     ebx, edx
                        movzx   esi, byte ptr [esi+10]
                        imul    esi, edi
                        add     esi, ecx

                    // Se calcula total_r / divisor, se clampea el resultado y se guarda:

                        mov     ecx, 255
                        mov     edi, [output_image_pointer]

                        xor     edx, edx
                        idiv    [divisor]
                        test    eax, eax
                        jl      red_underflow
                        cmp     eax, ecx
                        ja      red_overflow
                        mov     [edi], al
                        jmp     set_green
                    red_underflow:
                        mov     [edi], ch
                        jmp     set_green
                    red_overflow:
                        mov     [edi], cl

                        // Se calcula total_g / divisor, se clampea el resultado y se guarda:

                    set_green:
                        mov     eax, ebx
                        xor     edx, edx
                        idiv    [divisor]
                        test    eax, eax
                        jl      green_underflow
                        cmp     eax, ecx
                        ja      green_overflow
                        mov     [edi+1], al
                        jmp     set_blue
                    green_underflow:
                        mov     [edi+1], ch
                        jmp     set_blue
                    green_overflow:
                        mov     [edi+1], cl

                        // Se calcula total_b / divisor, se clampea el resultado y se guarda:

                    set_blue:
                        mov     eax, esi
                        xor     edx, edx
                        idiv    [divisor]
                        test    eax, eax
                        jl      blue_underflow
                        cmp     eax, ecx
                        ja      blue_overflow
                        mov     [edi+2], al
                        jmp     scanline_end
                    blue_underflow:
                        mov     [edi+2], ch
                        jmp     scanline_end
                    blue_overflow:
                        mov     [edi+2], cl

                    scanline_end:

                        add     [ output_image_pointer], 4
                        add     [aligned_image_pointer_base], 4
                    }
                }

                aligned_image_pointer_base += image_pointer_delta;
                 output_image_pointer      += image_pointer_delta;
            }
        }

    #elif defined(SSE2_ASSEMBLY_VERSION)

        #error "SSE2_VERSION not implemented!"

    #endif

}
