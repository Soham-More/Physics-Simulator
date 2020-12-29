#include <Physics_Sphere.h>

PE::Physics_Sphere::Physics_Sphere(glm::vec3 Pos, float r, sf::Color col, OGL::Shader& sh)
{
    this->ps = OGL::Sphere(Pos, r);
    this->radius = r;
    Properties = new PE::Object_Properties;
    Properties->Position = Pos;
    Properties->radius = r;
    Properties->color = col;
    ps.SetShader(sh);
    ps.SetColor(col);
}

PE::Physics_Sphere::~Physics_Sphere()
{
    //dtor
}

void PE::Physics_Sphere::Update(float DeltaTime)
{
    ps.SetRadius(Properties->radius);
    ps.SetColor(Properties->color);

    if(!Properties->ApplyPhysics)
    {
        Properties->Mass = 0.0f;

        Properties->Velocity = glm::vec3();
        Properties->Accleration = glm::vec3();

        Properties->Accleration = glm::vec3(0, 0, 0);
        Properties->u_Velocity = glm::vec3(0, 0, 0);
        Properties->Velocity = glm::vec3(0, 0, 0);
        Properties->Gravity = glm::vec3(0, 0, 0);
        Properties->Magnetic_Accleration = glm::vec3(0, 0, 0);
        Properties->Coulomb_Accleration = glm::vec3(0, 0, 0);

        ps.SetPosition(Properties->Position);

        return;
    }

    Properties->Total_Accleration = Properties->Accleration + Properties->Gravity + Properties->Coulomb_Accleration + Properties->Magnetic_Accleration;

    Properties->Velocity = Properties->u_Velocity + (Properties->Total_Accleration * DeltaTime);

    Properties->Position += (Properties->u_Velocity * DeltaTime) + ((0.5f * DeltaTime * DeltaTime) * Properties->Total_Accleration);

    ps.SetPosition(Properties->Position);

    Properties->u_Velocity = Properties->Velocity;
}

void PE::Physics_Sphere::Draw()
{
    ps.Draw();
}
