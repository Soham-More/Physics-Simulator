#ifndef TAB_RECT_H
#define TAB_RECT_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include <Wrapper.h>
#include <EventHandler.h>

namespace UI
{
    class Tab_Rect
    {
        private:
            sf::RectangleShape Box;
            bool isClicked;

            sf::Font f;
            sf::Text Txt;

            EventData* Event;

            sf::Vector2f Sz;
        public:
            Tab_Rect() : isClicked(false){ ; }
            Tab_Rect(sf::Vector2f Pos, std::string Text, UI::EventData& ev);

            void Create(sf::Vector2f Pos, std::string Text, UI::EventData& ev);

            bool Draw(sf::RenderWindow& win);

            sf::Vector2f Get_Size() { return Sz; }

            ~Tab_Rect();
    };
}

#endif // TAB_RECT_H
