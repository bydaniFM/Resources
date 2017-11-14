
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

        rotation_x.set< Rotation3f::AROUND_THE_X_AXIS > (0.5);
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

        for (int index = 0, number_of_vertices = original_vertices.size (); index < number_of_vertices; index++)
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

        int number_of_vertices = transformed_vertices.size ();

        std::vector< Point2i > rounded_vertices(number_of_vertices);

        for (int index = 0; index < number_of_vertices; index++)
        {
            Point2i & rounded_vertex     = rounded_vertices    [index];
            Point4f & transformed_vertex = transformed_vertices[index];

            rounded_vertex.coordinates ()[0] = int( std::floorf (transformed_vertex.coordinates ()[0] * width  / 2 + 0.5f) ) + width  / 2;
            rounded_vertex.coordinates ()[1] = int( std::floorf (transformed_vertex.coordinates ()[1] * height / 2 + 0.5f) ) + height / 2;
        }

        // Se borra el framebúffer y se dibujan los triángulos:

        rasterizer.clear ();
        rasterizer.set_color (0, 0, 255);

        for (int index = 0, number_of_indices = original_indices.size (); index < number_of_indices; )
        {
            Point2i & rounded_vertex_0 = rounded_vertices[original_indices[index++]];
            Point2i & rounded_vertex_1 = rounded_vertices[original_indices[index++]];
            Point2i & rounded_vertex_2 = rounded_vertices[original_indices[index++]];

            rasterizer.draw_triangle
            (
                rounded_vertex_0.coordinates ()[0], rounded_vertex_0.coordinates ()[1],
                rounded_vertex_1.coordinates ()[0], rounded_vertex_1.coordinates ()[1],
                rounded_vertex_2.coordinates ()[0], rounded_vertex_2.coordinates ()[1]
            );
        }

        // Se copia el framebúffer oculto en el framebúffer de la ventana:

        rasterizer.get_color_buffer ().gl_draw_pixels (0, 0);
    }

}
