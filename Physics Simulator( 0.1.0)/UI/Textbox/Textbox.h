#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include <InputStream.h>
#include <Wrapper.h>

namespace UI
{
    struct TextBox_Style
    {
        bool isCentered = false;

        sf::Color Selected_Color = sf::Color::White;
        sf::Color Default_Color = sf::Color::White;

        bool Bold_Text = false;
        sf::Color Text_Color = sf::Color::Black;

        sf::Vector2f Scale;

        TextBox_Style()
        {
            Scale = sf::Vector2f(1.0f, 1.0f);
        }
    };

    class Textbox
    {
        private:
            sf::RectangleShape Box;
            sf::RectangleShape line;

            std::string Text;
            sf::Text txt;

            TextBox_Style TextBoxStyle;

            bool isClicked = false;
            bool isValueChanged = false;

            // Numbers
            bool OnlyN = false; // Allow Only Numbers

            bool isDotPresent = false;
            bool isNegative = false;

            bool PointInRect(sf::RectangleShape& r, sf::Vector2f p);

            // Cursor Parameters : BackSpace
            float W_t_bs = 0.25f;
            bool Backspaced = false;

            sf::Clock bs_clk;

            // Cursor Parameters : Movement
            float W_t_ML = 0.25f;
            float W_t_MR = 0.25f;

            bool LMoved = false;
            bool RMoved = false;

            sf::Clock lm_clk;
            sf::Clock rm_clk;

            // Cursor Parameters : Position
            int Position = 0;

            bool DClick = false;

            // Cursor Parameters : Blink
            bool Show = true;

            sf::Clock blk;

            // Event Data
            EventData* Event;

            /// Get Position Of Cursor In Text
            int GetCursorPosition();

        public:
            Textbox(){ ; }
            Textbox(sf::Vector2f Pos, int Sz, EventData& Event, const std::string& InitText = "", bool OnlyNum = false);

            void Create(sf::Vector2f Pos, int Sz, EventData& Event, const std::string& InitText = "", bool OnlyNum = false);
            void SetStyle(TextBox_Style& ts);

            void Update();

            void Draw(sf::RenderWindow& win);

            bool isActive(){ return isClicked; }
            std::string GetInput(){ isValueChanged = false; return Text; }
            void resetValue(std::string val);

            ~Textbox();
    };
}

#endif // TEXTBOX_H
