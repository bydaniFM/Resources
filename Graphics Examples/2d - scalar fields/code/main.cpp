
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2016                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <string>
#include "View.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

using sf::Font;
using sf::Text;
using sf::Clock;
using sf::Event;
using sf::VideoMode;
using sf::RenderWindow;

using namespace example;
using namespace sf::Style;

int main ()
{
    static const size_t window_width  = 1024;
    static const size_t window_height =  768;

    // Create the window and the view that will be shown within the window:

    RenderWindow window(VideoMode(window_width, window_height), "Scalar fields", Titlebar | Close, sf::ContextSettings(32));
    View         view  (window_width, window_height);

    // Prepare the fps text object:

    Font font;
    Text text;

    font.loadFromFile     ("../../assets/saxmono.ttf");
    text.setFont          (font);
    text.setCharacterSize (16);
    text.setColor         (sf::Color::Blue);
    text.setPosition      (sf::Vector2f(12.f, 10.f));

    // Run the main loop:

    Clock timer;

    float fps     = 0.0f;
    bool  running = true;

    do
    {
        timer.restart ();

        // Attend the window events:

        Event event;

        while (window.pollEvent (event))
        {
            if (event.type == Event::Closed)
            {
                running = false;
            }
        }

        // Update the view:

        view.update ();

        // Repaint the view:

        view.render ();

        // Draw the fps text:

        if (fps > 0.f)
        {
            text.setString (std::to_string (fps));

            window.pushGLStates ();
            window.draw (text);
            window.popGLStates ();
        }

        // Swap the OpenGL buffers:

        window.display ();

        // Calculate the current fps:

        fps = 1.f / timer.getElapsedTime ().asSeconds ();
    }
    while (running);

    // Close the application:

    return (EXIT_SUCCESS);
}
