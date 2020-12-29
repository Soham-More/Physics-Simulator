#ifndef OBJECT_PROPERTIES_H
#define OBJECT_PROPERTIES_H

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace PE
{
    class Object_Properties
    {
        public:
            Object_Properties();

            void Update();

            ~Object_Properties();

            //Physics
            float Mass;
            float Charge;

            glm::vec3 Position;

            glm::vec3 Velocity;
            glm::vec3 u_Velocity;

            glm::vec3 Total_Accleration;
            glm::vec3 Accleration;
            glm::vec3 Gravity;
            glm::vec3 Magnetic_Accleration;
            glm::vec3 Coulomb_Accleration;

            //Sphere Properties
            std::string Name;
            float radius;
            glm::mat4 Model;
            sf::Color color;

            bool ApplyPhysics = true;

            //Self
            static int Count;
    };
}

#endif // OBJECT_PROPERTIES_H
