#include "UI_Window.h"

std::string UI_Window::float_to_string(float a)
{
    std::stringstream fss;

    fss << a;

    std::string ans = fss.str();

    std::string result;

    bool Decimal_Encountered = false;

    int Places_After_Decimal = 0;

    for(char c : ans)
    {
        if(c == '.')
        {
            Decimal_Encountered = true;
        }

        result += c;

        if(Places_After_Decimal >= 2)
        {
            if(result == "-0.00") result = 0.0f;

            return result;
        }

        if(Decimal_Encountered)
        {
            Places_After_Decimal++;
        }
    }

    return ans;
}

UI_Window::UI_Window()
{
    // Create Settings For Window
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    // Create the main window
    win.create(sf::VideoMode(500, 375), "Editor", sf::Style::Resize, settings);
    Screen.create(500, 375);
    Screen_Capture.setSize(sf::Vector2f(500, 375));
    Screen_Capture.setPosition(sf::Vector2f());

    win.setVerticalSyncEnabled(true);
    win.setPosition(sf::Vector2i(5, 20));

    Section = win.getDefaultView();

    nxt.Create(sf::Vector2f(447, 137.5f), sf::Vector2f(50, 100), ">", EventSystem.App_Event, sf::Color::Black);
    prev.Create(sf::Vector2f(3, 137.5f), sf::Vector2f(50, 100), "<", EventSystem.App_Event, sf::Color::Black);

    if(!Settings_Texture.loadFromFile("Textures/Settings.png"))
    {
        UI::ErrorStream::NewError("File not Found!",
                                  "Settings.png was not found in Textures folder!",
                                  KILL_PROGRAM);
    }

    Settings_Button.setSize(sf::Vector2f(40, 40));
    Settings_Button.setTexture(&Settings_Texture);
    Settings_Button.setOrigin(Settings_Button.getSize() * 0.5f);
    Settings_Button.setPosition(sf::Vector2f(480, 40) - Settings_Button.getOrigin());

    if(!Blur_Shader.loadFromFile("Blur.vert", sf::Shader::Fragment))
    {
        UI::ErrorStream::NewError("File not Found!",
                                  "Blur.vert was not found!",
                                  KILL_PROGRAM);
    }

    Render_State.shader = &Blur_Shader;

    Settings_Label.setFont(UI::Init::Static_Font.GetFont());
    B.setFont(UI::Init::Static_Font.GetFont());
    C.setFont(UI::Init::Static_Font.GetFont());
    G.setFont(UI::Init::Static_Font.GetFont());

    Settings_Label.setString("Settings");
    Settings_Label.setFillColor(sf::Color::Black);
    Settings_Label.setStyle(sf::Text::Bold);

    sf::FloatRect fr = Settings_Label.getGlobalBounds();

    Settings_Label.setPosition(250 - (fr.width/2.0f), 5.0f);

    char str[] = {char(181), '\0'};

    B.setString(std::string(str) + "(Permeability of Space):");
    B.scale(sf::Vector2f(0.75f, 0.75f));
    B.setFillColor(sf::Color::Black);
    B.setStyle(sf::Text::Bold);

    B.setPosition(20.0f, 50.0f);

    UI::TextBox_Style ts;

    ts.Default_Color = sf::Color(sf::Color::Cyan.r, sf::Color::Cyan.g, sf::Color::Cyan.b, 128);
    ts.Selected_Color = sf::Color(sf::Color::Cyan.r, sf::Color::Cyan.g, sf::Color::Cyan.b, 192);
    ts.Text_Color = sf::Color::Black;
    ts.isCentered = true;

    B_tb.Create(sf::Vector2f(5.0f + B.getGlobalBounds().left + B.getGlobalBounds().width, 55.0f), 120, EventSystem.App_Event, float_to_string(PE::System_Properties::u), true);
    B_tb.SetStyle(ts);

    C.setString("k(Coulomb's Constant):");
    C.scale(sf::Vector2f(0.75f, 0.75f));
    C.setFillColor(sf::Color::Black);
    C.setStyle(sf::Text::Bold);

    C.setPosition(20.0f, 100.0f);

    C_tb.Create(sf::Vector2f(5.0f + C.getGlobalBounds().left + C.getGlobalBounds().width, 105.0f), 120, EventSystem.App_Event, float_to_string(PE::System_Properties::k), true);
    C_tb.SetStyle(ts);

    G.setString("G(Gravitational Constant):");
    G.scale(sf::Vector2f(0.75f, 0.75f));
    G.setFillColor(sf::Color::Black);
    G.setStyle(sf::Text::Bold);

    G.setPosition(20.0f, 150.0f);

    G_tb.Create(sf::Vector2f(5.0f + G.getGlobalBounds().left + G.getGlobalBounds().width, 155.0f), 120, EventSystem.App_Event, float_to_string(PE::System_Properties::G), true);
    G_tb.SetStyle(ts);
}

