
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2015                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
 *  Para ejecutar el programa la librería de enlace dinámico de SDL (SDL2.dll  *
 *  en Windows) y de SDL_ttf (SDL2_ttf.dll) y sus dependencias (zlib1.dll y    *
 *  libfreetype-6.dll) deben estar disponibles en alguna de las rutas en las   *
 *  que el sistema operativo espera encontrarlas.                              *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <SDL.h>
#include <ciso646>
#include <SDL_ttf.h>

int main (int number_of_arguments, char ** arguments)
{
    // Se comprueba que se está recibiendo un parámetro con la ruta de un archivo TTF:

    if (number_of_arguments != 2)
    {
        SDL_Log ("Se espera recibir un argumento que sea la ruta de un archivo TTF.");
        return -1;
    }

    // Se hace inicializa SDL:

    if (SDL_Init (SDL_INIT_VIDEO) < 0 || TTF_Init () < 0)
    {
        SDL_Log ("No se ha podido inicializar SDL2.");
    }
    else
    {
        // Se crea una ventana:

        const int window_width  = 800;
        const int window_height = 600;

        SDL_Window * window = SDL_CreateWindow
        (
           "SDL True Type Text Sample",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            window_width,
            window_height,
            SDL_WINDOW_SHOWN
        );

        if (not window)
        {
            SDL_Log ("No se ha podido crear una ventana.");
        }
        else
        {
            // Se toma el buffer de la ventana para dibujar en él:

            SDL_Surface * surface = SDL_GetWindowSurface (window);

            if (not surface)
            {
                SDL_Log ("No se ha podido acceder al buffer de la ventana.");
            }
            else
            {
                // Se intenta cargar el archivo TTF:

                TTF_Font * font = TTF_OpenFont (arguments[1], 64);

                if (not font)
                {
                    SDL_Log ("No se ha podido cargar el archivo TTF:");
                    SDL_Log (arguments[1]);
                }
                else
                {
                    // Se crea una superficie con el texto rasterizado:

                    SDL_Color     text_color   = { 0, 0, 255 };
                    SDL_Surface * text_surface = TTF_RenderText_Blended (font, "Hello, World!", text_color);

                    if (not text_surface)
                    {
                        SDL_Log ("Ha ocurrido algún error al intentar rasterizar texto.");
                    }
                    else
                    {
                        // Se rellena el fondo de la ventana de color gris:

                        SDL_Rect target_rect;

                        target_rect.w = text_surface->w;
                        target_rect.h = text_surface->h;
                        target_rect.x = window_width  / 2 - target_rect.w / 2;
                        target_rect.y = window_height / 2 - target_rect.h / 2;

                        SDL_FillRect    (surface, 0, SDL_MapRGB (surface->format, 225, 225, 225));
                        SDL_FillRect    (surface, &target_rect, SDL_MapRGB (surface->format, 245, 245, 245));
                        SDL_BlitSurface (text_surface, 0, surface, &target_rect);

                        bool exit = false;

                        do
                        {
                            // Se procesan los eventos acumulados:

                            SDL_Event event;

                            while (SDL_PollEvent (&event) > 0)
                            {
                                if (event.type == SDL_QUIT)
                                {
                                    exit = true;
                                }
                            }

                            SDL_UpdateWindowSurface (window);
                        }
                        while (!exit);

                        SDL_FreeSurface (text_surface);
                    }

                    TTF_CloseFont (font);
                }
            }

            SDL_DestroyWindow (window);
        }

        TTF_Quit ();
    }

    SDL_Quit ();

    return 0;
}
