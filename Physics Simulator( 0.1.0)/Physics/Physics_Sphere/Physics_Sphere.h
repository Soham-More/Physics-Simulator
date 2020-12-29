#ifndef PHYSICS_SPHERE_H
#define PHYSICS_SPHERE_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iOGL.hpp>

#include <Object_Properties.h>

namespace PE
{
    class Physics_Sphere
    {
        private:
            OGL::Sphere ps;

        public:
            PE::Object_Properties* Properties;

            Physics_Sphere(){;}

            Physics_Sphere(glm::vec3 Pos, float r, sf::Color col, OGL::Shader& sh);

            void Update(float DeltaTime);

            void Draw();

            ~Physics_Sphere();

            float radius;
    };
}

#endif // PHYSICS_SPHERE_H
