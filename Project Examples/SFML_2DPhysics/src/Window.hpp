
#pragma once

#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace physics2D
{

	class Window
	{
	public:

		RenderWindow * window;

		Window(int width, int height, std::string title)
		{
			window = new RenderWindow(VideoMode(width, height), title, Style::Titlebar | Style::Close, ContextSettings(32));
			window->setVerticalSyncEnabled(true);
		}

	};
}