#ifndef SLIDER_H
#define SLIDER_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include <EventHandler.h>
#include <Wrapper.h>
#include <DataTypes.h>

namespace UI
{
    class Slider
    {
        private:
            static int Count;

            sf::RectangleShape Knob;
            sf::RectangleShape Holder;

            sf::Text Min_Text;
            sf::Text Max_Text;

            sf::RectangleShape ValueBox;
            sf::Text Value_Txt;

            UI::EventData* Event;

            float Min = 0;
            float Max = 100;

            float Min_X = 0;
            float Max_X = 100;

            bool isClicked;

            sf::Vector2f Pos;

            bool PointInRect(sf::RectangleShape& r, sf::Vector2f p);
            std::string float_to_string(float a);
        public:
            Slider() : isClicked(false){ ; }
            Slider(sf::Vector2f Pos, float Size, UI::EventData& e, sf::Color Knob_Color);
            void Create(sf::Vector2f Pos, float Size, UI::EventData& e, sf::Color Knob_Color);

            void Set_Limits(float Min, float Max, float Init_Val = 0);

            void Draw(sf::RenderWindow& win, bool ShowLimits = false);

            ~Slider();

            /// Value of This Slider
            float Value = 0;
    };
}

#endif // SLIDER_H
