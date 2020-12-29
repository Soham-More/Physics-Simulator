#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

#include <iostream>
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#include <EventHandler.h>
#include <DataTypes.h>

namespace UI
{
    class InputStream
    {
        private:
            std::string StringStream;

            unsigned int Stream_Limit;

            UI::EventData* e;

            bool Listen;

            void flush();
        public:
            InputStream() : Listen(false), Stream_Limit(10){ ; }

            InputStream(UI::EventData& e);

            void SetEventHandler(UI::EventData& e);

            UI::EventData* GetEventHandler(){ return e; }

            void SetLimit(int s_Limit);

            /// Start Listening Input.
            void ListenInput();

            /// Listens A Character From Keyboard and Returns.
            char Listen_Charecter();

            /// Finish Listening Input and return Whatever Was Listened from Keyboard.
            std::string GetString();

            void __Update_Stream();

            ~InputStream();
    };
}

#endif // INPUTSTREAM_H
