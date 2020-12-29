#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include <Wrapper.h>
#include <EventHandler.h>

#include <Font.h>

namespace UI
{
    class Button
    {
        private:
            sf::RectangleShape Box;
            bool isClicked;

            sf::Vector2f ButtonPos;
            sf::Vector2f ButtonSize;
            bool isReversed = false;

            sf::Font f;
            sf::Text Txt;

            sf::Texture tex1;
            sf::Texture tex2;

            sf::Shader sh;
            sf::Shader sh1;

            EventData* Event;
        public:
            Button();
            Button(sf::Vector2f Pos, sf::Vector2f Size, std::string Text, EventData& Event, sf::Color color, bool Reverse = false);
            Button(sf::Vector2f Pos, sf::Vector2f Size, std::string Text, EventData& Event, const std::string& filename);

            void Create(sf::Vector2f Pos, sf::Vector2f Size, std::string Text, EventData& Event, sf::Color color, bool Reverse = false);
            void Create(sf::Vector2f Pos, sf::Vector2f Size, std::string Text, EventData& Event, const std::string& filename);

            void SetText(std::string title);

            bool Draw(sf::RenderWindow& win);

            ~Button();
    };
}

#endif // BUTTON_H
