#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <iostream>
#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include <Physics_Sphere.h>
#include <Object_Properties.h>
#include <System_Properties.h>

namespace PE
{
    class Physics_System
    {
        private:
            std::vector<PE::Physics_Sphere> System;

            void ApplyInverseSquareLaws(int x);

            void ApplyCollision(int x);

            glm::vec3 GetMagneticField(PE::Object_Properties& x, PE::Object_Properties& i, float u, float d);

        public:
            Physics_System();

            bool AddSphere(PE::Physics_Sphere& ps);

            void Update(float DeltaTime);

            void Draw();

            ~Physics_System();

            PE::System_Properties sp;
    };
}

#endif // PHYSICS_SYSTEM_H
