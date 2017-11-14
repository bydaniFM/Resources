
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on december of 2013                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <cmath>
#include <cassert>
#include "View.hpp"
#include <Vector.hpp>
#include <Scaling.hpp>
#include <Rotation.hpp>
#include <Projection.hpp>
#include <Translation.hpp>

using namespace toolkit;

namespace example
{

    View::View(size_t width, size_t height)
    :
        width       (width ),
        height      (height),
        Color_buffer(width, height),
        rasterizer  (Color_buffer )
    {
        // Se definen los datos de los vértices:

        static const int vertices[][4] =
        {
            { -1, -1, +1, 1 },      // 0
            { +1, -1, +1, 1 },      // 1
            { +1, +1, +1, 1 },      // 2
            { -1, +1, +1, 1 },      // 3
            { -1, -1, -1, 1 },      // 4
            { +1, -1, -1, 1 },      // 5
            { +1, +1, -1, 1 },      // 6
            { -1, +1, -1, 1 },      // 7
        };

        // Se cargan en un búffer los datos del array:

        size_t number_of_vertices = sizeof(vertices) / sizeof(int) / 4;

        original_vertices.resize (number_of_vertices);

        for (size_t index = 0; index < number_of_vertices; index++)
        {
            original_vertices[index] = Vertex(vertices[index]);
        }

        transformed_vertices.resize (number_of_vertices);
            display_vertices.resize (number_of_vertices);

        // Se definen los datos de color de los vértices:

        static const int colors[][3] =
        {
            { 255,   0,   0 },      // 0
            {   0, 255,   0 },      // 1
            {   0,   0, 255 },      // 2
            {   0,   0, 255 },      // 3
            { 255, 255,   0 },      // 4
            { 255,   0, 255 },      // 5
            { 255,   0,   0 },      // 6
            { 255,   0,   0 },      // 7
        };

        size_t number_of_colors = sizeof(colors) / sizeof(int) / 3;

        assert(number_of_colors == number_of_vertices);             // Debe haber el mismo número
                                                                    // de colores que de vértices
        original_colors.resize (number_of_colors);

        for (size_t index = 0; index < number_of_colors; index++)
        {
            original_colors[index].set (colors[index][0], colors[index][1], colors[index][2]);
        }

        // Se generan los índices de los triángulos:

        static const int triangles[][3] =
        {
            { 0, 1, 2 },        // front
            { 0, 2, 3 },
            { 4, 0, 3 },        // left
            { 4, 3, 7 },
            { 5, 4, 7 },        // back
            { 5, 7, 6 },
            { 1, 5, 6 },        // right
            { 1, 6, 2 },
            { 3, 2, 6 },        // top
            { 3, 6, 7 },
            { 0, 4, 5 },        // bottom
            { 0, 5, 1 },
        };

        size_t number_of_triangles = sizeof(triangles) / sizeof(int) / 3;

        original_indices.resize (number_of_triangles * 3);

        Index_Buffer::iterator indices_iterator = original_indices.begin ();

        for (size_t triangle_index = 0; triangle_index < number_of_triangles; triangle_index++)
        {
            *indices_iterator++ = triangles[triangle_index][0];
            *indices_iterator++ = triangles[triangle_index][1];
            *indices_iterator++ = triangles[triangle_index][2];
        }
    }

    void View::update ()
    {
        // Se actualizan los parámetros de transformatión (sólo se modifica el ángulo):

        static float angle = 0.1f;

        angle += 0.01f;

        // Se crean las matrices de transformación:

        Rotation3f    rotation_x;
        Rotation3f    rotation_y;
        Translation3f translation (0, 0, -10);
        Projection3f  projection  (5, 15, 20, float(width) / float(height));

        rotation_x.set< Rotation3f::AROUND_THE_X_AXIS > (0.50f);
        rotation_y.set< Rotation3f::AROUND_THE_Y_AXIS > (angle);

        // Creación de la matriz de transformación unificada:

        // 0. Se parte de un cubo, con aristas de una unidad de longitud, centrado en (0,0)
        // 1. Se rota sobre sí mismo en el eje Y (todavía está en (0,0))
        // 2. Se rota sobre sí mismo en el eje X para que se vea un poco de canto (todavía está en (0,0))
        // 3. Se aleja hacia el fondo 10 unidades
        // 4. Se proyecta con perspectiva
        //                                4:           3:            2:           1:
        Transformation3f transformation = projection * translation * rotation_x * rotation_y;

        // Se transforman todos los vértices usando la matriz de transformación resultante:

        for (size_t index = 0, number_of_vertices = original_vertices.size (); index < number_of_vertices; index++)
        {
            // Se multiplican todos los vértices originales con la matriz de transformación y
            // se guarda el resultado en otro vertex buffer:

            Vertex & vertex = transformed_vertices[index] = Matrix44f(transformation) * Matrix41f(original_vertices[index]);

            // La matriz de proyección en perspectiva hace que el último componente del vector
            // transformado no tenga valor 1.0, por lo que hay que normalizarlo dividiendo:

            float divisor = 1.f / vertex[3];

            vertex[0] *= divisor;
            vertex[1] *= divisor;
            vertex[2] *= divisor;
            vertex[3]  = 1.f;
        }
    }

    void View::paint ()
    {
        // Se convierten las coordenadas transformadas y proyectadas a coordenadas
        // de recorte (-1 a +1) en coordenadas de pantalla con el origen centrado:

        size_t number_of_vertices = transformed_vertices.size ();

        Scaling3f        scaling        = Scaling3f    (float(width / 2), float(height / 2), 1.f);
        Translation3f    translation    = Translation3f(float(width / 2), float(height / 2), 0.f);
        Transformation3f transformation = translation * scaling;

        for (size_t index = 0; index < number_of_vertices; index++)
        {
            display_vertices[index] = Point4i( Matrix44f(transformation) * Matrix41f(transformed_vertices[index]) );
        }

        // Se borra el framebúffer y se dibujan los triángulos:

        rasterizer.clear ();

        for (int * indices = original_indices.data (), * end = indices + original_indices.size (); indices < end; indices += 3)
        {
            if (is_frontface (transformed_vertices.data (), indices))
            {
                // Se establece el color del polígono a partir del color de su primer vértice:

                rasterizer.set_color (original_colors[*indices]);

                // Se rellena el polígono:

                rasterizer.fill_convex_polygon (display_vertices.data (), indices, indices + 3);
            }
        }

        // Se copia el framebúffer oculto en el framebúffer de la ventana:

        rasterizer.get_color_buffer ().gl_draw_pixels (0, 0);
    }

    bool View::is_frontface (const Vertex * const projected_vertices, const int * const indices)
    {
        const Vertex & v0 = projected_vertices[indices[0]];
        const Vertex & v1 = projected_vertices[indices[1]];
        const Vertex & v2 = projected_vertices[indices[2]];

        // Se asumen coordenadas proyectadas y polígonos definidos en sentido horario.
        // Se comprueba a qué lado de la línea que pasa por v0 y v1 queda el punto v2:

        return ((v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]) > 0.f);
    }

}
