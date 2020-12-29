#ifndef OBJECT_EDITOR_H
#define OBJECT_EDITOR_H

#include <iostream>
#include <windows.h>

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iUI.hpp>
#include <iOGL.hpp>
#include <Physics.hpp>

class Object_Editor
{
    private:
        //Self defining Attributes
        UI::EventData* evtd;

        //Physics Attributes
        PE::System_Properties* sysp;

        // Object_Editor Id.
        int id = 0;
        sf::Vector2f Offset_Pos;

        // Labels

            // 1st Page:

            // ->Position
            sf::Text Pos_Label;
            sf::Text x;
            sf::Text y;
            sf::Text z;

            // ->Radius
            sf::Text radius;

            // ->Color
            sf::Text Color_Label;
            sf::Text r;
            sf::Text g;
            sf::Text b;
            sf::Text pv;

            // 2nd Page:

            // ->Mass & Charge
            sf::Text m_Label;
            sf::Text c_Label;

            // ->Velocity
            sf::Text v_Label;
            sf::Text vx;
            sf::Text vy;
            sf::Text vz;

            // ->Acceleration: Part-A
            sf::Text a_Label;
            sf::Text ax; sf::Text avx;
            sf::Text ay; sf::Text avy;
            sf::Text az; sf::Text avz;

            sf::Text B; sf::Text Bx; sf::Text By; sf::Text Bz; // Magnetic
            sf::Text G; sf::Text Gx; sf::Text Gy; sf::Text Gz; // Gravity
            sf::Text C; sf::Text Cx; sf::Text Cy; sf::Text Cz; // Coulomb

            // ->Acceleration: Part-B
            sf::Text ab_Label;
            sf::Text abx;
            sf::Text aby;
            sf::Text abz;


        //UI elements
        UI::Textbox title;

            // 1st Page:

            //->Position
            UI::Textbox PositionX;
            UI::Textbox PositionY;
            UI::Textbox PositionZ;

            // ->Radius
            UI::Textbox TRadius;

            // ->Color
            UI::Slider Red;
            UI::Slider Green;
            UI::Slider Blue;

            sf::RectangleShape Preview;

            // 2nd page:

            // ->Mass & Charge
            UI::Textbox Mass;
            UI::Textbox Charge;

            // ->Velocity
            UI::Textbox VelocityX;
            UI::Textbox VelocityY;
            UI::Textbox VelocityZ;

            // -> Acceleration: Part-A
            sf::RectangleShape Show_More;
            sf::Texture Show_More_Tex;

            sf::RectangleShape More_Info_Container;

            // -> Acceleration: Part-B
            UI::Textbox AccelerationX;
            UI::Textbox AccelerationY;
            UI::Textbox AccelerationZ;

        // General
            sf::Vector2f direction;
            sf::Vector2f Moved;
            float Speed = 200.0f;

            bool isShifting = false;

            UI::Button down;

        // Draw Sections of elements
        void InitPosition();
        void DrawPosition(sf::RenderWindow& win);

        void InitRadius();
        void DrawRadius(sf::RenderWindow& win);

        void InitColor();
        void DrawColor(sf::RenderWindow& win);

        // 2nd Page
        void InitVelocity();
        void DrawVelocity(sf::RenderWindow& win);

        void InitMC();
        void DrawMC(sf::RenderWindow& win);

        void InitAccelerationA();
        void DrawAccelerationA(sf::RenderWindow& win);

        void InitAccelerationB();
        void DrawAccelerationB(sf::RenderWindow& win);

    public:
        Object_Editor();

        void Create(int ID);

        void Set(PE::System_Properties* p, UI::EventData* ed);

        void Draw(sf::RenderWindow& win, sf::View& view, float dt);

        ~Object_Editor();

        static int mode;
};

#endif // OBJECT_EDITOR_H
