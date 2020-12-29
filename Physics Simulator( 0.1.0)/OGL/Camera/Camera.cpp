#include "Camera.h"

OGL::Camera::Camera()
{
    Viewdirection = glm::vec3(0.0f, 0.0f, -1.0f);
    Up = glm::vec3(0.0f, 1.0f, 0.0f);
    Right = glm::cross(Viewdirection, Up);
    this->pos = glm::vec3(0, 50, 0);
}

OGL::Camera::~Camera()
{
    //dtor
}

glm::vec2 OGL::Camera::Update_Mouse(sf::RenderWindow& win)
{
    double xpos, ypos;

    sf::Mouse m;
    sf::Vector2i mp = m.getPosition();

    xpos = (double)mp.x;
    ypos = (double)mp.y;

    glm::vec2 DeltaMouse = glm::vec2(xpos, ypos) - oldMousePos;
    if(glm::length(DeltaMouse) > 50)
    {
        oldMousePos = glm::vec2(win.getPosition().x + 400, win.getPosition().y + 300);
        DeltaMouse = glm::vec2();
    }

    Viewdirection = glm::mat3(glm::rotate(glm::mat4(1.0f), -DeltaMouse.x * 0.05f, Up)) * Viewdirection;

    Right = glm::cross(Viewdirection, Up);

    Viewdirection = glm::mat3(glm::rotate(glm::mat4(1.0f),-DeltaMouse.y * 0.05f, Right)) * Viewdirection;

    oldMousePos = glm::vec2(win.getPosition().x + 400, win.getPosition().y + 300);

    return oldMousePos;
}

void OGL::Camera::Update_Keyboard(float DeltaTime)
{
    glm::vec3 Move(0.0f);

    sf::Keyboard k;

    float Speed = 1.0f * glfwGetTime();

    if(k.isKeyPressed(sf::Keyboard::Up))
        Move += DeltaTime * Viewdirection * Speed;
    if(k.isKeyPressed(sf::Keyboard::Down))
        Move -= DeltaTime * Viewdirection * Speed;
    if(k.isKeyPressed(sf::Keyboard::Right))
        Move += DeltaTime * Right * Speed;
    if(k.isKeyPressed(sf::Keyboard::Left))
        Move -= DeltaTime * Right * Speed;

    this->pos += Move;
}

glm::mat4 OGL::Camera::Get_View_Matrix()
{
    return glm::lookAt(
        pos,                 // Camera is at (4,3,3), in World Space
        pos + Viewdirection, // and looks at the origin
        Up//glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
}
