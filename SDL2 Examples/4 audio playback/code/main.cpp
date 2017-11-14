
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2015                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
 *  Para ejecutar el programa la librería de enlace dinámico de SDL (SDL2.dll  *
 *  en Windows), la de SDL Mixer (SDL2_mixer.dll) y las de OGG-Vorbis          *
 *  (libogg-0.dll, libvorbis-0.dll y libvorbisfile-3.dll) deben estar          *
 *  disponibles en alguna de las rutas en las que el sistema operativo espera  *
 *  encontrarlas.                                                              *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <SDL.h>
#include <ciso646>
#include <SDL_mixer.h>

int main (int , char ** )
{
    // Se hace inicializa SDL:

    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        SDL_Log ("No se ha podido inicializar SDL2.");
    }
    else
    {
        if (Mix_OpenAudio (22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
        {
            SDL_Log ("No se ha podido inicializar el subsistema de audio.");
        }
        else
        {
            // Se crea una ventana:

            SDL_Window * window = SDL_CreateWindow ("Audio Playback Sample", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

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
                    // Se intenta cargar un sonido y una música:

                    Mix_Music * music = nullptr;
                    Mix_Chunk * sound = nullptr;

                    if
                    (
                        not (music = Mix_LoadMUS ("../../../assets/sounds/rainforest-ambience.ogg")) ||
                        not (sound = Mix_LoadWAV ("../../../assets/sounds/throw-knife.wav"))
                    )
                    {
                        SDL_Log ("No se ha podido cargar el audio.");
                    }
                    else
                    {
                        // Se inicia la reproducción de la música en bucle con un fundido:

                        Mix_FadeInMusic (music, -1, 4000);

                        bool exit = false;

                        do
                        {
                            // Se procesan los eventos acumulados:

                            SDL_Event event;

                            while (SDL_PollEvent (&event) > 0)
                            {
                                switch (event.type)
                                {
                                    case SDL_MOUSEBUTTONDOWN:
                                    {                                       // Cuando se hace click con algún botón del ratón
                                        Mix_PlayChannel (-1, sound, 0);     // se reproduce un sonido en un canal libre
                                        break;
                                    }

                                    case SDL_QUIT:
                                    {
                                        exit = true;
                                        break;
                                    }
                                }
                            }

                            // Se rellena el fondo de la ventana de un color color que depende de
                            // si se está reproduciendo algún sonido o no:

                            SDL_FillRect (surface, 0, SDL_MapRGB (surface->format, 225, Mix_Playing (-1) ? 200 : 225, 200));

                            SDL_UpdateWindowSurface (window);
                        }
                        while (!exit);

                        Mix_HaltMusic   ();
                        Mix_HaltChannel (-1);
                    }

                    if (music) Mix_FreeMusic (music);
                    if (sound) Mix_FreeChunk (sound);
                }

                SDL_DestroyWindow (window);
            }

            Mix_CloseAudio ();
        }

        SDL_Quit ();
    }

    return 0;
}
