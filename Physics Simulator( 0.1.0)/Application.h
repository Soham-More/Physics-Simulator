#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <random>
#include <windows.h>

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iUI.hpp>
#include <iOGL.hpp>
#include <Physics.hpp>

class Application
{
    private:
        // App Window
        sf::RenderWindow win;

        // Texture for Special Effects(Post Processing)(Blur)
        sf::Texture Win_Tex;

        // Screen Displays the Post Processed Screen
        sf::RectangleShape Screen;

        // Cross Hair
        sf::RectangleShape CrossHair;
        sf::Texture tex;

        // Info Box
        sf::RectangleShape info;
        sf::Text info_name;

        // UI Event handler
        UI::EventHandler* EventSystem;

        // Camera
        OGL::Camera cam;

        // Testing Area
        OGL::Model m;

        // Shader/s
        OGL::Shader sh;
        sf::Shader Blur_Shader;

        PE::Physics_Sphere ps;
        PE::Physics_Sphere ps1;

        // A Collection of Physics Bodies
        PE::Physics_System system;

        float DeltaTime = 0;
        sf::Clock Time;
        unsigned int FramesPassed = 0;

        sf::Text FPS;
        sf::Clock Time_Passed;

        sf::Texture x;
        sf::Texture nx;
        sf::Texture y;
        sf::Texture ny;
        sf::Texture z;
        sf::Texture nz;

    public:
        Application(UI::EventHandler& eh);

        void Init();

        PE::System_Properties* GetPhyProperties(){ return &(this->system.sp); }

        void UpdateWindow();

        void HandleWindow();

        void Push_New_Sphere();

        void CaptureWindow();

        void Close();

        sf::Vector2i GetWindowPosition();

        std::string GetSelectedName();

        ~Application();
};

#endif // APPLICATION_H
