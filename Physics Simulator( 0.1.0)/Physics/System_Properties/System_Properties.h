#ifndef SYSTEM_PROPERTIES_H
#define SYSTEM_PROPERTIES_H

#include <iostream>
#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include <Physics_Sphere.h>
#include <Object_Properties.h>

namespace PE
{
    class System_Properties
    {
        private:
            ;

        public:
            System_Properties();
            ~System_Properties();

            std::vector<PE::Object_Properties* > P_System;

            static float k;

            static float G;

            static float u;
    };
}

#endif // SYSTEMPROPERTIES_H
