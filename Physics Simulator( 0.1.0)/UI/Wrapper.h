#pragma once

#ifndef WRAPPER_H
#define WRAPPER_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include <Font.h>
#include <InputStream.h>

namespace UI
{
    class Init
    {
    public:
        Init()
        {
            Static_Font.Load(UI::Fonts::Consolas_R);
        }

        static UI::Font Static_Font;
    };

    class Graphics
    {
        public:
            Graphics(){ ; }

            static void Update()
            {
                Console.__Update_Stream();
            }

            ~Graphics(){ ; }

            static UI::InputStream Console;
    };
}

#endif // WRAPPER_H
