#ifndef TAB_H
#define TAB_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include <list>

#include <Tab_Rect.h>

#include <Wrapper.h>
#include <EventHandler.h>

namespace UI
{
    class Tab
    {
        private:
            std::list<UI::Tab_Rect> tabs;

            int Curr;

            sf::Vector2f Pos;

            sf::Vector2f LPos;

            EventData* Event;

        public:
            Tab(){ ; }
            Tab(sf::Vector2f Pos, UI::EventData& ev);

            /** Takes In Name of New Tab and Returns Id of New TAb **/
            int Add_New_Tab(std::string Name);

            int Draw(sf::RenderWindow& win);

            ~Tab();
    };
}

#endif // TAB_H
