#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

namespace UI
{
    struct WindowData
    {
        sf::Vector2f Size;
        bool Closed;
        bool isFocused = false;

        void Init()
        {
            Closed = false;
        }
    };

    struct KeyboardData
    {
        enum ArrowName{ NONE = 0, UP, DOWN, RIGHT, LEFT };

        char Text;
        char Key;
        unsigned int ArrowKey;

        void Init()
        {
            Key = '\0';
            ArrowKey = NONE;
        }

    };

    struct MouseData
    {
        sf::Vector2f MousePos;
        bool LeftClick;
        bool Dragged;
        bool RightClick;
        int Scroll = 0;

        sf::Clock Time;
        bool DragMode;

        void Init()
        {
            LeftClick = false;
            RightClick = false;
            Dragged = false;
            DragMode = false;
            Time.restart();
        }
    };

    class EventData
    {
    public:
        EventData(){ ; }

        void Init()
        {
            KeyboardState.Init();
            MouseState.Init();
            WindowState.Init();
        }

        ~EventData(){ ; }

        KeyboardData KeyboardState;
        MouseData MouseState;
        WindowData WindowState;

    };

    class EventHandler
    {
        private:
            char Prev_Key;
            sf::Clock Key_Clock;

        public:
            EventHandler();

            void handleEvents(sf::RenderWindow& win);

            void ignoreEvents(sf::RenderWindow& win);

            ~EventHandler();

            EventData App_Event;
    };
}

#endif // EVENTHANDLER_H
