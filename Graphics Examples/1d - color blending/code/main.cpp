
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on october of 2013                                        *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "View.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>
using namespace std;

using namespace sf;
using namespace example;

static const size_t window_width  = 800;
static const size_t window_height = 600;

int main (int number_of_arguments, char * arguments[])
{
    // Create the window and the view that will be shown within the window:

    Window window(VideoMode(window_width, window_height), "Color Blending", Style::Titlebar | Style::Close, ContextSettings(32));
    View   view  (window_width, window_height, number_of_arguments == 2 ? arguments[1] : 0);

    // Initialization:

    window.setVerticalSyncEnabled (true);

    // Run the main loop:

    bool running = true;

    do
    {
        // Attend the window events:

        Event event;

        while (window.pollEvent (event))
        {
            if (event.type == Event::Closed)
            {
                running = false;
            }
        }

        // Repaint the view:

        view.paint ();

        // Swap the OpenGL buffers:

        window.display ();
    }
    while (running);

    // Close the application:

    return (EXIT_SUCCESS);
}
