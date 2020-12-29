#ifndef ERRORSTREAM_H
#define ERRORSTREAM_H

#include <iostream>
#include <windows.h>
#include <signal.h>
#include <SFML/Graphics.hpp>

#include <EventHandler.h>

#define KILL_PROGRAM true

namespace UI
{
    class ErrorStream
    {
        public:
            ErrorStream();

            static void NewError(std::string Error_Name, std::string Error_Discription, bool Kill_Program = false);

            ~ErrorStream();
    };
}

#endif // ERRORSTREAM_H
