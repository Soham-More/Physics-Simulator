#ifndef WRAPPERR_H
#define WRAPPERR_H

#include <iostream>
#include <windows.h>

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef UI_H
#include <UI.hpp>
#endif // UI_H

#include <Sphere.h>
#include <Shaders/Shader.h>

namespace OGL
{
    class Init
    {
        public:

            Init()
            {
                if(!glfwInit())
                {
                    UI::ErrorStream::NewError("Opengl Error", "Opengl(Glfw) Failed to Initialize.", KILL_PROGRAM);
                }

                if(glewInit() != GLEW_OK)
                {
                    UI::ErrorStream::NewError("Opengl Error", "Opengl(Glew) Failed to Initialize.", KILL_PROGRAM);
                }
            }
    };
}

#endif // WRAPPER_OGL_H
