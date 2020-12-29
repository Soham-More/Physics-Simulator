#include "Application.h"

Application::Application(UI::EventHandler& eh)
{
    // Create Settings For Window
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    // Create the main window
    win.create(sf::VideoMode(800, 600), "Physics Simulator(v0.1.0)", sf::Style::Close, settings);
    Win_Tex.create(800, 600);

    settings = win.getSettings();

    if((settings.minorVersion != 3) || (settings.majorVersion != 3))
    {
        UI::ErrorStream::NewError("OpenGL version 3.3 not Supported",
                                  std::string("OpenGL version 3.3 is not Supported by your GPU. ") +
                                  std::string("Nearest OpenGL version Supported is ") +
                                  std::to_string(settings.minorVersion) + "." +
                                  std::to_string(settings.majorVersion),
                                  KILL_PROGRAM);
    }

    Screen.setSize(sf::Vector2f(800, 600));

    win.setVerticalSyncEnabled(true);
    win.setPosition(sf::Vector2i(520, 20));

    EventSystem = &eh;
}

void Application::Init()
{
    std::vector<float> Triangle =
    {
        /*-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f*/

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    std::vector<float> g_uv_buffer_data =
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
        -0.5f, -0.5f,

        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
        -0.5f, -0.5f,

         0.5f,  0.5f,
         0.5f, -0.5f,
        -0.5f, -0.5f,
        -0.5f, -0.5f,
        -0.5f,  0.5f,
         0.5f,  0.5f,

         0.5f,  0.5f,
         0.5f, -0.5f,
        -0.5f, -0.5f,
        -0.5f, -0.5f,
        -0.5f,  0.5f,
         0.5f,  0.5f,

        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
        -0.5f, -0.5f,

        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
        -0.5f, -0.5f
    };

    std::vector<float> Vertex;

    for(int i = 0, j = 0; i < Triangle.size(); i += 3)
    {
        Vertex.push_back(Triangle[i + 0]);
        Vertex.push_back(Triangle[i + 1]);
        Vertex.push_back(Triangle[i + 2]);

        Vertex.push_back(2 * g_uv_buffer_data[j + 0]);
        Vertex.push_back(2 * g_uv_buffer_data[j + 1]);
        j += 2;

        float k = i / 3.0f;

        if(k > -1 && k < 6)
        {
            Vertex.push_back(-3.0f);
        }
        else if(k > 5 && k < 12)
        {
            Vertex.push_back(3.0f);
        }
        else if(k > 11 && k < 18)
        {
            Vertex.push_back(-1.0f);
        }
        else if(k > 17 && k < 24)
        {
            Vertex.push_back(1.0f);
        }
        else if(k > 23 && k < 30)
        {
            Vertex.push_back(-2.0f);
        }
        else if(k > 29 && k < 36)
        {
            Vertex.push_back(2.0f);
        }
    }

    std::vector<unsigned int> Index;

    for(int i = 0; i < Vertex.size(); i++)
    {
        Index.push_back(i);
    }

    x.loadFromFile("Tex/Cube_X.png");
    x.setRepeated(true);
    x.setSmooth(true);

    nx.loadFromFile("Tex/Cube_NX.png");
    nx.setRepeated(true);
    nx.setSmooth(true);

    y.loadFromFile("Tex/Cube_Y.png");
    y.setRepeated(true);
    y.setSmooth(true);

    ny.loadFromFile("Tex/Cube_NY.png");
    ny.setRepeated(true);
    ny.setSmooth(true);

    z.loadFromFile("Tex/Cube_Z.png");
    z.setRepeated(true);
    z.setSmooth(true);

    nz.loadFromFile("Tex/Cube_NZ.png");
    nz.setRepeated(true);
    nz.setSmooth(true);

    sh = OGL::Shader("Shader.vert");

    Blur_Shader.loadFromFile("Blur.vert", sf::Shader::Fragment);

    m.GenerateModel(Vertex, Index);

    m.SetShader(sh);
    m.SetPosition(glm::vec3(0, 0, 0));
    m.Scale(glm::vec3(400, 400, 400));

    m.SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));

    ps = PE::Physics_Sphere(glm::vec3(0, 0, 0), 5.0f, sf::Color::Red, sh);
    ps1 = PE::Physics_Sphere(glm::vec3(30, 0, 0), 10.0f, sf::Color::Blue, sh);

    ps.Properties->u_Velocity = glm::vec3(0, 0, 0); ps.Properties->Name = "Light Source"; ps.Properties->ApplyPhysics = false;
    ps1.Properties->u_Velocity = glm::vec3(0, 0, 10); ps1.Properties->Charge = 1;

    system.AddSphere(ps);
    system.AddSphere(ps1);

    CrossHair.setSize(sf::Vector2f(25, 25));
    CrossHair.setOrigin(CrossHair.getSize() * 0.5f);
    CrossHair.setPosition(sf::Vector2f(400, 300));

    if(!tex.loadFromFile("Textures/Crosshair.png"))
        UI::ErrorStream::NewError("Texture Loading Failed!",
                                  "Texture Textures/Crosshair.png Has failed. Please Make Sure that Textures/Crosshair.png Exists",
                                  KILL_PROGRAM);

    CrossHair.setTexture(&tex);

    info_name.setFont(UI::Init::Static_Font.GetFont());

    FPS.setFont(UI::Init::Static_Font.GetFont());
    FPS.setPosition(sf::Vector2f());
}