void UI_Window::Draw_Settings()
{
    std::vector<sf::Texture* > TextureArray;

    for(int i = 0; i < 50; i++)
    {
        clk.restart();

        win.clear(sf::Color::Cyan);

        EventSystem.handleEvents(win);
        UI::Graphics::Update();

        sf::Texture* tex = new sf::Texture(Screen);
        TextureArray.push_back(tex);

        Settings_Button.rotate(75.0f * DeltaTime);

        Blur_Shader.setUniform("Sigma", 1.0f);
        Blur_Shader.setUniform("blur_radius", 1.0f);

        win.draw(Screen_Capture, Render_State);
        Screen.update(win);

        Draw_Settings_Body(int(float(i/50.0f) * 255));
        win.draw(Settings_Button);

        win.display();

        DeltaTime = clk.getElapsedTime().asSeconds();
    }

    sf::Texture* tex = new sf::Texture(Screen);
    TextureArray.push_back(tex);

    bool isClicked = false;

    while(!isClicked && !End)
    {
        clk.restart();

        win.clear(sf::Color::Cyan);

        EventSystem.handleEvents(win);
        UI::Graphics::Update();

        win.draw(Screen_Capture, Render_State);
        win.draw(Settings_Button);

        Draw_Settings_Body(255);

        sf::Vector2f MousePos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
        UI::MouseData ms = EventSystem.App_Event.MouseState;
        sf::FloatRect fr = Settings_Button.getGlobalBounds();

        if(fr.contains(MousePos) && ms.LeftClick && !ms.Dragged)
        {
            isClicked = true;
        }
        else if(ms.LeftClick)
        {
            isClicked = false;
        }

        win.display();

        DeltaTime = clk.getElapsedTime().asSeconds();
    }

    for(int i = 0; (i < 50) && !End; i++)
    {
        clk.restart();

        win.clear(sf::Color::Cyan);

        EventSystem.handleEvents(win);
        UI::Graphics::Update();

        Screen_Capture.setTexture(TextureArray[50 - i]);

        Settings_Button.rotate(75.0f * DeltaTime);

        win.draw(Screen_Capture);
        win.draw(Settings_Button);

        Draw_Settings_Body(int(float((50.0f - i)/50.0f) * 255));

        win.display();

        DeltaTime = clk.getElapsedTime().asSeconds();
    }
}

void UI_Window::Draw_Settings_Body(int alpha)
{
    // Set Alpha
    Settings_Label.setFillColor(sf::Color(Settings_Label.getFillColor().r, Settings_Label.getFillColor().g, Settings_Label.getFillColor().b, alpha));
    B.setFillColor(sf::Color(B.getFillColor().r, B.getFillColor().g, B.getFillColor().b, alpha));
    C.setFillColor(sf::Color(C.getFillColor().r, C.getFillColor().g, C.getFillColor().b, alpha));
    G.setFillColor(sf::Color(G.getFillColor().r, G.getFillColor().g, G.getFillColor().b, alpha));

    UI::TextBox_Style ts;

    ts.Default_Color = sf::Color(sf::Color::Cyan.r, sf::Color::Cyan.g, sf::Color::Cyan.b, std::max(alpha - 127, 0));
    ts.Selected_Color = sf::Color(sf::Color::Cyan.r, sf::Color::Cyan.g, sf::Color::Cyan.b, std::max(alpha - 63, 0));
    ts.Text_Color = sf::Color(0, 0, 0, alpha);
    ts.isCentered = true;

    B_tb.SetStyle(ts);
    C_tb.SetStyle(ts);
    G_tb.SetStyle(ts);

    win.draw(Settings_Label);
    win.draw(B);
    win.draw(C);
    win.draw(G);

    B_tb.Update();
    C_tb.Update();
    G_tb.Update();

    if(B_tb.isActive())
    {
        if((B_tb.GetInput() != "")  && (B_tb.GetInput() != "-"))
        {
            float val = std::stof(B_tb.GetInput());

            if(val > 999.0f && val < 0.0f)
            {
                PE::System_Properties::u = val;
            }
            else
            {
                if(val > 999.0f)
                {
                    B_tb.resetValue("999.0");
                    PE::System_Properties::u = 999.0f;
                }
                else if(val < 0.0f)
                {
                    B_tb.resetValue("1.0");
                    PE::System_Properties::u = 1.0f;
                }
            }
        }
    }
    else
    {
        B_tb.resetValue(float_to_string(PE::System_Properties::u));
    }

    if(C_tb.isActive())
    {
        if((C_tb.GetInput() != "")  && (C_tb.GetInput() != "-"))
        {
            float val = std::stof(C_tb.GetInput());

            if(val > 999.0f && val < 0.0f)
            {
                PE::System_Properties::k = val;
            }
            else
            {
                if(val > 999.0f)
                {
                    C_tb.resetValue("999.0");
                    PE::System_Properties::k = 999.0f;
                }
                else if(val < 0.0f)
                {
                    C_tb.resetValue("1.0");
                    PE::System_Properties::k = 1.0f;
                }
            }
        }
    }
    else
    {
        C_tb.resetValue(float_to_string(PE::System_Properties::k));
    }

    if(G_tb.isActive())
    {
        if((G_tb.GetInput() != "")  && (G_tb.GetInput() != "-"))
        {
            float val = std::stof(G_tb.GetInput());

            if(val > 999.0f && val < 0.0f)
            {
                PE::System_Properties::G = val;
            }
            else
            {
                if(val > 999.0f)
                {
                    G_tb.resetValue("999.0");
                    PE::System_Properties::G = 999.0f;
                }
                else if(val < 0.0f)
                {
                    G_tb.resetValue("1.0");
                    PE::System_Properties::G = 1.0f;
                }
            }
        }
    }
    else
    {
        G_tb.resetValue(float_to_string(PE::System_Properties::G));
    }

    B_tb.Draw(win);

    C_tb.Draw(win);

    G_tb.Draw(win);
}

