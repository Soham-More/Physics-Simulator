#ifndef SWITCH_H
#define SWITCH_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include <EventHandler.h>
#include <Wrapper.h>

/// This Header Is Not Implemented
namespace UI
{
    class Switch
    {
        private:
            sf::RectangleShape Switch_Rect;
            sf::RectangleShape Switcher;

            sf::Text Txt_Off;
            sf::Text Txt_On;

            bool Animation = false;
        public:
            Switch(){ ; }
            Switch(sf::Vector2f Pos, sf::Color Switch_Color = sf::Color::White);

            void Create(sf::Vector2f Pos, sf::Color Switch_Color = sf::Color::White);

            void Draw(sf::RenderWindow& win, float DeltaTime){}

            ~Switch();

            bool Value = false;
    };
}

#endif // SWITCH_H
