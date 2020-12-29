#include "Physics_System.h"

PE::Physics_System::Physics_System()
{
    //ctor
}

PE::Physics_System::~Physics_System()
{
    //dtor
}

void PE::Physics_System::Update(float DeltaTime)
{
    for(int i = 0; i < System.size(); i++)
    {
        ApplyCollision(i);
    }

    for(int i = 0; i < System.size(); i++)
    {
        ApplyInverseSquareLaws(i);

        System[i].Update(DeltaTime);
    }
}

void PE::Physics_System::Draw()
{
    for(int i = 0; i < System.size(); i++)
    {
        System[i].Draw();
    }
}

void PE::Physics_System::ApplyInverseSquareLaws(int x)
{
    PE::Object_Properties p1 = *System[x].Properties;

    glm::vec3 c_Accleration = glm::vec3();

    glm::vec3 Accleration = glm::vec3();

    glm::vec3 B = glm::vec3();

    float k = PE::System_Properties::k;

    float G = PE::System_Properties::G;

    float u = PE::System_Properties::u;

    for(int i = 0; i < System.size(); i++)
    {
        if(i == x) continue;

        PE::Object_Properties p2 = *System[i].Properties;

        float Distance = glm::distance(p2.Position - p1.Position, glm::vec3());

        glm::vec3 Direction = (p2.Position - p1.Position) / Distance;

        Accleration += ((G * p2.Mass)/(Distance * Distance)) * Direction;

        c_Accleration -= ((k * p2.Charge * p1.Charge)/(Distance * Distance * p1.Mass)) * Direction;

        B += GetMagneticField(p1, p2, u, Distance);
    }

    System[x].Properties->Gravity = Accleration;
    System[x].Properties->Coulomb_Accleration = c_Accleration;

    System[x].Properties->Magnetic_Accleration = glm::cross(B, p1.Velocity) * p1.Charge;
}

void PE::Physics_System::ApplyCollision(int x)
{
    for(int i = 0; i < System.size(); i++)
    {
        if(i == x) continue;

        if(glm::distance(System[i].Properties->Position, System[x].Properties->Position) <= (System[i].radius + System[x].radius))
        {
            glm::vec3 v1;

            float m1 = System[x].Properties->Mass, m2 = System[i].Properties->Mass;

            v1 = (System[x].Properties->Velocity * ((m1 - m2)/(m1 + m2))) +
                 (System[i].Properties->Velocity * ((2.0f * m2)/(m1 + m2)));

            System[x].Properties->u_Velocity = v1;
        }
    }

    float dpx_p = System[x].Properties->Position.x + 200;
    float dpx_n = System[x].Properties->Position.x - 200;

    float dpy_p = System[x].Properties->Position.y + 200;
    float dpy_n = System[x].Properties->Position.y - 200;

    float dpz_p = System[x].Properties->Position.z + 200;
    float dpz_n = System[x].Properties->Position.z - 200;

    float r = System[x].radius;

    float xp = (r*r) - (dpx_p * dpx_p);
    float xn = (r*r) - (dpx_n * dpx_n);

    float yp = (r*r) - (dpy_p * dpy_p);
    float yn = (r*r) - (dpy_n * dpy_n);

    float zp = (r*r) - (dpz_p * dpz_p);
    float zn = (r*r) - (dpz_n * dpz_n);

    if((xp > 0.0f || xn > 0.0f || yp > 0.0f || yn > 0.0f || zp > 0.0f || zn > 0.0f))
    {
        System[x].Properties->u_Velocity = -System[x].Properties->u_Velocity;
    }
}

glm::vec3 PE::Physics_System::GetMagneticField(PE::Object_Properties& x, PE::Object_Properties& i, float u, float d)
{
    float PI = 3.14f;

    glm::vec3 B = (u / (4 * PI)) * (glm::cross(i.Charge * i.Velocity, x.Position - i.Position) / (d*d));

    return B;
}

bool PE::Physics_System::AddSphere(PE::Physics_Sphere& ps)
{
    for(int i = 0; i < System.size(); i++)
    {
        if(glm::distance(System[i].Properties->Position, ps.Properties->Position) <= (System[i].radius + ps.radius))
        {
            return false;
        }
    }

    float dpx_p = ps.Properties->Position.x + 200;
    float dpx_n = ps.Properties->Position.x - 200;

    float dpy_p = ps.Properties->Position.y + 200;
    float dpy_n = ps.Properties->Position.y - 200;

    float dpz_p = ps.Properties->Position.z + 200;
    float dpz_n = ps.Properties->Position.z - 200;

    float r = ps.radius;

    float xp = (r*r) - (dpx_p * dpx_p);
    float xn = (r*r) - (dpx_n * dpx_n);

    float yp = (r*r) - (dpy_p * dpy_p);
    float yn = (r*r) - (dpy_n * dpy_n);

    float zp = (r*r) - (dpz_p * dpz_p);
    float zn = (r*r) - (dpz_n * dpz_n);

    if((xp > 0.0f || xn > 0.0f || yp > 0.0f || yn > 0.0f || zp > 0.0f || zn > 0.0f))
    {
        return false;
    }


    System.push_back(ps);
    sp.P_System.push_back(ps.Properties);

    return true;
}
