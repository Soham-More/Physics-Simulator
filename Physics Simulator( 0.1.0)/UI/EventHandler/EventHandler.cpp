#include "EventHandler.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include <cctype>

using namespace UI;

EventHandler::EventHandler()
{
    App_Event.Init();
}

EventHandler::~EventHandler()
{
    //dtor
}

void EventHandler::handleEvents(sf::RenderWindow& win)
{
    win.setActive();

    sf::Event Win_Event;
    while(win.pollEvent(Win_Event))
    {
        switch(Win_Event.type)
        {
        case sf::Event::Closed:
            App_Event.WindowState.Closed = true;
            break;
        case sf::Event::GainedFocus:
            App_Event.WindowState.isFocused = true;
            break;
        case sf::Event::LostFocus:
            App_Event.WindowState.isFocused = false;
            break;
        case sf::Event::TextEntered:
            App_Event.KeyboardState.Text = static_cast<char>(Win_Event.text.unicode);
            break;
        case sf::Event::KeyPressed:

            if((isalpha(char(Win_Event.key.code + 65)) && isupper(char(Win_Event.key.code + 65))) || isdigit(char(Win_Event.key.code + 22)) || (Win_Event.key.code == sf::Keyboard::Period) || (Win_Event.key.code == sf::Keyboard::Hyphen) || (Win_Event.key.code == sf::Keyboard::Space))
            {
                if(char(Win_Event.key.code + 65) == Prev_Key)
                {
                    if(Key_Clock.getElapsedTime().asSeconds() >= 0.5f)
                    {
                        if(isalpha(char(Win_Event.key.code + 65)))
                        {
                            App_Event.KeyboardState.Key = char(Win_Event.key.code + 65);
                        }
                        if(isdigit(char(Win_Event.key.code + 22)))
                        {
                            App_Event.KeyboardState.Key = char(Win_Event.key.code + 22);
                        }
                        if(Win_Event.key.code == sf::Keyboard::Period)
                        {
                            App_Event.KeyboardState.Key = '.';
                        }
                        if(Win_Event.key.code == sf::Keyboard::Hyphen)
                        {
                            App_Event.KeyboardState.Key = '-';
                        }
                        if(Win_Event.key.code == sf::Keyboard::Space)
                        {
                            App_Event.KeyboardState.Key = ' ';
                        }
                        Prev_Key = App_Event.KeyboardState.Key;
                        Key_Clock.restart();
                    }
                }
                else
                {
                    if(isalpha(char(Win_Event.key.code + 65)))
                    {
                        App_Event.KeyboardState.Key = char(Win_Event.key.code + 65);
                    }
                    if(isdigit(char(Win_Event.key.code + 22)))
                    {
                        App_Event.KeyboardState.Key = char(Win_Event.key.code + 22);
                    }
                    if(Win_Event.key.code == sf::Keyboard::Period)
                    {
                        App_Event.KeyboardState.Key = '.';
                    }
                    if(Win_Event.key.code == sf::Keyboard::Hyphen)
                    {
                        App_Event.KeyboardState.Key = '-';
                    }
                    if(Win_Event.key.code == sf::Keyboard::Space)
                    {
                        App_Event.KeyboardState.Key = ' ';
                    }
                    Prev_Key = App_Event.KeyboardState.Key;
                    Key_Clock.restart();
                }
            }

            break;

        case sf::Event::Resized:
            App_Event.WindowState.Size.x = Win_Event.size.width;
            App_Event.WindowState.Size.y = Win_Event.size.height;
            break;
        case sf::Event::MouseButtonPressed:
            break;
        case sf::Event::MouseMoved:
            break;
        default:
            App_Event.Init();
            break;
        }
    }

    if(!App_Event.MouseState.DragMode && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        App_Event.MouseState.Time.restart();
        App_Event.MouseState.DragMode = true;
    }
    else if(App_Event.MouseState.DragMode)
    {
        if(App_Event.MouseState.Time.getElapsedTime().asSeconds() > 0.25f)
        {
            App_Event.MouseState.Dragged = true;
        }
    }

    App_Event.MouseState.LeftClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    App_Event.MouseState.RightClick = sf::Mouse::isButtonPressed(sf::Mouse::Right);

    sf::Vector2f m = win.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y));

    App_Event.MouseState.MousePos = sf::Vector2f(m.x, m.y);
}

void EventHandler::ignoreEvents(sf::RenderWindow& win)
{
    sf::Event Win_Event;
    while(win.pollEvent(Win_Event))
    {
        switch(Win_Event.type)
        {
        case sf::Event::Closed:
            App_Event.WindowState.Closed = true;
            break;
        case sf::Event::TextEntered:
            break;
        case sf::Event::KeyPressed:
            break;
        case sf::Event::Resized:
            App_Event.WindowState.Size.x = Win_Event.size.width;
            App_Event.WindowState.Size.y = Win_Event.size.height;
            break;
        case sf::Event::MouseButtonPressed:
            break;
        case sf::Event::MouseMoved:
            break;
        default:
            break;
        }
    }
}
