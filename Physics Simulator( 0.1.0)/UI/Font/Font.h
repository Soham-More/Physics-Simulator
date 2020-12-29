#ifndef FONT_H
#define FONT_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include <ErrorStream.h>

namespace UI
{
    namespace Fonts
    {
        const std::string Consolas_R = "Fonts/consola.ttf";
        const std::string Greek_R = "Fonts/Greek Symbols Regular.ttf";
    }

    class Font
    {
        private:
            sf::Font font;
        public:
            Font();

            void Load(const std::string& FontPath);
            sf::Font& GetFont();

            ~Font();
    };
}

#endif // FONT_H
