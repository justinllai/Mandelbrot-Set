#include "ComplexPlane.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
    //get desktop resoltion
    int screenW = VideoMode::getDesktopMode().width / 2;
    int screenH = VideoMode::getDesktopMode().height / 2;

    RenderWindow window(VideoMode(screenW, screenH), "Mandelbrot Set");

    ComplexPlane ComplexPlane(screenW, screenH);

    Font font;

    if (!font.loadFromFile("arial.ttf"))
    {
        return -1;
    }
    
    Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::Red);

#include "ComplexPlane.h"
#include <iostream>
#include <SFML/Graphics.hpp>

    using namespace std;
    using namespace sf;

    int main()
    {
        //get desktop resolution
        int screenW = VideoMode::getDesktopMode().width / 2;
        int screenH = VideoMode::getDesktopMode().height / 2;

        RenderWindow window(VideoMode(screenW, screenH), "Mandelbrot Set");

        ComplexPlane ComplexPlane(screenW, screenH);

        Font font;

        if (!font.loadFromFile("arial.ttf"))
        {
            return -1;
        }


        Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(Color::Red);
        text.setPosition(10.f, 10.0f);

        while (window.isOpen())
        {

            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {

                    window.close();
                }
                if (event.type == Event::MouseButtonPressed)
                {
                    Vector2i mousePixel = Mouse::getPosition(window);

                    if (event.mouseButton.button == Mouse::Left)
                    {
                        complexPlane.zoomIn();
                        complexPlane.setCenter(mousePixel);
                    }
                    if (event.mouseButton.button == Mouse::Right)
                    {
                        complexPlane.zoomOut();
                        complexPlane.setCenter(mousePixel);
                    }
                }
                if (event.type == Event::MouseMoved)
                {
                    Vector2i mousePixel = Mouse::getPosition(window);
                    complexPlane.setMouseLocation(mousePixel);
                }
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    window.close();
                }
            }
        

            complexPlane.updateRender();
            complexPlane.loadText(text);

            window.clear();

            window.draw(complexPlane);
            window.draw(text);

            window.display();
        }

        return 0;



    }