void Application::UpdateWindow()
{
    Time.restart();

    win.setActive();
    win.setVerticalSyncEnabled(true);

    // Process events
    EventSystem->handleEvents(win);

    // Clear screen
    win.clear(sf::Color::Cyan);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // OpenGL.
    cam.Update_Mouse(win);
    cam.Update_Keyboard(DeltaTime);

    sh.SetUniformMat4f("Projection", glm::perspective(glm::radians(60.0f), (float)win.getSize().x/(float)win.getSize().y, 0.1f, 750.0f));
    sh.SetUniformMat4f("View", cam.Get_View_Matrix());

    sh.SetUniform("cameraPos", cam.GetPlayerPos().x, cam.GetPlayerPos().y, cam.GetPlayerPos().z, 0.0f);

    system.Update(DeltaTime);

    system.Draw();

    Call(glActiveTexture(GL_TEXTURE0 + 0));
    sf::Texture::bind(&x);
    sh.SetUniform1i("x", 0);

    Call(glActiveTexture(GL_TEXTURE0 + 1));
    sf::Texture::bind(&nx);
    sh.SetUniform1i("nx", 1);

    Call(glActiveTexture(GL_TEXTURE0 + 2));
    sf::Texture::bind(&y);
    sh.SetUniform1i("y", 2);

    Call(glActiveTexture(GL_TEXTURE0 + 3));
    sf::Texture::bind(&ny);
    sh.SetUniform1i("ny", 3);

    Call(glActiveTexture(GL_TEXTURE0 + 4));
    sf::Texture::bind(&z);
    sh.SetUniform1i("z", 4);

    Call(glActiveTexture(GL_TEXTURE0 + 5));
    sf::Texture::bind(&nz);
    sh.SetUniform1i("nz", 5);

    sh.SetUniform("cameraPos", cam.GetPlayerPos().x, cam.GetPlayerPos().y, cam.GetPlayerPos().z, 1.0f);

    m.Draw();

    win.setMouseCursorVisible(false);
    sf::Mouse::setPosition(sf::Vector2i(400, 300) + GetWindowPosition());
    win.setMouseCursorGrabbed(true);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TEXTURE_BIT | GL_TRANSFORM_BIT | GL_VIEWPORT_BIT);
    glDisable(GL_DEPTH_TEST);

    win.resetGLStates();

    if(EventSystem->App_Event.MouseState.RightClick)
    {
        std::string Name = GetSelectedName();

        if(Name != "")
        {
            info_name.setString(Name);
            info_name.setCharacterSize(15);
            sf::FloatRect infr = info_name.getGlobalBounds();

            info.setSize(sf::Vector2f(infr.width + 10.0f, infr.height + 5.0f));
            info.setOrigin(info.getSize() * 0.5f);
            info.setPosition(sf::Vector2f(400, 250));
            info.setFillColor(sf::Color(0, 0, 0, 100));
            info.setOutlineColor(sf::Color(255, 255, 255, 64));
            info.setOutlineThickness(2);

            info_name.setPosition(info.getPosition() - sf::Vector2f((infr.width / 2.0f) + 1.25f, (infr.height / 2.0f) + 5.0f));
            info_name.setFillColor(sf::Color::White);

            win.draw(info);
            win.draw(info_name);
        }
    }

    if(Time_Passed.getElapsedTime().asSeconds() >= 1.0f)
    {
        std::string s = std::to_string(FramesPassed);

        if(s == "0") s = "60";

        FPS.setString("FPS: " + s);
        Time_Passed.restart();
        FramesPassed = 0;
    }

    // SFML Drawing(Cross Hair)
    win.draw(CrossHair);
    win.draw(FPS);

    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    sh.Bind();

    // Update the window
    win.display();

    FramesPassed++;

    win.setActive(false);

    DeltaTime = Time.getElapsedTime().asSeconds();
}

