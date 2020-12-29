#include "Object_Properties.h"

PE::Object_Properties::Object_Properties()
{
    Accleration = glm::vec3(0, 0, 0);
    u_Velocity = glm::vec3(0, 0, 0);
    Velocity = glm::vec3(0, 0, 0);
    Position = glm::vec3(0, 0, 0);
    Gravity = glm::vec3(0, 0, 0);
    Magnetic_Accleration = glm::vec3(0, 0, 0);
    Coulomb_Accleration = glm::vec3(0, 0, 0);

    Mass = 1.0f;
    Charge = 0.0f;

    color = sf::Color::Black;

    Count++;

    Name = "OBJECT " + std::to_string(Count);
}

void PE::Object_Properties::Update()
{
    Model = glm::translate(glm::mat4(1.0f), Position);
}

PE::Object_Properties::~Object_Properties()
{
    //dtor
}
