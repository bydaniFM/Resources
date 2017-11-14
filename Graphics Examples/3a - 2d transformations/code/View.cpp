
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
#include <Translation.hpp>

using namespace toolkit;

namespace example
{

    View::View(size_t width, size_t height)
    :
        width       (width ),
        height      (height),
        color_buffer(width, height),
        rasterizer  (color_buffer )
    {
        // Se definen los datos de los vértices:

        static const int vertices[][3] =
        {
            {   45, -200, 1 },
            {  200,  -60, 1 },
            {  150,  140, 1 },
            {  -45,  200, 1 },
            { -200,   60, 1 },
            { -150, -140, 1 },
        };

        // Se cargan en un búffer los datos del array:

        size_t number_of_vertices =  sizeof(vertices) / sizeof(int) / 3;

        original_vertices.resize (number_of_vertices);

        for (size_t index = 0; index < number_of_vertices; index++)
        {
            original_vertices[index] = Vertex(vertices[index]);
        }

        // Se generan los índices del polígono (linealmente desde 0 hasta N-1):

        transformed_vertices.resize (number_of_vertices);

        indices.resize (number_of_vertices);

        for (size_t index = 0; index < number_of_vertices; index++)
        {
            indices[index] = index;
        }
    }

    void View::update ()
    {
        // Se actualizan los parámetros de transformatión (sólo se modifica el ángulo):

        static float angle = 0.1f;

        angle += 0.005f;

        // Se crean las matrices de transformación:

        Scaling2f     scaling      (0.5f);
        Rotation2f    rotation1    (angle * -5.f);
        Rotation2f    rotation2    (angle);
        Translation2f translation1 (150,   0);
        Translation2f translation2 (400, 300);

        // Creación de la matriz de transformación unificada:

        // 0. Se parte de un hexágono centrado en (0,0)
        // 1. Se escala a la mitad (0.5)
        // 2. Se rota sobre sí mismo (todavía está en (0,0))
        // 3. Se separa el hexágono del centro 150 unidades hacia la derecha (150,0)
        // 4. Se rota el hexágono alrededor de  (0,0) (no estando en el centro ya)
        // 5. Se mueve el centro de coordenadas (0,0) al centro de la ventana (800/2,600/2)

        //                                5:             4:          3:             2:          1:
        Transformation2f transformation = translation2 * rotation2 * translation1 * rotation1 * scaling;

        // Se multiplican todos los vértices originales con la matriz de transformación y
        // se guarda el resultado en otro vertex buffer:

        for (int index = 0, number_of_vertices = original_vertices.size (); index < number_of_vertices; index++)
        {
            transformed_vertices[index] = Matrix33f(transformation) * Matrix31f(original_vertices[index]);
        }
    }

    void View::paint ()
    {
        // Como la función de relleno de polígonos no acepta como entrada vértices con tres
        // coordenadas en coma flotante, hay que transformarlos a vértices con dos coordenadas
        // enteras que sí acepta.

        int number_of_vertices = transformed_vertices.size ();

        std::vector< Point2i > rounded_vertices(number_of_vertices);

        for (int index = 0; index < number_of_vertices; index++)
        {
            Point2i & rounded_vertex     = rounded_vertices    [index];
            Point3f & transformed_vertex = transformed_vertices[index];

            rounded_vertex.coordinates ()[0] = int( std::floorf (transformed_vertex.coordinates ()[0] + 0.5f) );
            rounded_vertex.coordinates ()[1] = int( std::floorf (transformed_vertex.coordinates ()[1] + 0.5f) );
        }

        // Se borra el framebúffer y se dibuja el polígono transformado:

        rasterizer.clear ();
        rasterizer.set_color (0, 0, 255);
        rasterizer.fill_convex_polygon (rounded_vertices.data (), indices.data (), indices.data () + number_of_vertices);

        // Se copia el framebúffer oculto en el framebúffer de la ventana:

        rasterizer.get_color_buffer ().gl_draw_pixels (0, 0);
    }

}