void UI_Window::SetApplication(Application& app)
{
    sysp = app.GetPhyProperties();
    main_app = &app;

    for(int i = 1; i < sysp->P_System.size(); i++)
    {
        Object_Editor* Editor = new Object_Editor;

        Editor->Create(i);
        Editor->Set(sysp, &EventSystem.App_Event);

        Editors.push_back(Editor);
    }
}

void UI_Window::Run()
{
    while(!End)
    {
        UpdateWindow();
    }

    win.close();

    Done = true;
}

void UI_Window::UpdateWindow()
{
    clk.restart();

    EventSystem.handleEvents(win);

    win.setActive();
    win.clear(sf::Color::Cyan);

    win.setTitle(sysp->P_System[Current_Editor]->Name);

    win.setView(win.getDefaultView());

    if(Current_Editor == Editors.size())
    {
        nxt.SetText("+");
    }
    else
    {
        nxt.SetText(">");
    }

    if(!Object_Editor::mode)
    {
        if(nxt.Draw(win) && !isShifting)
        {
            direction = sf::Vector2f(1.0f, 0.0f);
            isShifting = true;

            if(Current_Editor == Editors.size())
            {
                main_app->Push_New_Sphere();

                Object_Editor* Editor = new Object_Editor;

                Editor->Create(++Current_Editor);
                Editor->Set(sysp, &EventSystem.App_Event);

                Editors.push_back(Editor);
            }
            else
            {
                Current_Editor++;
            }
        }

        if(prev.Draw(win) && (Current_Editor - 1) && !isShifting)
        {
            direction = sf::Vector2f(-1.0f, 0.0f);
            isShifting = true;
            Current_Editor--;
        }

        if((abs(Moved.x) < 500.0f) && isShifting)
        {
            Speed += 100.0f * DeltaTime;

            sf::Vector2f Move = direction * DeltaTime * Speed;
            Section.move(Move);
            Moved += Move;
        }
        else
        {
            if(abs(Moved.x) > 500.0f)
            {
                Display_Section = win.getDefaultView();

                Display_Section.move(500.0f * (Current_Editor - 1), 0);

                Section = Display_Section;
            }

            direction = sf::Vector2f();
            Moved = sf::Vector2f();
            isShifting = false;
            Speed = 200.0f;
        }
    }

    win.setView(Section);

    for(Object_Editor* Editor : Editors)
    {
        Editor->Draw(win, Section, DeltaTime);
    }

    win.setView(win.getDefaultView());

    sf::Vector2f MousePos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
    bool isClicked = false;
    UI::MouseData ms = EventSystem.App_Event.MouseState;

    sf::FloatRect fr = Settings_Button.getGlobalBounds();

    if(fr.contains(MousePos) && ms.LeftClick && !ms.Dragged)
    {
        isClicked = true;
    }
    else if(ms.LeftClick)
    {
        isClicked = false;
    }

    if(isClicked)
    {
        Screen.update(win);
        Screen_Capture.setTexture(&Screen);

        Draw_Settings();
    }

    win.draw(Settings_Button);

    win.setView(Section);

    win.display();

    win.setActive(false);

    DeltaTime = clk.getElapsedTime().asSeconds();
}

void UI_Window::HandleWindow()
{
    //clk.restart();

    EventSystem.handleEvents(win);
    //UI::Graphics::Update();

    //win.setActive(false);

    //DeltaTime = clk.getElapsedTime().asSeconds();
}

void UI_Window::Close()
{
    End = true;
}

UI_Window::~UI_Window()
{
    //dtor
}
