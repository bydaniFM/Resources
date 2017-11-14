
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2015                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
 *  Para ejecutar el programa la librería de enlace dinámico de SDL (SDL2.dll  *
 *  en Windows) debe estar disponible en alguna de las rutas en las que el     *
 *  sistema operativo espera encontrarla.                                      *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <SDL.h>
#include <ciso646>

int main (int , char ** )
{
    // Se hace inicializa SDL:

    if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
        SDL_Log ("No se ha podido inicializar SDL2.");
    }
    else
    {
        // Se crea una ventana:

        SDL_Window * window = SDL_CreateWindow ("SDL Basic Input Sample", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

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
                bool exit = false;

                // Se rellena el fondo de la ventana de color gris:

                SDL_FillRect (surface, 0, SDL_MapRGB (surface->format, 225, 225, 225));

                do
                {
                    // Se procesan los eventos acumulados:

                    SDL_Event event;

                    while (SDL_PollEvent (&event) > 0)
                    {
                        switch (event.type)
                        {
                            case SDL_KEYDOWN:
                            {
                                // Si se pulsan ciertas teclas se borra el contenido de la ventana:

                                switch (event.key.keysym.sym)
                                {
                                    case SDLK_SPACE:
                                    case SDLK_ESCAPE:
                                    case SDLK_RETURN:
                                    case SDLK_KP_ENTER:
                                    {
                                        SDL_FillRect (surface, 0, SDL_MapRGB (surface->format, 225, 225, 225));
                                    }
                                }

                                break;
                            }

                            case SDL_MOUSEBUTTONDOWN:
                            case SDL_MOUSEMOTION:
                            {
                                // Si se mueve el ratón mientras se mantiene presionado alguno de sus tres
                                // botones principales se dibuja un pequeño rectángulo de color:

                                int mouse_x = 0, mouse_y = 0;

                                uint32_t buttons = SDL_GetMouseState (&mouse_x, &mouse_y);

                                uint8_t  left    = buttons & SDL_BUTTON(SDL_BUTTON_LEFT  ) ? 255 : 0;
                                uint8_t  middle  = buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE) ? 255 : 0;
                                uint8_t  right   = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT ) ? 255 : 0;

                                if (left || middle || right)
                                {
                                    SDL_Rect cursor_area = { mouse_x - 1, mouse_y - 1, 3, 3 };

                                    SDL_FillRect (surface, &cursor_area, SDL_MapRGB (surface->format, left, middle, right));
                                }

                                break;
                            }

                            case SDL_QUIT:
                            {
                                exit = true;
                                break;
                            }
                        }
                    }

                    SDL_UpdateWindowSurface (window);
                }
                while (!exit);
            }

            SDL_DestroyWindow (window);
        }

        SDL_Quit ();
    }

    return 0;
}
