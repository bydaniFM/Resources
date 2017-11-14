/*
Autor: Daniel Fernandez
Date: 24/10/2017
*/

#pragma once

#include <SDL.h>

namespace engine_name
{

	class Window
	{
	public:

		enum Flag {
			SHOWN = SDL_WINDOW_SHOWN,
			FULLSCREEN = SDL_WINDOW_FULLSCREEN,
			BORDERLESS = SDL_WINDOW_BORDERLESS
		};

	private:

		SDL_Window * window;

	public:

		Window(const std::string & title, int width, int height)
		{
			window = SDL_CreateWindow
			(
				title.c_str(),
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				width,
				height,
				SDL_WINDOW_SHOWN
			);
		}

		~Window()
		{
			SDL_DestroyWindow(window);
		}

	};

}