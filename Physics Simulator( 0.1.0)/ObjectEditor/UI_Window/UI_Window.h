#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <iostream>
#include <vector>
#include <windows.h>

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iUI.hpp>
#include <iOGL.hpp>
#include <Physics.hpp>

#include <../../Application.h>
#include <Object_Editor.h>

class UI_Window
{
    private:
        sf::RenderWindow win;

        UI::EventHandler EventSystem;

        Application* main_app;
        PE::System_Properties* sysp;

        float DeltaTime;
        sf::Clock clk;

        bool End = false;
        bool Done = false;

        std::vector<Object_Editor* > Editors;

        int Current_Editor = 1;

        // Screen Movement
        UI::Button nxt;
        UI::Button prev;

        sf::View Section;
        sf::View Display_Section;

        sf::Vector2f direction;
        sf::Vector2f Moved;
        float Speed = 200.0f;

        bool isShifting = false;

        // Physics Settings
        sf::Texture Screen;
        sf::Shader Blur_Shader;
        sf::RenderStates Render_State;
        sf::RectangleShape Screen_Capture;

        sf::Texture Settings_Texture;
        sf::RectangleShape Settings_Button;

        // Name
        sf::Text Settings_Label;

        // Constants
        sf::Text B;
        UI::Textbox B_tb;

        sf::Text C;
        UI::Textbox C_tb;

        sf::Text G;
        UI::Textbox G_tb;

        bool Show_Settings = false;

        void Draw_Settings();
        void Draw_Settings_Body(int alpha);

        std::string float_to_string(float a);

    public:
        UI_Window();

        void SetApplication(Application& app);

        void Run();

        void UpdateWindow();

        void HandleWindow();

        void Close();

        bool Finished() { return Done; }

        UI::EventHandler& GetEventHandler(){ return EventSystem; }

        ~UI_Window();
};

#endif // UI_WINDOW_H