void Application::CaptureWindow()
{
    Win_Tex.update(win);
    Win_Tex.setSmooth(true);
}

void Application::HandleWindow()
{
    Time.restart();

    // Process events
    EventSystem->handleEvents(win);

    win.setMouseCursorVisible(true);
    win.setMouseCursorGrabbed(false);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TEXTURE_BIT | GL_TRANSFORM_BIT | GL_VIEWPORT_BIT);
    glDisable(GL_DEPTH_TEST);

    win.resetGLStates();

    Blur_Shader.setUniform("Sigma", 1.25f);
    Blur_Shader.setUniform("blur_radius", 0.0025f);

    sf::RenderStates RenderState_Blur;

    RenderState_Blur.shader = &Blur_Shader;

    Screen.setTexture(&Win_Tex);

    win.draw(Screen, RenderState_Blur);

    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // Update the window
    win.display();

    //std::cout << "FPS : " << 1/DeltaTime << "\n";

    DeltaTime = Time.getElapsedTime().asSeconds();
}

std::string Application::GetSelectedName()
{
    /*
    float ds = 0.1f;

    glm::vec3 Pos = cam.GetPlayerPos();
    glm::vec3 ViewDirection = cam.GetViewDirection();

    for(int i = 0; (float(i) * ds) < 550.0f; i++)
    {
        glm::vec3 RayPoint = Pos + (ViewDirection * (float(i) * ds));

        for(auto& element : system.sp.P_System)
        {
            float dist = glm::distance(RayPoint, element->Position);

            if(element->radius > dist)
            {
                return element->Name;
            }
        }
    }

    */

    glm::vec3 Pos = cam.GetPlayerPos();
    glm::vec3 ViewDirection = cam.GetViewDirection();

    for(auto& element : system.sp.P_System)
    {
        float Dist = glm::distance(Pos, element->Position);

        glm::vec3 ObjDir = (element->Position - Pos)/Dist;

        float cosAngle = glm::dot(ObjDir, ViewDirection);

        float dist = Dist * sqrt(1.0f - (cosAngle * cosAngle));

        if(element->radius > dist)
        {
            return element->Name;
        }
    }

    return "";
}

void Application::Close()
{
    win.close();
}

sf::Vector2i Application::GetWindowPosition()
{
    return win.getPosition();
}

void Application::Push_New_Sphere()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> pos(-200.0f, 200.0f);
    std::uniform_real_distribution<float> rad(-15.0f, 15.0f);
    std::uniform_int_distribution<int> col(0, 255);

    Restart:

    PE::Physics_Sphere* ps = new PE::Physics_Sphere(glm::vec3(pos(mt), pos(mt), pos(mt)), rad(mt), sf::Color(col(mt), col(mt), col(mt)), sh);

    if(!system.AddSphere(*ps))
        goto Restart;
}

Application::~Application()
{
    //dtor
}
