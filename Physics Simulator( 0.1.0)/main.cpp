#include <iostream>
#include <fstream>
#include <windows.h>

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <SFML/System.hpp>

#include <UI.hpp>
#include <OGL.hpp>
#include <Physics.hpp>

#include "Application.h"
#include <Object_Editor.h>
#include <UI_Window.h>

float PE::System_Properties::k = 10.0f;
float PE::System_Properties::G = 10.0f;
float PE::System_Properties::u = 10.0f;

int PE::Object_Properties::Count = -1;
int Object_Editor::mode = 0;

int main()
{
    std::fstream log_file;

    log_file.open("Error_Log.log", std::ios::out | std::ios::in);

    std::cerr.rdbuf(log_file.rdbuf());

    // Event Handler
    UI::EventHandler EventSystem;

    UI::ErrorStream::NewError("Small Tutorial",
                              "Use escape key to toggle mouse visibility.\n Use Arrow Keys to move.");

    Application app(EventSystem);

    UI::Init();
    OGL::Init();

    app.Init();

    int i = 1;

    sf::Clock clk;

    UI_Window ui;

    ui.SetApplication(app);

    UI::Graphics::Console.SetEventHandler(ui.GetEventHandler().App_Event);

    sf::Thread th(UI_Window::Run, &ui);

    th.launch();

    while(!EventSystem.App_Event.WindowState.Closed)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && clk.getElapsedTime().asSeconds() > 0.5f)
        {
            i = 1 - i;
            clk.restart();
            if(!i)
            {
                app.CaptureWindow();
            }
        }

        if(i)
        {
            app.UpdateWindow();
        }
        else
        {
            app.HandleWindow();
        }
    }

    glfwTerminate();

    log_file.flush();
    log_file.close();

    ui.Close();

    raise(SIGBREAK); // The App won't close if I use app.close() (Gives SIGSEGV error)

    return 0;
}
